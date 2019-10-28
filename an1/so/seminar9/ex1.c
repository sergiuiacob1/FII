#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#define DMAX 100

//using namespace std;

int main(){
	pid_t pid_fecior;
	int flag_comunicare;
	FILE *filePointerComunicare, *filePointer;
	char replica[DMAX];

	if ((pid_fecior=fork()) == -1){
		perror ("Fork error!: ");
		return -1;
	}

	/*if (filePointerComunicare == NULL)
	{
		perror ("Eroare la deschiderea fisierului comunicare.txt");
		return -2;
	}*/
	//0 fiu, 1 parinte, 2 s-a terminat unul dintre fisiere

	if (pid_fecior == 0){
		//sunt in fiu
		filePointer = fopen ("fiu.txt", "r");
		if (filePointer == NULL)
		{
			perror ("Eroare la deschiderea fisierului fiu.txt");
			return -2;
		}

		do {
			do {
				filePointerComunicare = fopen ("comunicare.txt", "r");
				//fseek (filePointerComunicare, 0, SEEK_SET);
				fscanf (filePointerComunicare, "%d", &flag_comunicare);
				fclose (filePointerComunicare);
			} while (flag_comunicare==1);
			//fclose(filePointerComunicare);

			//a venit randul meu, ori 0 ori 2
			filePointerComunicare = fopen ("comunicare.txt", "w");
			do {
				if (feof(filePointer) || fgets (replica, 99, filePointer)==NULL){//nu am citit nimic
					//fseek (filePointerComunicare, 0, SEEK_SET);
					fprintf (filePointerComunicare, "2\n");//eu am terminat
					fclose (filePointer);
					fclose (filePointerComunicare);
					//fflush (filePointerComunicare);
					fflush (stdout);
					return 0;//gata
				}

				printf ("%s\n", replica);
			} while (flag_comunicare==2);
		
			if (flag_comunicare!=2){//parintele mai are replici
				//fseek (filePointerComunicare, 0, SEEK_SET);
				fprintf (filePointerComunicare, "1\n");//e randul lui tata
				fflush (filePointerComunicare);
				fclose (filePointerComunicare);
			}

		} while (1);
	}
	else{
		filePointer = fopen ("parinte.txt", "r");
		if (filePointer == NULL){
			perror ("Eroare la deschiderea fisierului parinte.txt");
			return -2;
		}

		do{

			do {
				filePointerComunicare = fopen ("comunicare.txt", "r");
				//fseek (filePointerComunicare, 0, SEEK_SET);
				fscanf (filePointerComunicare, "%d", &flag_comunicare);
				fclose (filePointerComunicare);
			} while (flag_comunicare == 0);//cat timp e randul feciorului

			//fclose(filePointerComunicare);
			filePointerComunicare = fopen ("comunicare.txt", "w");
			do {
				if (feof(filePointer) || fgets (replica, 99, filePointer) == NULL){
					//fseek (filePointerComunicare, 0, SEEK_SET);
					fprintf (filePointerComunicare, "2\n");//eu am terminat
					fclose (filePointer);
					fclose (filePointerComunicare);
					//fflush (filePointerComunicare);
					fflush (stdout);
					return 0;//inchei procesul
				}

				printf ("%s\n", replica);
			} while (flag_comunicare == 2);

			if (flag_comunicare!=2){//feciorul mai are de vorbit
				//fseek (filePointerComunicare, 0, SEEK_SET);
				fprintf (filePointerComunicare, "0\n");
				fflush (filePointerComunicare);
				fclose (filePointerComunicare);
			}

		} while (1);
	}
	return 0;
}
