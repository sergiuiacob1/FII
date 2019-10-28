#include <iostream>
#include <fstream>
#include "t3.h"

using namespace std;

int vector[121], nrVal;
nod *liste[100], *rez2, *endListe[100];
int nrListe;

grafListaMuchii graf;
compConexe rezpb3;
int ordin;

void read();
void read2();

int main() {
	/*read();
	rez2 = combinareSortareListe(nrListe, liste);
	while (rez2) {
		cout << rez2->val << " ";
		rez2 = rez2->urm;
	}*/

	read2();
	rezpb3 = CompConexe(graf, ordin);
	int i, j;
	for (i = 0; i < rezpb3.nrComponente; ++i) {
		for (j = 0; j < ordin; ++j)
			cout << rezpb3.componente[i][j] << ' ';
		cout << '\n';
	}

	getchar();
	return 0;
}

void read2() {
	int i, j;
	ifstream fin("data.txt");
	fin >> graf.nrNoduri >> graf.nrMuchii;
	for (i = 0; i < graf.nrMuchii; ++i)
		fin >> graf.muchii[0][i] >> graf.muchii[1][i];
	fin >> ordin;

}

void read() {
	int i, j, nrVal, x;
	nod *newNode;
	ifstream fin("data.txt");
	fin >> nrListe;
	
	for (i = 0; i < nrListe; ++i) {
		fin >> nrVal;
		for (j = 0; j < nrVal; ++j) {
			newNode = new nod; newNode->urm = NULL;
			fin >> newNode->val;
			if (!liste[i])
				liste[i] = endListe[i] = newNode;
			else {
				endListe[i]->urm = newNode;
				endListe[i] = newNode;
			}
		}
	}
	fin.close();
	return;
}

/*int grad[MAX_NODURI + 10], muchiiScoase[MAX_MUCHII + 10], nrMuchiiScoase;
bool muchieEliminata[MAX_MUCHII + 10];
inline void calcGrad(const int &, int [][MAX_MUCHII]);
void eliminaMuchii(const int &, const int &, int [][MAX_MUCHII]);
void checkSolution(const int &nrNoduri);

ArbBin* maxArbBin(int nrNoduri, int nrMuchii, int muchii[2][MAX_MUCHII]) {
ArbBin *rez = nullptr;
bool matAdiac[MAX_NODURI + 10][MAX_NODURI + 10];

calcGrad(nrMuchii, muchii);
for (int i = 0; i <= MAX_MUCHII; ++i)
muchieEliminata[i] = false;

buildMatAdiac(matAdiac, muchii, nrMuchii);

nrMuchiiScoase = 1;
for (int i = 0; i < nrMuchii; ++i) {
muchieEliminata[i] = true;
muchiiScoase[0] = i;
eliminaMuchii(nrNoduri, nrMuchii, muchii);
muchieEliminata[i] = false;
}
return rez;
}

void eliminaMuchii(const int &nrNoduri, const int &nrMuchii, int muchii[][MAX_MUCHII]) {
if (nrMuchiiScoase == nrMuchii - (nrNoduri - 1)) {
checkSolution(nrNoduri);
return;
}
}

bool viz[MAX_NODURI + 10];

void checkSolution(const int &nrNoduri) {
int i;
for (i = 0; i <= MAX_NODURI; ++i)
viz[i] = false;

for (i = 1; i <= nrNoduri; ++i)
if (grad[i] > 3)
return;

for (i=1; i<nrNoduri; ++i)
if (!viz[i]) {
buildTree (i);
}
return;
}

inline void calcGrad(const int &nrMuchii, int muchii[][MAX_MUCHII]) {
int i;
for (i = 0; i <= MAX_NODURI; ++i)
grad[i] = 0;
for (i = 0; i < nrMuchii; ++i) {
++grad[muchii[0][i]];
++grad[muchii[1][i]];
}
}*/