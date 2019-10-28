#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

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
	int val = 1;

	fdWrite = open (fifo_hi2ho, O_WRONLY);
	fdRead = open (fifo_ho2hi, O_RDONLY);

	for (int i = 1; i<=10; ++i){
		printf ("hi-");
		fflush (stdout);

		val = 1;
		write (fdWrite, &val, 4);
		read (fdRead, &val, 4);//astept
	}

	close (fdWrite);
	close (fdRead);

	return 0;
}
