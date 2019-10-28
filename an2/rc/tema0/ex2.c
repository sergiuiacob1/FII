#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

struct dirent *de;

void searchFile (char *fileName, char *currentPath);
char *concateneaza (const char *, const char *);

int main(int argc, char * argv[], char * env[]){
	if (argc<2){
		printf ("Not all arguments were specified!\n");
		return -1;
	}

	searchFile (argv[2], argv[1]);

	return 0;
}

void searchFile (char *fileName, char *currentPath){
	char *newPath;
    DIR *dd;

	dd = opendir (currentPath);
	if (dd == NULL){
		//printf ("Failed to open directory %s\n", currentPath);
		return;
	}

	while ( (de=readdir(dd)) != NULL){
        if (strcmp (de->d_name, ".") == 0 || strcmp (de->d_name, "..") == 0) continue;
		newPath = concateneaza (currentPath, de->d_name);
        //printf ("Sunt in: %s\n", newPath);
		if (strstr (de->d_name, fileName) != NULL){
            printf ("Found a new file %s\n", newPath);
		}

		searchFile (fileName, newPath);//cu stat
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
