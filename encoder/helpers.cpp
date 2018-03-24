#include "helpers.h"


/*
	Purpose of this function is to return back a boolean reponse to whether a file
	path exists or not
*/
bool
does_file_exist(char *file_path)
{
	struct stat file_info;
	return stat(file_path, &file_info) != 0 ? false : true;
}

/*
	The purpose of this function is to provide a means safely delete a pointer and set
	the variable back to NULL as to avoid a dangling pointer.
*/
void
safe_delete(void **p)
{
	if (p != NULL)
	{
		delete *p;
		*p = NULL;
	}
}