/*******************************************************************************************************
Enunt a treia problema:

Sa se scrie un program C care va primi ca argument la linia de comanda o valoare numerica N, 
va citi N numere de la tastatura si va calcula suma cifrelor tuturor numerelor impare din secventa, 
implementand urmatorii pasi:
1. procesul initial (P0) va crea un proces fiu P1 si ii va transmite toate numerele impare  
din secventa de numere citita de la tastatura; transmiterea datelor se va realiza prin intermediul 
unui canal de comunicatie anonima;
2. procesul fiu P1 va crea la randul sau un nou proces fiu P2, va calcula suma cifrelor pentru 
fiecare numar primit de la procesul P0 si va transmite valorile calculate procesului P2; 
transmiterea datelor se va realiza prin intermediul unui canal de comunicatie anonima;  
3. procesul P2 va calcula suma numerelor primite de la procesul P1 si va transmite valoarea 
calculata procesului P1 prin intermediul codului de retur (apel exit() sau instructiune return);
4. procesul P1 va transmite procesului P0 valoarea primita de la procesul P2 prin intermediul 
codului de retur (apel exit() sau instructiune return); 
5. procesul P0 va afisa la final valoarea primita de la procesul P1.

OBSERVATIE: Utilizarea de fisiere obisnuite in locul canalelor de comunicatie anonime 
va fi penalizata cu trei puncte. 

NOTA: pastrati enuntul in acest comentariu si scrieti rezolvarea mai jos.
*******************************************************************************************************/

#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int pipe0to1[2], pipe1to2[2];

void parinte(int);
void fiu1();
void fiu2();
void make_pipes();

int main(int argc, char *argv[]) {
	if (argc!=2){
		printf ("Nu ati specificat toti parametrii!\n");
		exit (3);
	}

	if (atoi(argv[1]) < 1){
		printf ("Programul trebuie sa citeasca macar 1 numar!\n");
		exit (4);
	}

	make_pipes();
	parinte(atoi(argv[1]));

	return 0;
}

void make_pipes(){
	if (pipe(pipe0to1) == -1){
		perror ("Eroare la crearea pipe-ului");
		exit (1);
	}

	if (pipe(pipe1to2) == -1){
		perror ("Eroare la crearea pipe-ului");
		exit (1);
	}
}

void parinte(int n){
	int rez, pid, val;

	close (pipe0to1[0]);
	close (pipe1to2[0]); close (pipe1to2[1]);

	if ( (pid = fork()) == -1){
		perror ("Eroare la primul fork");
		exit (2);
	}

	if (pid){
		for (int i = 0; i<n; ++i){
			scanf ("%d", &val);
			//printf ("Parintele a citit %d\n", val);
			if (val%2 == 1)//daca e impar
				if (write (pipe0to1[1], &val, 4) < 0){
					perror ("Eroare la scrierea catre primul fiu");
					exit (5);
				}
		}

		close (pipe0to1[1]);

		wait (&rez);//astept codul de terminare de la fiul 1
		printf ("Parintele a primit de la primul fiu rezultatul: %d\n", rez/256);
	}
	else
		fiu1();

	return;
}

void fiu1(){
	int rez, pid, val, sum;

	close (pipe0to1[1]);
	close (pipe1to2[0]);

	if ( (pid = fork()) == -1){
		perror ("Eroare la cel de-al doilea fork");
		exit (2);
	}

	if (pid){
		//sunt in primul fiu, transmit celui de-al doilea
		while (read(pipe0to1[0], &val, 4) != 0){
			//printf ("Fiul 1 a citit %d\n", val);
			sum = 0;
			while (val){
				sum+=val%10;
				val/=10;
			}

			if (write (pipe1to2[1], &sum, 4) < 0){
				perror ("Eroare la scrierea catre al doilea fiu" );
				exit (5);
			}
		}

		close (pipe0to1[0]);
		close (pipe1to2[1]);

		wait (&rez);//astept rezultatul de la cel de-al doilea fiu
		
		//printf ("Primul fiu a primit de la al doilea fiu: %d\n", rez/256);
		exit (rez/256);

	}
	else
		fiu2();

	return;
}

void fiu2(){
	int val, sum;
	
	close (pipe0to1[0]); close (pipe0to1[1]);
	close (pipe1to2[1]);
	
	sum=0;
	while (read (pipe1to2[0], &val, 4) != 0){
		//printf ("Fiul 2 a citit %d\n", val);
		sum+=val;
	}

	close (pipe1to2[0]);

	exit(sum);
}



