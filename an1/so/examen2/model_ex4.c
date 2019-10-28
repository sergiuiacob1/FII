#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int pipes[4][2];

void parinte();
void fiu1();
void fiu2();
void make_pipes();

int main(){
	int pid;

	make_pipes();
	pid = fork();

	if (pid){
		pid = fork();
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
	int i;
	for (i=0; i<4; ++i)
		pipe(pipes[i]);
}

void parinte(){
	int i, val, sum;

	close (pipes[2][0]); close (pipes[3][1]); close (pipes[0][0]); close (pipes[1][1]);


	while (EOF != scanf ("%d", &val))
		if (val>=0)
			write (pipes[0][1],  &val, 4);
		else
			write (pipes[2][1], &val, 4);

	close (pipes[0][1]);
	close (pipes[2][1]);

	read (pipes[1][0], &sum, 4);
	read (pipes[3][0], &val, 4);
	sum+=val;
	printf ("Suma de la parinte: %d\n", sum);
	
	close (pipes[1][0]);
	close (pipes[3][0]);
}

void fiu1(){
	int i, val, sum = 0;
	
	close (pipes[0][1]); close(pipes[1][0]);
	close (pipes[2][0]); close (pipes[2][1]); close (pipes[3][0]); close (pipes[3][1]);
	
	while (read (pipes[0][0], &val, 4)){
		sum+=val;
	}
	close (pipes[0][0]);

	printf ("Primul fiu a calculat suma: %d\n", sum);
	write (pipes[1][1], &sum, 4);
	close (pipes[1][1]);
	exit(sum);
}

void fiu2(){
	int i, val, sum = 0;

	close (pipes[1][0]); close (pipes[1][1]);
	close (pipes[2][1]); close (pipes[3][0]); close (pipes[0][0]); close (pipes[0][1]);

	while (read(pipes[2][0], &val, 4)){
		sum+=val;
	}
	close (pipes[2][0]);

	printf ("Al doilea fiu a calculat suma: %d\n", sum);
	write (pipes[3][1], &sum, 4);
	exit (sum);

	close (pipes[3][1]);
}
