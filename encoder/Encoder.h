#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "defs.h"
#include "helpers.h"

/*
	Encoder class contains all of the necessary utilities to parse out the data file 

*/
class Encoder
{
	public:
		Encoder();
		~Encoder();

		/* Public Member Methods */
		int16_t init(char *file_path);
		char* get_sensor_file_path(void);
		int16_t parse_sensor_values(void);
		int16_t set_sensor_file_path(char *);

	private:
		/* Private Member Variables */
		char				*m_cptrSensorFilePath;
		float				m_fCalAdcVal;
		int					m_iDataFileIndex;
		float				m_fEncCountsPerDeg;
		float				m_fAdcCountsPerDeg;
		std::ifstream		m_FileStream;
		std::vector<float>	m_vecTime;
		std::vector<float>	m_vecEncVals;
		std::vector<float>	m_vecAdcVals;

		/* Private Member Methods */
		void calibrate_sensor_readings(void);
};