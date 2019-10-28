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
#define DMAX 110
#define FIFO_FatherToSon "FIFO_FatherToSon"
#define FIFO_SonToFather "FIFO_SonToFather"
#define FIFO_Son1ToSon2 "FIFO_Son1ToSon2"
#define FIFO_Son2ToSon1 "FIFO_Son2ToSon1"

char commType[DMAX];
char pathToExe[DMAX*2];
char pathToSon2[DMAX*2];
int sockp[2], pipe_FatherToSon[2], pipe_SonToFather[2];
int pipe_Son2ToSon1[2];
int fdFatherWrite, fdFatherRead, fdSonWrite, fdSonRead;
int fdSon1ToSon2Write, fdSon2ToSon1Read;
bool loggedIn;

bool checkArgs (int, char *[]);
bool getLine (char []);
void processInputCommand (char []);
bool initialize(char *argv[]);
void makeComm();
void executeCommands();
void createFatherFileDescriptors();
void createSonFileDescriptors();
void createCommBetweenSons();
void closeFileDescriptors();
void getCommandResult(char []);
void login(char []);
void quit();
void removeTrailingChars (char [], const char *);

int main(int argc, char *argv[]){
    if (!checkArgs (argc, argv)){
        printf ("Wrong arguments!\n");
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
        char inputCommand [DMAX*2];
        createFatherFileDescriptors();

        while (getLine(inputCommand)){
            removeTrailingChars(inputCommand, " \t\r\n");
            if (strcmp (inputCommand, "quit") == 0){
                quit();
                break;
            }
            processInputCommand(inputCommand);
            inputCommand[0] = 0;
        }

        write (fdFatherWrite, 0, 4);
    }
    else{
        createSonFileDescriptors();
        while (1) executeCommands();
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
    if ((inputLine = fgets (inputLine, DMAX-1, stdin)) == NULL)
        return false;
    return true;
}

void processInputCommand (char inputCommand[]){
    int lg = strlen (inputCommand);
    char answer[DMAX*2];
    write (fdFatherWrite, &lg, 4);
    write (fdFatherWrite, inputCommand, lg);

    read (fdFatherRead, &lg, 4);
    read (fdFatherRead, answer, lg);

    printf ("%s\n", answer);
}

bool initialize(char *argv[]){
    if (readlink ("/proc/self/exe", pathToExe, sizeof (pathToExe)) < 0){
        printf ("Error at readlink\n");
        return false;
    }
    while (pathToExe[strlen(pathToExe) - 1] != '/')
        pathToExe[strlen(pathToExe) - 1] = 0;

    strcpy (pathToSon2, pathToExe);
    strcat (pathToSon2, "server.bin");

    strcpy (commType, argv[1]);
    return true;
}

void executeCommands (){
    char command[DMAX*2], answer[DMAX];
    int lgCommand, lgAnswer;
    read (fdSonRead, &lgCommand, 4);
    if (lgCommand == 0){
        closeFileDescriptors();
        exit(0);
    }
    read (fdSonRead, command, lgCommand);

    if (strstr (command, "login") == command){
        login(command);
        return;
    }

    int pid = fork();
    if (pid == -1){
        perror ("Fork error");
        exit (-2);
    }

    if (pid){
        getCommandResult(answer);
        lgAnswer = strlen (answer);
        write (fdSonWrite, &lgAnswer, 4);
        write (fdSonWrite, answer, lgAnswer);
    }else{
        //printf ("Am trimis comanda %s\n", command);
        /*close (1);
        close (pipe_Son2ToSon1[0]);
        dup (pipe_Son2ToSon1[1]);
        if (execl (pathToSon2, "server.bin", command, NULL) < 0)
            perror ("Error at executing command");
        close (pipe_Son2ToSon1[1]);*/
        write (fdSon1ToSon2Write, &lgCommand, 4);
        write (fdSon1ToSon2Write, command, lgCommand);
        exit (-1);
    }
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
    close (pipe_Son2ToSon1[0]);
    close (pipe_Son2ToSon1[1]);

    close (fdSon2ToSon1Read);
    close (fdSon1ToSon2Write);
}

void createCommBetweenSons(){
    /*if (pipe(pipe_Son2ToSon1) == -1){
        perror ("Error at pipe between sons");
        exit (-4);
    }

    //de la fiul 2 o sa citesc in mod neblocant
    int flags;
    flags = fcntl (pipe_Son2ToSon1[0], F_GETFL);
    flags |= O_NONBLOCK;
    fcntl (pipe_Son2ToSon1[0], F_SETFL, flags);*/

    mknod (FIFO_Son1ToSon2, S_IFIFO | 0666, 0);
    mknod (FIFO_Son2ToSon1, S_IFIFO | 0666, 0);

    fdSon2ToSon1Read = open (FIFO_Son2ToSon1, O_RDONLY);
    fdSon1ToSon2Write = open (FIFO_Son1ToSon2, O_WRONLY);
    return;
}

void getCommandResult(char answer[]){
    int lg = 0;
    answer[0] = 0;
    wait(NULL);
    lg = read (pipe_Son2ToSon1[0], answer, DMAX);
    if (lg > 0) answer[lg-1] = 0;
    printf ("Fiu 1 citit de la fiu 2\n");
    //DACA CITESC CARACTER CU CARACTER NU MERGE DE CE?!
}

void quit(){
    printf ("Quitting application\n");
}

void login(char command[]){
    FILE*fin = fopen ("users.txt", "r");
    char *p, line[DMAX], userAndPass[DMAX], son1Answer[DMAX];
    int lgAnswer;

    if (loggedIn){
        strcpy (son1Answer, "Already logged in!");
        lgAnswer = strlen (son1Answer);
        write (fdSonWrite, &lgAnswer, 4);
        write (fdSonWrite, son1Answer, lgAnswer);
    }

    removeTrailingChars (command, " \t\r\n");
    p = strchr (command, ' ');
    while (*p == ' ') ++p;

    strcpy (userAndPass, p);
    strcat (userAndPass, " ");
    p=strtok (NULL, " \t\r\n");
    strcat (userAndPass, p);

    while (fgets (line, DMAX, fin)){
        removeTrailingChars (line, " \t\r\n");
        if (strcmp (userAndPass, line) == 0){
            loggedIn = true;
            break;
        }
    }

    if (loggedIn){
        strcpy (son1Answer, "Successfully logged in!");
        lgAnswer = strlen (son1Answer);
        write (fdSonWrite, &lgAnswer, 4);
        write (fdSonWrite, son1Answer, lgAnswer);
    }
}

void removeTrailingChars (char s[], const char *toDelete){
    int lg;
    for (lg = 0; s[lg]; ++lg);

    while (strchr (toDelete, (int)s[lg-1])!= NULL)
        s[--lg] = 0;
}
