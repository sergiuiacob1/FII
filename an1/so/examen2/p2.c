/****************************************************************************************
Enunt a doua problema:

Programul de mai jos contine trei erori sintactice (adica, detectabile la compilare), si ar trebui sa ofere
urmatoarea functionalitate: Procesul principal creaza un fiu; Procesul fiu scrie in fisierul "fisier.txt"
un nume si un prenume; Procesul parinte citestele prenumele si apoi il afiseaza;

Corectati in programul de mai jos cele trei erori introduse voluntar in asa fel incat sa obtineti un program corect.
Dupa linia pe care ati facut o corectie, includeti si o explicatie ca si comentariu pentru a obtine punctajul integral.


NOTA: pastrati enuntul in acest comentariu si scrieti rezolvarea mai jos.
****************************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>//biblioteca necesara pentru wait()
#include <stdlib.h>//biblioteca necesara pentru system()

int main(int argc, char* argv[])
{

	int pid1;

	pid1 = fork();

	if(pid1 == -1)
	{
		perror("failed to create child process");
		return -1;
	}	

	if(pid1!=0)
	{
		wait(NULL);

		FILE* fisier;

		fisier = fopen("fisier.txt", "r");

		char a[10];

		fseek(fisier, 8, SEEK_SET);//SEEK_SET, nu SEK_SET
		//aici trebuie sa deplasam pointerul de citire pentru a nu citi numele, ci prenumele; SEK_SET nu exista
		//8 in loc de 7, sa sarim si spatul de la "Ionescu "

		fscanf(fisier, "%s", a);
		printf("Prenumele este %s", a);
		fclose(fisier);//fd nu era declarat, descriptorul de fisier este fisier, in acest caz

	}
	else
	{
		system("touch fisier.txt");

		FILE* fd;

		fd = fopen("fisier.txt", "w");

		char* nume = "Ionescu ";
		char* prenume = "Alexandru";
		
		fprintf(fd, "%s", nume);
		fprintf(fd, "%s", prenume);

		fclose(fd);//fclose, nu close; descriptorul de fisier este de tip FILE*, deci necesita functia fclose()
		//close e pentru descriptorii de fisier de tip int
		return 0;
	}

}
