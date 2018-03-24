#include <stdlib.h>
#include <iostream>

#include "defs.h"
#include "helpers.h"
#include "Encoder.h"
#include "UnitTests.h"

void main(int argc, char *argv[])
{
	// Check to make sure that some argument has been passed to the program
	if (argc < 2)
	{
		std::cerr << "No arguments have been passed to the application." << std::endl;
		return;
	}

	// Option to run unit tests
	if (strcmp(argv[argc - 1], "--test") == 0)
	{
		std::cout << "Running Tests." << std::endl;
		run_unit_tests();
		return;
	}

	// Store the file path passed in as the argument of the programn
	char *file_path = argv[argc - 1];
	
	// Check to make sure that the file path exists
	if (!does_file_exist(file_path))
	{
		std::cerr << "File does not exist: " << file_path << std::endl;
		return;
	}

	// Create Encoder Object
	Encoder *e = new Encoder();

	// Call init() to initialize the sensor data file
	// If the call does not execute successfully then issue an error
	if (e->init(file_path) != SUCCESS)
	{
		std::cerr << "Encoder did not intialize successfully." << std::endl;
		safe_delete((void**)&e);
		return;
	}

	// Begin parsing the sensor values
	// If the call does not execute successfully then issue an error
	if (e->parse_sensor_values() != SUCCESS)
	{
		std::cerr << "Sensor has failed." << std::endl;
		safe_delete((void**)&e);
		return;
	}

	// Report back to the operator that the sensor has passed.
	std::cout << "Sensor has passed." << std::endl;
	
	// Free memory and set pointers to NULL
	safe_delete((void**)&e);
	
}