#include <cstdio>
#include <fnctl.h>
#include <errno.h>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){
	//program -i/-o depozit.bin instructiuni.dat
	
	int fd, cod, cantitate, fileInstr, codDepozit, cantitateDepozit, startFd;
	struct flock lockDepozit, lockInstr;
	long long int fileSize, fileSizeInstr;
	bool foundCode;

	if (argv<3){
		printf ("Prea putini parametri!\n");
		exit (-1);
	}

	if (strcmp (argv[1], "-o")==0 && argv!=4){
		printf ("Parametri incorecti pentru argumentul -o");
		exit (-1);
	}

	if (strcmp (argv[1], "-i")==0 && argv!=3){
		printf ("Parametri incorecti pentru argumenul -i");
		exit (-1);
	}

	fd = open (argv[2], O_RDWR);
	if (fd == -1) { perror ("Nu s-a putut deschide fisierul!: "); exit (-2); }

	fseek (fd, 0, SEEK_END);
	fileSize = ftell (fd);
	fseek (fd, 0, SEEK_SET);//resetez pointerul

	if (strcmp (argv[1], "-i")==0){
		//lacatul trebuie sa fie pe tot fisierul
		lockDepozit.l_type = F_WRLCK;
		lockDepozit.l_whence = SEEK_SET;
		lockDepozit.l_start = 0;
		lockDepozit.l_len = fileSize;

		if (fcntl (fd, F_SETLKW, &lockDepozit) == -1){
			perror ("Nu s-a putut seta blocajul:");
			exit (-3);
		}

		while (1){
			scanf ("%d %d", &cod, &cantitate);
			if (cod == -1) break;
			fprintf (fd, "%d%d", cod, cantitate);
		}

		//deblochez fisierul		
		lockDepozit.l_type = F_UNLCK;
		if (fcntl (fd, F_SETLCK, &lock) == -1){
			perror ("Nu s-a putut debloca fisierul: ");
			exit (-3);
		}

		return 0;
	}

	//modific cantitatile respective
	fileInstr = open (argv[3], O_RDWR);
	if (fileInstr == -1){
		perror ("Nu s-a putut deschide fisierul cu instructiuni:");
		exit (-2);
	}

	fseek (fileInstr, 0, SEEK_END);
	fileSizeInstr = ftell (fileInstr);
	fseek (fileInstr, 0, SEEK_SET);

	lockInstr.l_type = F_RDLCK;
	lockInstr.l_whence = SEEK_SET;
	lockInstr.l_start = 0;
	lockInstr.l_len = fileSizeInstr;

	fcntl (fileInstr, F_SETLKW, &lockInstr);

	startFd = fd;

	while (1){
		if (fscanf (fileInstr, "%d", &cod) == 0)
			break;
		if (fscanf (fileInstr, "%d", &cantitate) == 0){
			printf ("Fisierul de instructiuni nu este corect!");
			exit (-4);
		}

		fd=startFd;//ma duc inapoi la inceputul fisierului depozit.bin
		//calculez dimensiunea fisierului curent
		fseek (fd, 0, SEEK_END);
		fileSize = ftell (fd);
		fd=startFd; //resetez catre inceput

		//caut codul, setez blocaj si scriu
		lockDepozit.l_type = F_RDLCK;
		lockDepozit.l_whence = SEEK_SET;
		lockDepozit.l_start = 0;
		lockDepozit.len = fileSize;//size-ul pentru depozit
		fcntl (fd, F_SETLKW, &lockDepozit);

		foundCode = false;
		while (1){
			if (fscanf (fd, "%d", &codDepozit) == 0)
				break;//s-a terminat
			fscanf (fd, "%d", &cantitateDepozit);
			if (cod == codDepozit){
				foundCode = true;
				break;
			}
		}

		if (foundCode) cantitate+=cantitateDepozit;
		if (!foundCode && cantitate<0){
			printf ("Fisier de instructiuni invalid!");
			exit (-5);
		}

		//deblochez depozit ca sa pot scrie
		//lockDepozit.l_type = F_UNLCK;
		//fcntl (startFd, F_SETLK, &lockDepozit);
		//deja am blocat tot fisierul!!!!!

		//scriu
		//lockDepozit.l_type = F_WRLCK;
		//lockDepozit.l_whence = SEEK_CUR;
		//lockDepozit.l_start = 0;
		//lockDepozit.l_len = 4;//scriu doar 4 bytes

		//fcntl (fd, F_SETLKW, &lockDepozit);
		if (foundCode)
			fprintf (fd, "%d", cantitate);
		else{
			fd = fseek (fd, 0, SEEK_END);
			fprintf (fd, "%d%d", cod, cantitate);
		}

		//deblochez depozitul
		lockDepozit.l_type = F_UNLCK;
		fcntl (fd, F_SETLK, &lockDepozit);
		
	}
	return 0;
}
