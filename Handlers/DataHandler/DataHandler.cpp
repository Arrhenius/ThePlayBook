#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE


#include "DataHandler.h"
#include <direct.h>
#include <fcntl.h>



// Solution found:
// https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c

// Might adjust this to something else in the future but for now will be used
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif


// Obtained from:
// https://stackoverflow.com/questions/11238918/s-isreg-macro-undefined

// Windows does not define the S_ISREG and S_ISDIR macros in stat.h, so we do.
// We have to define _CRT_INTERNAL_NONSTDC_NAMES 1 before #including sys/stat.h
// in order for Microsoft's stat.h to define names like S_IFMT, S_IFREG, and S_IFDIR,
// rather than just defining  _S_IFMT, _S_IFREG, and _S_IFDIR as it normally does.
#define _CRT_INTERNAL_NONSTDC_NAMES 1
#include <sys/stat.h>
#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif
#if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif





void LocalDataSave(UserHandler* user)
{
	int fd;
	char path[MAXBUFSZ];
	struct stat dir;
	struct stat file;
	FILE* fp;



	// To handle directory existence stat will be used for now
	// but will later be adjusted to avoid the time-of-check to 
	// time-of-use bug (though I think this issue shouldn't be
	// too pressing given the task this tool is being created
	// for
	// TODO: Create error logger to handle the endless mess that
	// could potentially occur here
	memset(path, 0, sizeof(MAXBUFSZ));

	if (getcwd(path, MAXBUFSZ))
		printf("Current directory: %s\n", path);
	else
	{
		fprintf(stderr, "Failed to obtain current directory\n");
		exit(EXIT_FAILURE);
	}

	// check if path is a director
	// if it doesn't exist, create it
	strcat(path, SAVEDIR);
	if (stat(path, &dir) == 0 && S_ISDIR(dir.st_mode))
	{
		printf("Proceeding to save data...\n");
	}
	else
	{
		if (mkdir(path) == -1)
		{
			fprintf(stderr, "Failed to create directory at path '%s'!\n", path);
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	if (chdir(path) != 0)
	{
		perror("Directory change failed ");

	}
	strcat(path, SAVEFILEWSEP);

	if (stat(SAVEFILE, &file) == 0)
	{
		fp = fopen(SAVEFILE, "rb+");
		if (!fp)
		{
			fprintf(stderr, "Failed to open file %s\n", SAVEFILE);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fp = fopen(SAVEFILE, "wb+");
		if (!fp)
		{
			fprintf(stderr, "Failed to create binary file for reading or writing!\n");
			exit(EXIT_FAILURE);
		}
	}

	if (fp)
	{
		fwrite(user->getUsername(), sizeof(char), MAXNAMESZ, fp);
		fwrite(user->getFirstName(), sizeof(char), MAXNAMESZ, fp);
		fwrite(user->getLastName(), sizeof(char), MAXNAMESZ, fp);
		fwrite(user->getEmail(), sizeof(char), MAXEMAILSZ, fp);
		fwrite(user->getKey(), sizeof(char), MAXKEYSZ, fp);
		fclose(fp);
	}
	else
	{
		fprintf(stderr, "Unable to write to file stream, unexpected error occurred!\n");
		exit(EXIT_FAILURE);
	}




}