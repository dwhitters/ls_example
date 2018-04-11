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
		printf("Must provide file path!\n");
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
		printf("Error on opening directory.\n");
		exit(EXIT_FAILURE);
	}

	/* Read all the entries in the file path. */
	while ((entryPtr = readdir(dirPtr)))
	{
		if(arg_provided)
		{
			if(arg[1] == 'a')
			{
				printf("%s  ", entryPtr->d_name);
			}
			else if(arg[1] == 'n')
			{
				char file_to_search[256] = {0};
				memcpy(file_to_search, file_path, strlen(file_path));
				(void)strcat(file_to_search, "/");
				(void)strcat(file_to_search, entryPtr->d_name);

				if (stat(file_to_search, &statBuf) < 0) {
					printf("huh?  there is \n");
					exit(1);
				}
				printf("%llu\t", (unsigned long long)statBuf.st_uid);
				printf("%llu\t", (unsigned long long)statBuf.st_gid);
				printf("%llu\t", (unsigned long long)statBuf.st_size);
				printf("%s\n", entryPtr->d_name);
			}
			else if(arg[1] == 'i')
			{
				char file_to_search[256] = {0};
				memcpy(file_to_search, file_path, strlen(file_path));
				(void)strcat(file_to_search, "/");
				(void)strcat(file_to_search, entryPtr->d_name);

				if (stat(file_to_search, &statBuf) < 0) {
					printf("huh?  there is \n");
					exit(1);
				}
				printf("%llu\t", (unsigned long long)statBuf.st_ino);
				printf("%s\n", entryPtr->d_name);
			}
		}
		else
		{
			/* Don't allow hidden files to be displayed. */
			if(entryPtr->d_name[0] == '.')
			{
				continue;
			}
			printf("%s  ", entryPtr->d_name);
		}
	}

	printf("\n");

	/* Close the directory stream. */
	closedir(dirPtr);
	return 0;
}
