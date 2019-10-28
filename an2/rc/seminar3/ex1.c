#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define PMAX 7

int count;

int main(){
    int pid;

    printf ("Tatal: A\n");

    while (count < PMAX){
        pid = fork();
        ++count;
        if (!pid) {//fiul
            printf ("Fiul nr. %d: %c\n", count, (char)('A' + count));
        }
        else
            break;
    }

    while (wait(NULL) != -1);
    return 0;
}

