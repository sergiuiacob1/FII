#include <fstream>
#include <stdio.h>
#include "header.h"

using namespace std;

struct graf G;
void readGraf(struct graf);
void showGraf(struct graf);

int main() {
	readGraf (G);
	showGraf(G);
	getchar();
}

void readGraf(struct graf G) {
	ifstream fin("data.txt");
	fin >> G.nrNoduri >> G.nrMuchii;

	int i, a, b;
	for (i = 0; i < G.nrMuchii; ++i) {
		fin >> a >> b;
		pushStack(&G.listaVfAdiacente[a], b);
		pushStack(&G.listaVfAdiacente[b], a);
	}

}

void showGraf(struct graf G) {
	cout << G.nrNoduri << ' ' << G.nrMuchii << '\n';

	int i;
	nod *iterator;
	for (i = 0; i < G.nrNoduri; ++i)
		for (iterator = G.listaVfAdiacente[i]; iterator; iterator = iterator->next)
			cout << i << " " << iterator->value << '\n';

}