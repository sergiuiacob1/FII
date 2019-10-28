#pragma once
#include <iostream>
#define NMAX 110
#define MMAX 210

/*struct muchie {
	static unsigned int nrMuchii;
	unsigned int vf1, vf2;
};
typedef muchie listaMuchii[MMAX];*/

struct nod {
	int value;
	nod *next;
};
typedef nod *vfAdiacente[NMAX];

struct graf {
	int nrNoduri, nrMuchii;
	vfAdiacente listaVfAdiacente;
};

struct coada {
	struct nod *prim = NULL, *ultim = NULL;
	struct nod *currentNode;
	bool notEmpty() {
		return (prim!=NULL);
	}
};

void pushQueue(struct coada);
struct nod *popQueue(struct coada);
void pushStack(nod **, const int &);
void BFS(struct graf, nod *);