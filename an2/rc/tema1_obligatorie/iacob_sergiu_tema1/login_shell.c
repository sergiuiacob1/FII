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
#define DMAX 11000
#define FIFO_FatherToSon "FIFO_FatherToSon"
#define FIFO_SonToFather "FIFO_SonToFather"
#define FIFO_Son1ToSon2 "FIFO_Son1ToSon2"
#define FIFO_Son2ToSon1 "FIFO_Son2ToSon1"

char commType[DMAX];
char currentPath[DMAX/5], pathForCommand[DMAX/5];
char pathToMyFind[DMAX/5], pathToMyStat[DMAX/5];
int sockp[2], pipe_FatherToSon[2], pipe_SonToFather[2];
int sockSons[2];
int fdFatherWrite, fdFatherRead, fdSonWrite, fdSonRead;
bool loggedIn;

bool checkArgs (int, char *[]);
bool getLine (char []);
void processInputCommand (char []);
bool initialize(char *argv[]);
void makeComm();
void executeCommands(char[], int);
void createFatherFileDescriptors();
void createSonFileDescriptors();
void createCommBetweenSons();
void closeFileDescriptors();
void getCommandResult(char [DMAX*10]);
void login(char []);
void quit();
void removeTrailingChars (char [], const char *);
void fiu1();
void fiu2();
void buildCommand (char[], char *[], char[]);
void setCommandDirectory (int, char *[], char []);
void writeToFileDescriptor (int, char []);
void simplifyPath (char []);
char *strrstr (char *where, const char *what);
bool changeWorkingDirectory (char[]);
void execCommand (char [], char *[]);
void myfind(char [], char *[]);
void mystat(char [], char *[]);

int main(int argc, char *argv[]){
    if (!checkArgs (argc, argv)){
        printf ("Wrong arguments! Please specify as argument what to use: fifo/socket/pipe\n");
        return -1;
    }
    if (!initialize(argv))
        return -1;

    makeComm();

    int pid = fork();
    if (pid == -1){
        printf ("Eroare la fork!\n");
        return -1;
    }

    if (pid){
        char inputCommand [DMAX/5];
        createFatherFileDescriptors();

        while (getLine(inputCommand)){
            if (strcmp (inputCommand, "quit") == 0){
                quit();
                break;
            }
            processInputCommand(inputCommand);
            memset (inputCommand, 0, sizeof(inputCommand));
        }
        write (fdFatherWrite, 0, 4);
    }
    else{
        createSonFileDescriptors();
        fiu1();
    }

    closeFileDescriptors();
    wait(NULL);
    return 0;
}

bool checkArgs (int argc, char *argv[]){
    if (argc != 2)
        return false;
    if (!strcmp (argv[1], "fifo") || !strcmp (argv[1], "pipe")
        || ! strcmp (argv[1], "socket"))
        return true;
    return false;
}

bool getLine (char inputLine[]){
    if ((inputLine = fgets (inputLine, DMAX/5-1, stdin)) == NULL)
        return false;

    removeTrailingChars (inputLine, " \t\r\n");
    return true;
}

void processInputCommand (char inputCommand[]){
    int lg = strlen (inputCommand);
    char answer[DMAX*10];

    if (!lg) return;

    write (fdFatherWrite, &lg, 4);
    write (fdFatherWrite, inputCommand, lg);

    read (fdFatherRead, &lg, 4);
    read (fdFatherRead, answer, lg);
    answer[lg] = 0;

    if (strlen (answer))
        printf ("\n%s\n", answer);
}

bool initialize(char *argv[]){
    getcwd (currentPath, sizeof (currentPath));
    strcpy (pathToMyFind, currentPath);
    strcat (pathToMyFind, "/myfind.bin");
    strcpy (pathToMyStat, currentPath);
    strcat (pathToMyStat, "/mystat.bin");
    strcpy (commType, argv[1]);
    loggedIn = false;
    return true;
}

void fiu1(){
    int lgCommand;
    char command[DMAX/5];
    while (1){
        read (fdSonRead, &lgCommand, 4);
        if (lgCommand == 0)
            return;
        read (fdSonRead, command, lgCommand);
        command[lgCommand] = 0;

        executeCommands (command, lgCommand);
    }
}

