#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char *fifo_hi2ho = "fifo_hi2ho";
char *fifo_ho2hi = "fifo_ho2hi";

int main(){

	if (-1 == mkfifo (fifo_hi2ho, 0600)){
		if (errno == EEXIST){
			printf ("Fifo deja exista\n");
			//exit (2);
		}
		else{
			perror ("Fifo imposibil");
			exit (1);
		}
	}
	if (-1 == mkfifo (fifo_ho2hi, 0600)){
		if (errno == EEXIST){
			printf ("Fifo deja exista!\n");
			//exit (2);
		}
		else {
			perror ("Fifo imposibil");
			exit (1);
		}
	}

	int fdWrite, fdRead;
	int val;

	fdRead = open (fifo_hi2ho, O_RDONLY);
	fdWrite = open (fifo_ho2hi, O_WRONLY);

	for (int i = 1; i<=10; ++i){
		if (read (fdRead, &val, 4) == 0){
			printf ("ho nu a citit nik\n");
		}

		printf ("ho\n");
		fflush (stdout);

		val = 1;
		write (fdWrite, &val, 4);
	}

	close (fdRead);
	close (fdWrite);

	return 0;
}
