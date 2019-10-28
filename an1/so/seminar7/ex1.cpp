#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int frecv[300];
char *fileName, caracter;
int fileDescriptor, rezRead;

int main(int argc, char *argv[], char* env[]){
	fileName = argv[1];
	fileDescriptor = open (fileName, O_RDONLY);
	if (fileDescriptor == -1){
		cout << "Nu s-a putut deschide fisierul!\n";
		return 0;
	}

	/*do{
		read (fileDescriptor, &caracter, 1);
		++frecv[(int)caracter];
	} while (lseek (fileDescriptor, 1, SEEK_CUR));*/

	while (1){
		rezRead = read (fileDescriptor, &caracter, 1);
		if (rezRead == 0 || rezRead == -1)
			break;
		++frecv[(int)caracter];
		//lseek (fileDescriptor, 1, SEEK_CUR);
		printf ("Am citit %c\n", caracter);
	}

	for (int i=0; i<256; ++i)
		if (frecv[i])
			printf ("Caracterul %c apare de %d ori\n", char (i), frecv[i]);
	
	return 0;
}
