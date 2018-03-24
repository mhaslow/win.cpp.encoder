#pragma once

// Set up defines which will be used throughout the solution
#define MAX_VOLTAGE 5							// Maximum voltage 
#define MAX_ENC_ROTATION_DEG 360				// Full rotation of motor shaft
#define MAX_ADC_COUNT 255						// 8-bit ADC
#define NUM_COUNTS_PER_MOTOR_ROTATION 2048		// Num of counts read for one full rotation of the motor shaft
#define GEAR_REDUCTION 30						// Gear reduction value
#define INIT_TIME 0.5							// Initialization time in seconds for the two sensors
#define THRESHOLD 5.8							// Specification which is used to compare the sensor value
												//		This value was calculated based on the difference between the ADC values
												//		of a perfect functioning sensor and a normal functioning sensor and then converted it to degrees

// Method Return Codes
#define SUCCESS						0x0000
#define ERROR_FILE_NOT_OPEN			0x0001
#define ERROR_READ_LINE				0x0002
#define ERROR_SENSOR_VALUE			0x0003
#define ERROR_FILE_DOES_NOT_EXIST	0x0004