void executeCommands (char command[], int lgCommand){
    char answer[DMAX*10];
    int lgAnswer;

    if (strstr (command, "login") == command){
        login(command);
        return;
    }

    if (!loggedIn){
        writeToFileDescriptor (fdSonWrite, "You need to log in.");
        return;
    }

    if (strstr (command, "cd") == command){
        if (changeWorkingDirectory(command) == false)
            writeToFileDescriptor (fdSonWrite, "Wrong arguments for cd");
        else
            writeToFileDescriptor (fdSonWrite, currentPath);
        return;
    }

    int pid = fork();
    if (pid == -1){
        perror ("Fork error");
        exit (-2);
    }

    if (pid){
        //dau comanda la executat
        write (sockSons[1], &lgCommand, 4);
        write (sockSons[1], command, lgCommand);
        //iau raspunsul de la fiu
        getCommandResult(answer);
        lgAnswer = strlen (answer);
        write (fdSonWrite, &lgAnswer, 4);
        write (fdSonWrite, answer, lgAnswer);
    }else
        fiu2();
}

void fiu2(){
    char inputCommand[DMAX/5], command[DMAX/5];
    char *args[DMAX/5];
    int lgInputCommand;
    close (sockSons[1]);

    read (sockSons[0], &lgInputCommand, 4);
    read (sockSons[0], inputCommand, lgInputCommand);
    inputCommand[lgInputCommand] = 0;

    buildCommand (command, args, inputCommand);

    if (strstr (command, "myfind") == command)
        myfind(command, args);
    else
        if (strstr (command, "mystat") == command)
            mystat(command, args);
        else
            execCommand (command, args);
    close (sockSons[0]);
    exit (0);
}

void buildCommand (char command[], char *args[], char inputCommand[]){
    int argsCount;
    char *p;
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
    if (argsCount == 1) return;

    if (args[1][0] != '-') {//asta e nume/cale pt fisier
        if (args[1][0] != '/'){//cale relativa, concatenez
            strcpy (pathForCommand, currentPath);
            strcat (pathForCommand, "/");
            strcat (pathForCommand, args[1]);
            if (pathForCommand[strlen (pathForCommand) - 1] != '/'){
                int lg = strlen (pathForCommand);
                pathForCommand[lg] = '/';
                pathForCommand[lg+1] = 0;
            }

            simplifyPath (pathForCommand);
            if (strlen (pathForCommand) > 1)
                removeTrailingChars(pathForCommand, "/");
            args[1] = pathForCommand;
            }
    }
}

void execCommand (char command[], char *args[]){
    int pid;
    pid = fork();

    if (!pid){
        close (1);
        dup (sockSons[0]);
        close (sockSons[0]);
        execvp (command, args);
        perror ("Error at executing command");
        exit(-1);
    }

    wait(NULL);
}


void makeComm(){
    if (strcmp (commType, "fifo") == 0){
        mknod (FIFO_FatherToSon, S_IFIFO | 0666, 0);
        mknod (FIFO_SonToFather, S_IFIFO | 0666, 0);
    }

    if (strcmp (commType, "pipe") == 0){
        if (pipe(pipe_FatherToSon) == -1){
            perror ("Pipe error");
            exit (-1);
        }

        if (pipe (pipe_SonToFather) == -1){
            perror ("Pipe error");
            exit (-1);
        }
    }

    if (strcmp (commType, "socket") == 0){
        if (socketpair (AF_UNIX, SOCK_STREAM, 0, sockp) < 0){
            perror ("Socket error");
            exit (-1);
        }
    }

    createCommBetweenSons();
}

void createFatherFileDescriptors(){
    if (strcmp (commType, "fifo") == 0){
        fdFatherRead = open (FIFO_SonToFather, O_RDONLY);
        fdFatherWrite = open (FIFO_FatherToSon, O_WRONLY);
    }

    if (strcmp (commType, "pipe") == 0){
        fdFatherRead = pipe_SonToFather[0];
        fdFatherWrite = pipe_FatherToSon[1];
        close (pipe_SonToFather[1]);
        close (pipe_FatherToSon[0]);
    }

    if (strcmp (commType, "socket") == 0){
        fdFatherRead = sockp[1];
        fdFatherWrite = sockp[1];
        close (sockp[0]);
    }
}

void createSonFileDescriptors(){
    if (strcmp (commType, "fifo") == 0){
        fdSonWrite = open (FIFO_SonToFather, O_WRONLY);
        fdSonRead = open (FIFO_FatherToSon, O_RDONLY);
    }

    if (strcmp (commType, "pipe") == 0){
        fdSonRead = pipe_FatherToSon[0];
        fdSonWrite = pipe_SonToFather[1];
        close (pipe_FatherToSon[1]);
        close (pipe_SonToFather[0]);
    }

    if (strcmp (commType, "socket") == 0){
        fdSonRead = sockp[0];
        fdSonWrite = sockp[0];
        close (sockp[1]);
    }
}

