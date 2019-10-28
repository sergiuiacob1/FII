#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

char *fifo = "test";

int main(){

	if (-1 == mkfifo (fifo, 0600)){
		if (errno != EEXIST){
			perror("Eroare la fifo");
			exit (1);
		}
	}

	int fdWrite = open (fifo, O_RDWR | O_NONBLOCK);
	char val = 0;
	int cap = 0;
	
	while (1){
		if (write (fdWrite, &val, 1) <= 0)
			break;
		++cap;
		if (cap%1024 == 0){
			printf ("%d KB\n", cap/1024);
			fflush (stdout);
			}
	}

	printf ("Am scris %d\n", cap);

	close (fdWrite);
	
	return 0;
}
