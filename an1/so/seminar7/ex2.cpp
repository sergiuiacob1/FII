#include <iostream>
#include <sys/stat.h>
#include <vector>
#include <cstring>

using namespace std;

vector <char[]> filesFound;
DIR *dd;
struct dirent *de;

void searchFile (char *fileName, char *currentPath);
void showPaths();
char *concateneaza (const char *, const char *);

int main(int argc, char * argv[], char * env[]){
	if (argc==1){
		printf ("No file name specified!\n");
		return -1;
	}

	searchFile (argv[1], "/home/sergiu/");

	if (!filesFound.size()){
		printf ("File not found!\n");
		return -2;
	}

	showPaths();
	return 0;
}

void showPaths(){
	for (auto i: filesFound)
		printf ("%s\n", i->data());
	return;
}

void searchFile (char *fileName, char *currentPath){
	char *newPath;

	dd = opendir (currentPath);
	if (dd == nullptr){
		printf ("Failed to open directory %s\n", currentPath);
		return;
	}

	while ( (de=readdir(dd)) !=nullptr){
		newPath = concateneaza (currentPath, fileName);
		if (strcmp (fileName, de.d_name) == 0){
			filesFounds.push_back (newPath);
		}
		
		searchFile (fileName, newPath);//cu stat
		delete newPath;
	}

	closedir (currentPath);
	return;
}

char *concateneaza (const char *s1, const char *s2){
	char *result = new char [strlen (s1) + strlen (s2) + 1];
	strcpy (result, s1);
	strcat (result, s2);
	return result;
}
