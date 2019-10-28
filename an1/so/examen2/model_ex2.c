#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

char *args[5] = { "/bin/cat", "-n", "-E", "./ceva.txt", 0};

int main(){
	int pid, rez;

	pid = fork();

	if (pid){
		pid = wait(&rez);
		printf ("Fiul %d a returnat: %d\n", pid, rez);
	}
	else {
	//fiu
	execvp ("/bin/cat", args);
	}
	return 0;
}