void closeFileDescriptors(){
    close (fdFatherWrite);
    close (fdFatherRead);
    close (fdSonWrite);
    close (fdSonRead);

    close (sockSons[0]);
    close (sockSons[1]);
}

void createCommBetweenSons(){
    if (socketpair (AF_UNIX, SOCK_STREAM, 0, sockSons) < 0){
        perror ("Socket error for sons");
        exit (-1);
    }

    //fiu1 trebuie sa citeasca in mod neblocant de la fiu 2
    int flags = fcntl (sockSons[1], F_GETFL);
    flags |= O_NONBLOCK;
    fcntl (sockSons[1], F_SETFL, flags);
    return;
}

void quit(){
    printf ("Quitting application\n");
}

void login(char command[]){
    FILE*fin = fopen ("users.txt", "r");
    char *p, line[DMAX/5], userAndPass[DMAX/5];

    if (loggedIn){
        writeToFileDescriptor (fdSonWrite, "Already logged in!");
        return;
    }

    removeTrailingChars (command, " \t\r\n");
    p = strtok (command, " \t"); p = strtok (NULL, " \t");
    if (p == NULL){
        writeToFileDescriptor (fdSonWrite, "Wrong arguments!");
        return;
    }
    strcpy (userAndPass, p); strcat (userAndPass, " ");
    p = strtok (NULL, " \t");
    if (p == NULL){
        writeToFileDescriptor (fdSonWrite, "Wrong arguments!");
        return;
    }
    strcat (userAndPass, p);
    p = strtok (NULL, " \t");
    if (p != NULL){
        writeToFileDescriptor(fdSonWrite, "Too many arguments for login!");
        return;
    }

    while (fgets (line, DMAX/5, fin)){
        removeTrailingChars (line, " \t\r\n");
        if (strcmp (userAndPass, line) == 0){
            loggedIn = true;
            break;
        }
    }

    if (loggedIn){
        writeToFileDescriptor (fdSonWrite, "Successfully logged in!");
        return;
    }
    writeToFileDescriptor (fdSonWrite, "Failed to log in!");
}

void removeTrailingChars (char s[], const char *toDelete){
    int lg;
    for (lg = 0; s[lg]; ++lg);

    while (strchr (toDelete, (int)s[lg-1])!= NULL)
        s[--lg] = 0;
}

void getCommandResult(char answer[DMAX*10]){
    int lgAnswer;
    wait(NULL);
    answer[0] = 0;
    lgAnswer = read (sockSons[1], answer, DMAX*10);//citesc in mod neblocant
    if (lgAnswer >= 0)
        answer[lgAnswer] = 0;
}

void writeToFileDescriptor (int fd, char str[]){
    int lg = strlen (str);
    write (fd, &lg, 4);
    write (fd, str, lg);
}

void simplifyPath (char path[]){
    char *aux, *aux2;

    while (1){// "../" la final
        aux = strstr (path, "../");
        if (aux && (aux - path) >= 3){
            for (aux2 = aux - 2; aux2 != path; --aux2)
                if (*aux2 == '/') break;
            *(aux2 + 1) = 0;
            strcat (path, aux+3);
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

bool changeWorkingDirectory (char command[]){
    char *p = strtok (command, " \t");
    char newPath[DMAX];

    strcpy (newPath, currentPath);
    strcat (newPath, "/");
    p = strtok (NULL, " \t");

    if (p){
        if (*p != '/')
            strcat (newPath, p);
        else
            strcpy (newPath, p);
    }

    if (chdir (newPath) == -1)
        return false;

    getcwd (currentPath, sizeof(currentPath));
    return true;
}

void myfind(char command[], char *args[]){
    int pid;
    pid = fork();

    if (!pid){
        close (1);
        dup (sockSons[0]);
        close (sockSons[0]);
        execvp (pathToMyFind, args);
        exit(-1);
    }

    wait(NULL);
}

void mystat(char command[], char *args[]){
    int pid;
    pid = fork();

    if (!pid){
        close (1);
        dup (sockSons[0]);
        close (sockSons[0]);
        execvp (pathToMyStat, args);
        exit(-1);
    }

    wait(NULL);
}
