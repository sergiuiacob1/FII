#include <sys/socket.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#define DMAX 1100

bool checkArgs(int, char*[]);
void showStats (char *);

int main(int argc, char *argv[]){
    if (!checkArgs(argc, argv))
        return -1;

    showStats (argv[1]);

    return 0;
}

bool checkArgs(int argc, char *argv[]){
    if (argc != 2){
        printf ("Wrong arguments for mystat!");
        return false;
    }

    return true;
}

void showStats (char *arg){
    struct stat result;
    char time[DMAX], pathToFile[DMAX*2];
    strcpy (pathToFile, arg);
    while (pathToFile[strlen(pathToFile) - 1] == '/'){
        pathToFile[strlen(pathToFile) - 1] = 0;
    }
    if (lstat (pathToFile, &result) == -1){
        perror ("Error at stat call");
        return;
    }
    printf ("Inode: %ld\n", result.st_dev);

    printf ("File size: %ld\n", result.st_size);

    printf ("File permissions: ");
    printf((S_ISDIR(result.st_mode)) ? "d" : "-");
    printf((result.st_mode & S_IRUSR) ? "r" : "-");
    printf((result.st_mode & S_IWUSR) ? "w" : "-");
    printf((result.st_mode & S_IXUSR) ? "x" : "-");
    printf((result.st_mode & S_IRGRP) ? "r" : "-");
    printf((result.st_mode & S_IWGRP) ? "w" : "-");
    printf((result.st_mode & S_IXGRP) ? "x" : "-");
    printf((result.st_mode & S_IROTH) ? "r" : "-");
    printf((result.st_mode & S_IWOTH) ? "w" : "-");
    printf((result.st_mode & S_IXOTH) ? "x" : "-");
    printf ("\n");

    printf ("Time of last access: %s", ctime(&result.st_atime));
    printf ("Time of last modification: %s", ctime(&result.st_mtime));
}
