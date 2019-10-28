#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#define DMAX 100

int f[DMAX];

void make_pipes();
void parinte();
void fiu1();
void fiu2();

int p0top1[2], p1top2[2], p2top0[2];
FILE *fin, *fout;
char value;

int main(int argc, char *argv[]){
	make_pipes();
	int pid;

	if ((pid = fork()) == -1){
		perror ("Eroare la primul fork: ");
		return -1;
	}

	if (pid){
		if ((pid = fork()) == -1){
			perror ("Eroare la al doilea fork: ");
			return -1;
		}

		if (pid)
			parinte();
		else
			fiu2();
	}
	else
		fiu1();

	return 0;
}

void make_pipes(){
	if (pipe(p0top1) == -1){
		perror ("Eroare la pipe: ");
		exit (-1);
	}

	if (pipe(p1top2) == -1){
		perror ("Eroare la pipe: ");
		exit (-1);
	}

	if (pipe(p2top0) == -1){
		perror ("Eroare la pipe: ");
		exit (-1);
	}
	
	return;
}

void parinte(){
	close (p0top1[0]);
	close (p1top2[0]); close(p1top2[1]);
	close (p2top0[1]);

	fin = fopen ("date.txt", "r");
	fout = fdopen (p0top1[1], "w");

	while (fscanf (fin, "%c", &value) && !feof(fin)){
		fprintf (fout, "%c", value);
		fflush (fout);
	}
	
	fclose (fin);
	fclose (fout);

	fin = fdopen (p2top0[0], "r");
	int rez;
	fscanf (fin, "%d", &rez);
	printf ("Al doilea fiu a returnat %d litere disticte\n", rez);
	fclose (fin);
}

void fiu1(){
	close (p0top1[1]);
	close (p1top2[0]);
	close (p2top0[0]); close (p2top0[1]);
	fin = fdopen (p0top1[0], "r");
	fout = fdopen (p1top2[1], "w");

	while (fscanf (fin, "%c", &value) && !feof (fin)){
		if ('a'<=value && value<='z'){
			fprintf (fout, "%c", value);
			fflush (fout);
		}
	}

	fclose (fin);
	fclose (fout);

	//printf ("Fiu1 a terminat\n");
}

void fiu2(){
	int frecv[100], distincte=0;
	FILE *stats = fopen ("statistica.txt", "w");

	close (p0top1[0]); close (p0top1[1]);
	close (p1top2[1]);
	close (p2top0[0]); 

	fin = fdopen (p1top2[0], "r");
	fout = fdopen (p2top0[1], "w");

	for (int i = 0; i<='z'-'a'; ++i) frecv[i]=0;

	while (fscanf (fin, "%c", &value) && !feof (fin)){
		frecv[value-'a']++;
	}

	for (int i = 0; i<='z'-'a'; ++i)
		if (frecv[i]){
			++distincte;
			fprintf (stats, "%c: %d\n", i+'a', frecv[i]);
		}

	//printf ("Fiu2 urmeaza sa afiseze distincte\n");
	fprintf (fout, "%d", distincte);

	fclose (stats);
	fclose (fin);
	fclose (fout);
	//printf ("Fiu2 a terminat\n");
}
	
