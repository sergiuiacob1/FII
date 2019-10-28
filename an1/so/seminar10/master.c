#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define DMAX 10

//using namespace std;

void intToChar (int a, char arg[]){
	int nrc=0, ca;
	if (a==0) nrc=1;

	ca=a;
	while (a){
		nrc++;
		a/=10;
	}

	//arg = (char*) malloc(nrc+1);
	arg[nrc]=0;
	for (int i=nrc-1; i>=0; --i, ca/=10)
		arg[i]=ca%10 + '0';
}

int main(){
	int a, b, rez;
	char op, arg1[DMAX], arg2[DMAX], arg3[3];
	pid_t pid_fiu;

	//arg3 = (char *) malloc(2);
	arg3[1]=0;

	while (1){
		scanf("%d %d", &a, &b);
		if (a==0 && b==0) break;
		scanf(" %c", &op);
		arg3[0]=op;

		intToChar (a, arg1);
		intToChar (b, arg2);
		//printf ("a este: %s\n", arg1);
		//printf ("b este: %s\n", arg2);
		//printf ("Am citit: %c\n", arg3[0]);

		if ((pid_fiu = fork()) == -1){
			perror ("Nu s-a reusit crearea fiului: ");
			return -1;
		}

		if (pid_fiu != 0){
			wait (&rez);
			printf ("%d\n", rez/256);
		}
		else{//fiu
			if (execl ("slave.exe", "slave.exe", arg1, arg2, arg3, NULL) == -1){
				perror ("Nu s-a reusit apelarea slave.exe: ");
				return -2;
			}
		}

		//free(arg1);
		//free(arg2);
	}

	//free(arg3);
	return 0;
}
