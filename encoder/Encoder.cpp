#include "Encoder.h"


Encoder::Encoder()
	/* Initialization List */
	:	m_cptrSensorFilePath(NULL),
		m_fCalAdcVal(0.0f),
		m_iDataFileIndex(0),
		m_fEncCountsPerDeg((float)MAX_ENC_ROTATION_DEG / NUM_COUNTS_PER_MOTOR_ROTATION),
		m_fAdcCountsPerDeg((float)MAX_ENC_ROTATION_DEG / MAX_ADC_COUNT)
{

}

Encoder::~Encoder()
{
	// Delete Any Pointers used during programming running
	if (this->m_cptrSensorFilePath)
	{
		delete this->m_cptrSensorFilePath;
		this->m_cptrSensorFilePath = NULL;
	}
}

/*
	Purpose of this function is to open up the sensor data file and begin iterating through line
	by line and getting each necessary values which are delimited by spaces. The three values are then
	saved into local variables and then had the necessary unit convertion applied to them before
	they are stored into a vector for later use when parsing out the data.
*/
int16_t
Encoder::init(char *file_path)
{
	// Set the sensor file path
	this->set_sensor_file_path(file_path);

	// Open the file
	this->m_FileStream.open(this->m_cptrSensorFilePath);

	// Check to make sure the was able to be opened
	if (!this->m_FileStream.is_open())
	{
		std::cerr << __FUNCTION__ << " -- Following file was not able to be opened: " << this->m_cptrSensorFilePath << std::endl;
		return ERROR_FILE_NOT_OPEN;
	}

	// Iterate through each line of the file
	std::string line;
	while (std::getline(this->m_FileStream, line))
	{
		std::istringstream is_sstr(line);	// Input string stream
		float time = 0.0f;					// Time
		int encoder = 0;					// Value of encoder
		int potentiometer = 0;				// Value reading from potentiometer

		// Save the data into these three variables
		if (!(is_sstr >> time >> encoder >> potentiometer))
		{
			std::cerr << __FUNCTION__ << " -- Error reading line: " << is_sstr.str().c_str() << std::endl;
			return ERROR_READ_LINE;
		}
		// Convert all of the measured values to be the same units
		// Save them into a vector for use later
		m_vecTime.push_back(time);
		m_vecEncVals.push_back(((float)encoder * this->m_fEncCountsPerDeg) / GEAR_REDUCTION);
		m_vecAdcVals.push_back((float)potentiometer * this->m_fAdcCountsPerDeg);
	}

	// Close File Stream
	this->m_FileStream.close();

	// Run sensor calibration 
	this->calibrate_sensor_readings();
	
	// Return Success
	return SUCCESS;
}

/*
	Purpose of this function is to provide a method for getting the sensor file path
*/
char*
Encoder::get_sensor_file_path(void)
{
	return this->m_cptrSensorFilePath;
}

/*
	Purpose of this function is to provide a method for setting the sensor file path
*/
int16_t
Encoder::set_sensor_file_path(char * file_path)
{
	if (!does_file_exist(file_path))
	{
		std::cerr << __FUNCTION__ << " -- File does not exist: " << file_path << std::endl;
		return ERROR_FILE_DOES_NOT_EXIST;
	}
	this->m_cptrSensorFilePath = file_path;
	return SUCCESS;
}

/*
	Purpose of this function is to go through the values beginning at time == 0.0 to 
	time == 0.5 and get an average ADC value which will be used to calibrate the sensor
*/
void
Encoder::calibrate_sensor_readings(void)
{
	// Set up iterators for the two vectors
	std::vector<float>::iterator time_itr = this->m_vecTime.begin();
	std::vector<float>::iterator adc_itr = this->m_vecAdcVals.begin();

	// Initialize variables
	float sumOfAdcVals = 0.0f;

	// Iterate through each entry while the beginning 
	while (*time_itr++ < INIT_TIME)
	{
		// Begin adding up the adc values
		sumOfAdcVals += *adc_itr++;

		// Increment number of values seen
		this->m_iDataFileIndex++;
	}

	// Store the calibrated value and the total number of entries found 
	// during the initialization period
	this->m_fCalAdcVal = (sumOfAdcVals / this->m_iDataFileIndex);
}

/*
	Purpose of this function is to parse the saved data and inspect each sensor reading for potential 
	errors in the sensor.
*/
int16_t
Encoder::parse_sensor_values(void)
{
	// Initialize iterators to the ADC and Encoder values beginning at the last read data file index
	std::vector<float>::iterator adc_itr = std::next(this->m_vecAdcVals.begin(), this->m_iDataFileIndex);
	std::vector<float>::iterator enc_itr = std::next(this->m_vecEncVals.begin(), this->m_iDataFileIndex);

	// Iterate over the ADC and Encoder values
	while (adc_itr != this->m_vecAdcVals.end() && 
			enc_itr != this->m_vecEncVals.end())
	{
		// Get the current poof the potentiometer
		float curMotorPos = *adc_itr++;
		float calcMotorPos = this->m_fCalAdcVal + *enc_itr++;

		// Check to see if the different between the two values is larger than the threshold
		if (abs(curMotorPos - calcMotorPos) > THRESHOLD)
		{
			std::vector<float>::iterator time_itr = std::next(this->m_vecTime.begin(), this->m_iDataFileIndex);
			std::cout << "Sensor has failed at time: " << (float)*time_itr << std::endl;
			return ERROR_SENSOR_VALUE;
		}

		// Increment Datafile file index
		this->m_iDataFileIndex++;
	}

	// Return
	return SUCCESS;
}