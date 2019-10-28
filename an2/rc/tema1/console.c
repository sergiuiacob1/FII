#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#define DMAX 256

void removeTrailingChars (char [], const char *);
bool buildCommand (char [], char [], char *[]);
void executeCommand (char [], char *[]);
void setDirectory (int, char *[], char []);
char *strrstr (char *, const char *);
bool isDirectory (const char *);
void simplifyPath (char []);

char pathToExe[DMAX*2];
char pathForCommand[DMAX*2];

int main(int argc, char *argv[]){
    char command[DMAX], s[DMAX];
    char *arguments[DMAX];

    if (readlink ("/proc/self/exe", pathToExe, sizeof (pathToExe)) < 0)
        printf ("Error at readlink\n");

    while (pathToExe[strlen(pathToExe) - 1] != '/')
        pathToExe[strlen(pathToExe) - 1] = 0;

    while (fgets (s, sizeof(s), stdin)){
        removeTrailingChars (s, " \t\r\n");
        if (!strlen (s)) continue;
        if (!buildCommand (s, command, arguments))
            break;
        executeCommand (command, arguments);
    }
    return 0;
}

void removeTrailingChars (char s[], const char *toDelete){
    int lg;
    for (lg = 0; s[lg]; ++lg);

    while (strchr (toDelete, (int)s[lg-1])!= NULL)
        s[--lg] = 0;
}

bool buildCommand (char s[], char command[], char *args[]){
    char *p;
    int argsCount;

    p = strtok (s, " \t");
    strcpy (command, p);
    if (!strcmp (command, "exit"))
        return false;

    args[0] = command;
    argsCount = 1;

    while (p != NULL){
        p=strtok (NULL, " \t");
        args[argsCount++] = p;
    }
    --argsCount;

    setDirectory (argsCount, args, command);

    return true;
}

void executeCommand (char command[], char *args[]){
    int pid;
    printf ("Curent: %s\n", pathToExe);
    printf ("Pt comanda: %s\n", pathForCommand);
    pid = fork();

    if (!pid){
        execvp (command, args);
    }
}

void setDirectory (int argsCount, char *args[], char command[]){
    DIR *dirEntry;

    strcpy (pathForCommand, pathToExe);

    if (argsCount <= 1)
    {
        args[1] = pathForCommand;
        args[2] = NULL;
    }
    else
    {
        if (args[1][0] != '-'){
            if (args[1][0] != '/'){//cale relativa, concatenez
                strcat (pathForCommand, args[1]);

                int lg = strlen (pathForCommand);
                if (pathForCommand[lg-1] != '/'){
                    pathForCommand[lg] = '/';
                    pathForCommand[lg+1] = 0;
                }

                simplifyPath (pathForCommand);

                args[1] = pathForCommand;
                }
            else
                strcpy (pathForCommand, args[1]);
        }
        else
        {
            args[argsCount + 1] = NULL;
            for (int j = argsCount; j > 1; --j)
                args[j] = args[j-1];
            args[1] = pathForCommand;
        }
    }

    if (!strcmp (command, "cd")){
        if (isDirectory (args[1]))
            strcpy (pathToExe, args[1]);
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

bool isDirectory (const char *path){
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
