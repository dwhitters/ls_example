#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char * argv[])
{
    DIR *dirPtr;
    struct dirent *entryPtr;
    struct stat statBuf;

	char arg[3] = {0};
	char file_path[128] = {0};

	int index = 1;
	/* Set to true when arg is provided. */
	bool arg_provided = false;

	/* There must be additional arguments. */
	if(argc == 1)
	{
		perror("Must provide file path!");
		exit(EXIT_FAILURE);
	}
	/* 
 		We are assuming that there will either only by one argument
		or no arguments.
	*/
	if(argc == 3)
	{
		/* Copy the argument into our arg string if present. */
		memcpy(arg, argv[index], strlen(argv[index]));
		arg_provided = true;
		++index;
	}	

	/* Copy the file path into our variable. */
	memcpy(file_path, argv[index], strlen(argv[index]));

	/* Open the file path provided. */
    if((dirPtr = opendir(file_path)) == NULL)
    {
	perror("Error on opening directory.");
	exit(EXIT_FAILURE);
    }

	/* Read all the entries in the file path. */
    while ((entryPtr = readdir(dirPtr)))
    {
			printf("Name: %-20s", entryPtr->d_name);
			printf("\t");

			char file_to_search[256] = {0};
			memcpy(file_to_search, file_path, strlen(file_path));
			(void)strcat(file_to_search, "/");
			(void)strcat(file_to_search, entryPtr->d_name);

			if (stat(file_to_search, &statBuf) < 0) {
				perror("huh?  there is ");
				exit(1);
			}
			printf("Size: %llu\n", (unsigned long long)statBuf.st_size);
    }
    closedir(dirPtr);
    return 0;
}
