#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#define DMAX 100

int main(int argc, char *argv[]){
	char *dirName, arg1[10];
	char *args[5];
	char pathRm[10]="/bin/rm";
	int opt;
	pid_t pid_fiu;

	if (argc!=2){
		dirName = (char *) malloc(100);
		scanf ("%s", dirName);
		//printf("Nu au fost specificati parametri corecti!\n");
		//return -1;
	}
	else
		dirName = argv[1];

	printf ("Am primit directorul: %s\n", dirName);

	//ls -l dirName
	if ((pid_fiu = fork()) == -1){
		perror ("Nu s-a putut crea fiul:" );
		return -2;
	}

	if (pid_fiu == 0){
		arg1[0]='-'; arg1[1]='l'; arg1[2]=0;
		execlp("/bin/ls", "ls.exe", arg1, dirName, NULL);
	}
	else{
		//sterg?
		printf ("Sterg continutul directorului? 0 pentru NU, 1 pentru DA:\n");
		scanf ("%d", &opt);

		if (opt){
			arg1[0]='-'; arg1[1]='r'; arg1[2]=0;

			if ((pid_fiu = fork()) == -1){
				perror ("Nu s-a putut crea fiul:");
			}

			if (pid_fiu == 0){
				args[0]=pathRm;
				args[1]=arg1;
				args[2]=dirName;
				args[3]=NULL;
				execv ("/bin/rm", args);//rm -r dirName
			}
		}
	}

	if (argc!=2) free(dirName);
	
	if (pid_fiu!=0){
		printf ("DONE\n");
	}
	return 0;
}
