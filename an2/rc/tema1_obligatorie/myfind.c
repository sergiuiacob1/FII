#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#define DMAX 1000

struct dirent *de;
char pathToMyStat[DMAX], path[DMAX];

void searchFile (char *fileName, char *currentPath);
char *concateneaza (const char *, const char *);
bool initialize(int, char *[]);
void showStats (char *);
void printInfoAboutFile (char *);
bool symbolicLink (char *);

int main(int argc, char * argv[]){
    if (argc<2){
        write (1, "Not all arguments were specified!\n", strlen ("Not all arguments were specified!\n"));
        return -1;
    }

    if (!initialize(argc, argv))
        return -1;

    DIR *dd;
    dd = opendir (path);
    if (dd == NULL){
        perror ("myfind error");
        return -1;
    }

    searchFile (argv[2], path);
    return 0;
}

void searchFile (char *fileName, char *currentPath){
	char *newPath;
    DIR *dd;

	dd = opendir (currentPath);
	if (dd == NULL)
		return;

	while ( (de=readdir(dd)) != NULL){
        if (strcmp (de->d_name, ".") == 0 || strcmp (de->d_name, "..") == 0) continue;
		newPath = concateneaza (currentPath, de->d_name);
		if (strstr (de->d_name, fileName) != NULL){
            printInfoAboutFile (newPath);
		}

        if (!symbolicLink (newPath))
    		searchFile (fileName, newPath);
        free (newPath);
	}

	closedir (dd);
	return;
}

char *concateneaza (const char *s1, const char *s2){
    char *result = malloc (strlen (s1) + strlen (s2) + 2);
    int lg;
	strcpy (result, s1);
	strcat (result, s2);
    lg = strlen (result);
    result[lg] = '/';
    result[lg+1] = 0;
	return result;
}

bool initialize (int argc, char *argv[]){
    strcpy (path, argv[1]);
    if (path[strlen (path) - 1] != '/'){
        int lg = strlen (path);
        path[lg] = '/';
        path[lg+1] = 0;
    }

    if (readlink ("/proc/self/exe", pathToMyStat, sizeof (pathToMyStat)) < 0){
        perror ("Error at readlink");
        return false;
    }

    char *p = strrchr (pathToMyStat, '/');
    *(p+1) = 0;
    strcat (pathToMyStat, "mystat.bin");

    return true;
}

void showStats (char *pathToFile){
    char *args[3];
    int pid = fork();
    if (pid == -1){
        perror ("Error at fork");
        exit(0);
    }

    if (!pid){
        args[0] = pathToMyStat;
        args[1] = pathToFile;
        args[2] = NULL;
        execvp (pathToMyStat, args);
        perror ("Error at mystat call from myfind");
        exit (-1);
    }

    wait(NULL);
}

void printInfoAboutFile (char *pathToFile){
    write (1, "\nFound a new file ", strlen("\nFound a new file "));
    write (1, pathToFile, strlen (pathToFile));
    write (1, "\n", 1);
    fflush (stdout);
    showStats(pathToFile);
}

bool symbolicLink (char *pathToFile){
    pathToFile [strlen(pathToFile) - 1] = 0;
    struct stat result;
    if (lstat (pathToFile, &result) == -1){
        perror ("Error at lstat call");
        pathToFile[strlen(pathToFile)] = '/';
        return true;
    }

    pathToFile[strlen(pathToFile)] = '/';

    if (S_ISLNK (result.st_mode))
        return true;

    return false;
}
