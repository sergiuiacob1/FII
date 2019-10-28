#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#define DMAX 110
#define FIFO_Son1ToSon2 "FIFO_Son1ToSon2"
#define FIFO_Son2ToSon1 "FIFO_Son2ToSon1"

char pathToExe[DMAX*2];
char pathForCommand[DMAX*2];
bool loggedIn;
int fdSon2Read, fdSon2Write;

void processInputCommand (char []);
void executeCommand (char [], char *[]);
void buildCommand (char [], char *[], char []);
void removeTrailingChars (char [], const char *);
void setCommandDirectory (int, char *[], char []);
bool isDirectory (const char *);
bool initialize(char *argv[]);
bool checkArgs (int, char*[]);
char *strrstr (char *, const char *);
void simplifyPath (char []);
void buildInputCommand (int, char *[], char []);
void createFileDescriptors();

int main(int argc, char *argv[]){
    if (!checkArgs (argc, argv)){
        printf ("Wrong arguments for second son!\n");
        return -1;
    }

    if (!initialize(argv))
        return -1;

    char inputCommand[DMAX*2];
    buildInputCommand (argc, argv, inputCommand);

    processInputCommand (inputCommand);
}

bool checkArgs (int argc, char *argv[]){
    if (argc < 2)
        return false;
    return true;
}

void buildInputCommand (int argc, char *argv[], char inputCommand[]){
    strcpy (inputCommand, argv[1]);
    removeTrailingChars (inputCommand, " \t\r\n");
    for (int i = 2; i < argc; ++i){
        strcat (inputCommand, " ");
        strcat (inputCommand, argv[i]);
    }
    removeTrailingChars (inputCommand, " \t\r\n");
}

void processInputCommand (char inputCommand[]){
    char command[DMAX];
    char *args[DMAX];

    buildCommand(command, args, inputCommand);

    int fd = open ("test.out", O_WRONLY);
    for (int i = 0; args[i] != NULL; ++i){
        write (fd, args[i], strlen(args[i]));
        write (fd, "\n", 1);
    }
    close (fd);
    if (strcmp (command, "cd"))
        executeCommand (command, args);
}

void buildCommand (char command[], char *args[], char inputCommand[]){
    char *p;
    int argsCount;

    p = strtok (inputCommand, " \t");
    strcpy (command, p);
    args[0] = command;
    argsCount = 1;

    while (p != NULL){
        p = strtok (NULL, " \t");
        args[argsCount++] = p;
    }
    --argsCount;

    setCommandDirectory (argsCount, args, command);
}

void setCommandDirectory (int argsCount, char *args[], char command[]){
    strcpy (pathForCommand, pathToExe);

    if (argsCount <= 1){
        args[1] = pathForCommand;
        args[2] = NULL;
        return;
    }

    if (args[1][0] != '-') {//asta e nume/cale pt fisier
        if (args[1][0] != '/'){//cale relativa, concatenez
            strcat (pathForCommand, args[1]);
            removeTrailingChars(pathForCommand, "/");

            int lg = strlen (pathForCommand);
            pathForCommand[lg] = '/';
            pathForCommand[lg+1] = 0;

            simplifyPath (pathForCommand);
            }
        else
            strcpy (pathForCommand, args[1]);
    }
    else {
        args[argsCount + 1] = NULL;
        for (int j = argsCount; j > 1; --j)
            args[j] = args[j-1];
    }

    removeTrailingChars (pathForCommand, "/");
    args[1] = pathForCommand;

    if (!strcmp (command, "cd")){
        if (isDirectory (pathForCommand))
            strcpy (pathToExe, pathForCommand);
    }
}

void executeCommand (char command[], char *args[]){
    int pid;
    pid = fork();

    if (!pid){
        execvp (command, args);
        exit(-1);
    }

    wait(NULL);
}

void removeTrailingChars (char s[], const char *toDelete){
    int lg;
    for (lg = 0; s[lg]; ++lg);

    while (strchr (toDelete, (int)s[lg-1])!= NULL)
        s[--lg] = 0;
}

bool initialize(char *argv[]){
    if (readlink ("/proc/self/exe", pathToExe, sizeof (pathToExe)) < 0){
        printf ("Error at readlink\n");
        return false;
    }
    while (pathToExe[strlen(pathToExe) - 1] != '/')
        pathToExe[strlen(pathToExe) - 1] = 0;

    loggedIn = false;
    return true;
}

void logout(){
    if (loggedIn){
        loggedIn = false;
        write (1, "Logging out...\n", 14);
    }
    else
        write (1, "You are not logged in!\n",
                strlen ("You are not logged in!\n"));
    return;
}

void quit(){
    write (1, "Buh-bye!", 8);
    exit (0);
}

bool isDirectory (const char *path){
    if (path == NULL) return false;

    DIR *dirEntry;
    dirEntry = opendir (path);
    if (dirEntry != NULL) {
        closedir (dirEntry);
        return true;
    }
    return false;
}

void simplifyPath (char path[]){
    char *aux;

    while (1){// "../" la final
        aux = strrstr (path, "../");
        if (aux && *(aux + strlen ("../")) == 0){
            *(aux - 1) = 0;
            aux = strrstr (path, "/");
            *(aux + 1) = 0;
        }
        else
            break;
    }

    while (1){ // "./" redundante la final
        aux = strrstr (path, "./");
        if (aux && *(aux + strlen ("./")) == 0){
            *aux = 0;
        }
        else
            break;
    }

    return;
}

char *strrstr (char *where, const char *what){
    int lg;
    for (lg = strlen (where) - 1; lg>=0; --lg)
        if (strstr (where+lg, what))
            return (where+lg);
    return NULL;
}

void createFileDescriptors (){
    fdSon2Write = open (FIFO_Son2ToSon1, O_WRONLY);
    fdSon2Read = open (FIFO_Son1ToSon2, O_RDONLY);
}
