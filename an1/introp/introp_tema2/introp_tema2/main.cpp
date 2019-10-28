#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "t2.h"
#define tatdeauna while (true)

using namespace std;

void showList(rezultat);
void read();

ifstream fin("data.txt");
ofstream fout("dataOut.txt");

char sirFinal[MAX_SIR], literaStart;
cartonas vecCartonase[MAX_CARTONASE];
lista boyy[MAX_CARTONASE], girll[MAX_CARTONASE];
unsigned int nrCartonase;
rezultat joc;

char s1[100], s2[100], rez[100];

int main() {
	read();

	joc = mutariJoc(vecCartonase, nrCartonase, literaStart, sirFinal);

	showList(joc);

	getchar();
	return 0;
}

void showList(rezultat L) {
	if (L.sePoate)
		fout << "Se poate: DA\n";
	else {
		fout << "Se poate: NU\n";
		return;
	}

	fout << L.nrMutari << '\n';

	lista p = L.mutari;
	while (p != NULL) {
		fout << p->nod.sus << " -> " << p->nod.jos << '\n';
		p = p->urmator;
	}
}

void read() {
	unsigned int i;
	char ch, s[3];

	fin >> nrCartonase;

	for (i = 0; i < nrCartonase; ++i) {
		fin >> ch >> s;
		vecCartonase[i].sus = ch;
		strcpy_s(vecCartonase[i].jos, s);
	}

	fin >> literaStart;
	fin >> sirFinal;
}
