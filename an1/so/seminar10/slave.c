#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

//using namespace std;

int charToA(char *s){
	int rez=0;
	for (int i = 0; s[i]; ++i)
		rez = rez*10 + s[i] - '0';
	return rez;
}

int main(int argc, char *argv[]){
	int a, b, rez;
	char op;
	
	if(argc!=4)
	{
		printf ("Slave nu a primit toti parametrii!\n");
		return -1;
	}

	a=charToA(argv[1]);
	b=charToA(argv[2]);
	op=argv[3][0];

	printf("Slave a primit: %d %d %c\n", a, b, op);

	if (op=='+'){
		printf ("Am returnat: %d\n", a+b);
		exit(a+b);
	}
	else{
		printf ("Am returnat: %d\n", a-b);
		exit(a-b);
	}

	return 0;
}
