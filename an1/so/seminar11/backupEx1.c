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

int main(int argc, char *argv[]){
	int p[2], pidFirst, pidSecond, rez = 0;
	char value;

	p[0] = fileno(stdin);
	p[1] = fileno(stdout);

	FILE*fin = fdopen (p[0], "r");
	FILE*fout = fdopen (p[1], "w");

	if (-1 == pipe(p)){
		perror ("Eroare la pipe: ");
		return -1;
	}

	if ((pidFirst = fork()) == -1){
		perror ("Eroare la fork: ");
		return -2;
	}

	if (pidFirst){
		//fclose (fin);
		fin = fopen ("date.txt", "r");

		while (fscanf (fin, "%c", &value) && !feof (fin)){
			fprintf (fout, "%c", value);
			fflush (fout);
		}
		
		fclose (fin);

		waitpid (pidFirst, &rez, WUNTRACED);
		printf ("Al doilea fiu a returnat %d litere distincte\n", rez);
		fclose (fout);
	}
	else{
		//primul fiu, citesc din pipe
		if ((pidSecond = fork()) == -1){
			perror ("Eroare la al doilea fork: ");
			return -2;
		}
		
		if (pidSecond){
			while (fscanf (fin, "%c", &value) && !feof (fin)){
				if ('a'<=value && value<='z'){
					fprintf (fout, "%c", value);
					fflush (fout);
				}
			}
		fclose (fout);

		waitpid (pidSecond, &rez, WUNTRACED);
		printf ("Fiul 1: %d\n", rez);
		exit(rez);
		}
		else {
			//face aparitiile
			int distincte = 0;

			//fclose(fin);//TEST
			//exit (1);//TEST

			fout = fopen ("statistica.txt", "w");

			while (fscanf (fin, "%c", &value) && !feof(fin)){
				f[value-'a']++;
				printf ("Al doilea fiu a citit: %c\n", value);
			}
			fclose (fin);

			for (int i=0; i<'z'-'a'; ++i)
				if (f[i]){
					fprintf (fout, "%c %d\n", i+('z'-'a'), f[i]);
					distincte++;
				}

			fclose (fout);
			printf ("fiul 2: %d\n", distincte);
			exit (distincte);
			}
		}
	
	return 0;
}
