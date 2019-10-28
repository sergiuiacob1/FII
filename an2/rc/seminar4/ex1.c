#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
  {
    int sockp[2], child;
    char operator;
    int op1, op2;
    int rez;

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockp) < 0)
      {
        perror("Err... socketpair");
        exit(1);
      }

    while (scanf ("%d %c %d", &op1, &operator, &op2) > 0){
        if (fork()){//sunt in parinte
            write (sockp[1], &op1, 4);
            write (sockp[1], &operator, 1);
            write (sockp[1], &op2, 4);
            read (sockp[1], &rez, 4);
            printf ("%d\n", rez);
        }
        else{
            close (sockp[1]);
            read (sockp[0], &op1, 4);
            read (sockp[0], &operator, 1);
            read (sockp[0], &op2, 4);
            switch (operator){
                case '+':
                    rez = op1 + op2; break;
                case '-':
                    rez = op1 - op2; break;
                case '*':
                    rez = op1*op2; break;
                default:
                    rez = op1/op2;
            }

            write (sockp[0], &rez, 4);

            close (sockp[0]);
            exit (1);
        }
    }
  }
