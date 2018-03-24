#include "UnitTests.h"

void
run_unit_tests(void)
{
	if (test_file_path_not_exist())
	{
		std::cout << "test_file_path_not_exist() has passed" << std::endl;
	}
	else
	{
		std::cout << "test_file_path_not_exist() has failed" << std::endl;
	}

	if (test_init_bad_file_parse())
	{
		std::cout << "test_init_bad_file_parse() has passed" << std::endl;
	}
	else
	{
		std::cout << "test_init_bad_file_parse() has failed" << std::endl;
	}
}

/*
	The purpose of this unit test is to check the condition of the file path not existing.
*/
bool 
test_file_path_not_exist(void)
{
	bool rsp = false;
	char *bad_file_path = "C:\\Users\\Public\\Public Desktop\\Folder_That_Does_Not_Exist\\normal.txt";

	Encoder *e = new Encoder();

	e->set_sensor_file_path(bad_file_path) == ERROR_FILE_DOES_NOT_EXIST ? rsp = true : rsp = false;

	return rsp;
}

/*
	The purpose of this unit test is to check the condition of the file parsing getting a bad line without
	all of the values it is expecting being present.
*/
bool
test_init_bad_file_parse(void)
{
	bool rsp = false;
	char *bad_error_file = "..\\..\\Unit_Tests\\error_bad.txt";

	Encoder *e = new Encoder();
	
	e->init(bad_error_file) != SUCCESS ? rsp = true : rsp = false;

	return rsp;
}