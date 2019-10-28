#include <stdio.h>
//Construiti matricea unitate (1 pe diagonala, 0 in rest)
#include <malloc.h>

int **mat;

void matrice_unitate(int**, int) {
	_asm {
		mov eax, [ebp + 8] // first element
		mov eax, [eax]
		mov edx, [ebp + 12]
		mov ebx, 0 // i
		for1:
		cmp ebx, edx
			jge exit_for1
			mov edi, ebx
			imul edi, edx
 			add edi, ebx
			imul edi, 4
			add edi, eax
			mov[edi], 1
			add ebx, 1
			jmp for1
			exit_for1:
	}
}

void main() {
	int n = 5, i;
	mat = (int**)malloc(n * sizeof(int*));
	for (i = 0; i<n; i++) {
		mat[i] = (int*)malloc(n * sizeof(int));
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			mat[i][j] = 0;
	//int **p = mat;
	_asm {
		push 5
		push mat
		call matrice_unitate
		add esp, 8
	}
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
	getchar();
}


/*int V[100], n, nrPasi;


void Roteste(int *, int, int)
{
	_asm {
		mov esi, [ebp+8]
		mov edi, esi
		mov ecx, [ebp+12]

		_for:
		cmp ecx, 0
		JE _doneFor
		dec ecx
		push [esi+4*ecx]
		jmp _for

		_doneFor:
		mov ebx, [ebp+12]//n
		mov eax, [ebp+16]//pasi
		cmp ebx, eax
		jb _good
		xor edx, edx
		div ebx
		mov eax, edx

		_good:
		
		mov ecx, eax

		_for2:
		cmp ecx, ebx
		JE _doneFor2
		pop edi
		mov [esi + ecx*4], edi
		inc ecx
		jmp _for2

		_doneFor2:

		xor ecx, ecx

		_for3:
		cmp ecx, eax
		JE _doneFor3
		pop edi
		mov [esi + ecx*4], edi
		inc ecx
		jmp _for3

		_doneFor3:
	}
}

int main()
{
	cin >> n >> nrPasi;
	for (int i = 0; i < n; i++)
		cin >> V[i];

	cout << endl;
	int *p = V;
	Roteste(p, n, nrPasi);

	for (int i = 0; i < n; i++)
		cout << V[i] << ' ';
	cout << endl;
	getchar();
	getchar();
	return 0;
}*/


/*
unsigned nrBits(int) {
	_asm {
		//returneaza numarul de biti setati in reprezentarea interna a numarului primit ca parametru
		xor eax, eax
		mov ebx, [ebp+8]

		_for:
		cmp ebx, 0
		JE _done
		shr ebx, 1
		inc ecx
		JNC _for
		inc eax
		jmp _for


		_done:
	}
}


unsigned isPrime(int) {
	_asm {
		//returneaza 1 daca numarul primit ca parametru este prim, 0 in caz contrar
		mov esi, [ebp+8]
		xor ebx, ebx
		xor ecx, ecx
		mov edi, 2

		_for:
		mov eax, edi
		mul edi
		cmp eax, esi
		JG _prim

		mov eax, esi
		xor edx, edx
		div edi
		cmp edx, 0
		JE _notPrim
		inc edi
		jmp _for

		_notPrim:
		xor eax, eax
		jmp _done

		_prim:
		mov eax, 1
		
		_done:
	}
}


int palindrom(unsigned int) {
	_asm {
		//returneaza 1 daca numarul primit ca parametru este palindrom, 0 in caz contrar
		xor ebx, ebx
		mov esi, [ebp+8]
		mov ecx, 10

		_for:
		cmp esi, 0
		JE _done
		mov eax, esi
		xor edx, edx
		div ecx
		mov edi, edx//ultima cifra
		
		mov esi, eax //n/10

		mov eax, ebx
		mul ecx
		add eax, edi
		mov ebx, eax

		jmp _for

		_done:
		mov esi, [ebp+8]
		cmp esi, eax
		JE _equal
		xor eax, eax
		JMP _gataDeTot

		_equal:
		mov eax, 1

		_gataDeTot:
	}
}*/

/*unsigned short powerOf2(int, int*) {
	_asm {
		//Se da un vector prin intermediul a doi parametri: primul reprezinta numarul de elemente din vector iar al II-lea este pointer catre primul element din vector.
		//Functia returneaza numarul de elemente din vector - puteri ale lui doi.
	}
}*/


int progresie_aritmetica(int, int*) {
	_asm {
		mov esi, [ebp+12]
		mov ecx, [ebp+8]
		mov eax, 1

		mov edi, [esi]
		add esi, 4
		dec ecx
		mov ebx, [esi]
		//add esi, 4
		sub ebx, edi//ebx = ratia

		mov edi, [esi]
		add esi, 4
		dec ecx

		_for:
		cmp ecx, 0
		JE _done
		mov edx, [esi]
		sub edx, edi
		cmp edx, ebx
		JNE _notGood
		mov edi, [esi]
		add esi, 4
		dec ecx
		jmp _for

		_notGood:
		xor eax, eax

		_done:
	}
}

/*
int toUpper(char*) {
	_asm {
		
	}
}


int nrTok(char*) {
	_asm {
		//Sa se returneze numarul de cuvinte din textul primit ca parametru. Separatorii sunt: ',',  ' ',   '.'
	}
}*/

/*#include <stdio.h>
//Construiti matricea unitate (1 pe diagonala, 0 in rest)
void matrice_unitate(int *, int)
{
_asm {
mov esi, [ebp+8]
mov ebx, [ebp+12]
xor ecx, ecx

_for1:
cmp ecx, ebx
JE _gata
xor edi, edi
_for2:
cmp edi, ebx
JE _gatafor2
mov eax, ebx
mul ecx
add eax, edi
shl eax, 2
mov dword ptr [esi + eax], 0
cmp ecx, edi
JNE _notzero
mov dword ptr[esi + eax], 1

_notzero:
inc edi
jmp _for2

_gatafor2:
inc ecx
jmp _for1
_gata:
}
}*/

/*#include <stdio.h>

//Calculati suma elementelor pare dintr-un vector.
int suma_pare_vector(int *, int)
{
_asm
{
xor eax, eax
xor ecx, ecx
mov edi, [ebp+8]
mov edx, [ebp+12]

_for:
cmp ecx, edx
JE _gata
mov esi, [edi+ecx*4]
inc ecx
and esi, 1
CMP esi, 1
JE _for
add eax, [edi + ecx*4-4]
JMP _for


_gata:

}
}

void main()
{
int v[5] = { 5,1,2,3,6 };
int *p = v;
int s;

_asm {
push 5
push p
call suma_pare_vector
add esp, 8
mov s, eax
}

printf("Suma: %d", s);
getchar();
}*/

/*#include <iostream>

using namespace std;

int f(int) {
_asm {
xor ebx, ebx
mov esi, [ebp+8]
cmp esi, 1
JNBE _apelosRecursivos
mov ebx, 1
jmp _gata

_apelosRecursivos:
mov edi, esi
shr edi, 1
jc _impar

dec esi
push esi
call f
add esp, 4
shl eax, 1
mov ebx, eax

xor eax, eax
dec esi
push esi
call f
add esp, 4
mov ecx, 3
mul ecx
add ebx, eax
mov eax, ebx

jmp _gata

_impar:
dec esi
push esi
call f
add esp, 4
shl eax, 2
mov ebx, eax

xor eax, eax
dec esi
push esi
call f
add esp, 4
mov ecx, 5
mul ecx
add ebx, eax
mov eax, ebx

_gata:
mov eax, ebx
}

}

int main() {
int n;
cin >> n;
_asm {
xor eax, eax
}
cout << f(n);
getchar();getchar();
return 0;

}*/


/*#include <stdio.h>

unsigned int fact_rec(unsigned int) {
_asm {
mov esi, [ebp+8]
cmp esi, 2
JGE _apelosRecursivos
mov eax, 1
jmp _gata

_apelosRecursivos:
dec esi
push esi
call fact_rec
add esp, 4
mov esi, [ebp+8]
mul esi

_gata:
}
}


void main() {
int nr, fact;
printf("nr = ");
scanf_s("%u", &nr);
_asm {
push nr
call fact_rec
add esp, 4
mov fact, eax
}
printf("%u! = %u", nr, fact);
getchar();getchar();getchar();
}*/

/*include <iostream>

using namespace std;

int f(int) {
int rez;
_asm {
xor edx, edx
xor ebx, ebx
mov eax, 1
xor edi, edi
mov esi, [ebp+8]

_while:
CMP ecx, esi
JGE _gata
add edi, 2
mul edi
add ebx, eax

inc ecx
JMP _while
_gata:
mov rez, ebx

}
return rez;
}

int main() {
int n, rez;
cin >> n;

_asm {
push n
call f
add esp, 4
mov rez, eax
}
//cout << f(n);
cout << rez;
getchar();
getchar();
return 0;
}*/


/*#include <stdio.h>

//Sa se scrie codul in limbaj de asamblare care oglindeste bitii  unui numar

void main() {
char number;
number = 140;

_asm {
mov ah, number
xor cl, cl
xor al, al


_for:
cmp cl, 7
JNBE _dupaFor
mov bl, 1
shl bl, cl
and bl, ah
shr bl, cl

mov dl, 7
sub dl, cl
mov ch, cl
mov cl, dl
shl bl, cl
mov cl, ch

or al, bl

inc cl
JMP _for

_dupaFor:
mov number, al
}
if (number != 49)
printf("Failed! Your result is %d\n", number);
else
printf("OK!");
getchar();
}*/
