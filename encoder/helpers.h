#pragma once

#include <sys\stat.h>

// Function will return back True or False depending on whether the path exists
bool does_file_exist(char *file_path);

void safe_delete(void **p);