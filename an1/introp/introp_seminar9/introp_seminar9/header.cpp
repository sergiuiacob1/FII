#include <iostream>
#include "header.h"

using namespace std;

inline void visitNode(nod *, unsigned int[]);

void pushQueue(struct coada C, nod *value){
	if (!C.prim) {
		C.prim = C.ultim = value;
		return;
	}
	C.ultim->next = value;
}

struct nod *popQueue(struct coada C) {
	nod *result = C.currentNode;
	if (C.currentNode)
		C.currentNode = C.currentNode->next;

	return result;
}

void BFS(struct graf G, nod *root) {
	struct coada C;
	nod *currentNode;
	unsigned int nivel[NMAX];
	bool alreadyVisited[NMAX];
	for (int i = 0; i < G.nrNoduri; ++i)
		alreadyVisited[i] = false;

	pushQueue(C, root);
	alreadyVisited[root->value] = true;
	nivel[root->value] = 0;
	while (C.notEmpty()) {
		currentNode = popQueue(C);
		visitNode(currentNode, nivel);
		for (nod *vfAdiacent = currentNode; vfAdiacent; vfAdiacent = vfAdiacent->next)
			if (!alreadyVisited[vfAdiacent->value]) {
				alreadyVisited[vfAdiacent->value] = true;
				pushQueue(C, vfAdiacent);
				nivel[vfAdiacent->value] = nivel[currentNode->value] + 1;
			}
	}
}

inline void visitNode(nod *currentNode, unsigned int nivel[]) {
	cout << "Nivelul nodului " << currentNode->value << " este: ";
	cout << nivel[currentNode->value] << '\n';
}

/*void DFS(struct nod *vf) {
if (vf == NULL)
return;
struct nod *p;
for (p = vf; p; p = p->next)
return;
}


void pushQueue(nod **prim, nod **ultim, const int &value) {
	nod *newNode;

	newNode = new nod;
	newNode->vfAdiacent = value;
	newNode->next = NULL;

	if (!(*ultim)) {
		*prim = *ultim = newNode;
		return;
	}

	(*ultim)->next = newNode;
	*ultim = newNode;
}

inline nod * getLastNode(nod **prim) {
	nod *iterator;
	for (iterator = *prim; iterator->next; iterator = iterator->next);

	return iterator;
}

int popQueue(nod **prim, nod **ultim) {
	if (!(*prim))
		return -1;

	nod *aux = *prim;
	int result = (*prim)->vfAdiacent;
	*prim = (*prim)->next;
	delete aux;

	if (!(*prim))
		*ultim = NULL;

	return result;
}
*/

void pushStack(nod **prim, const int &value) {
	nod *newNode;

	newNode = new nod;
	newNode->value = value;
	newNode->next = *prim;
	*prim = newNode;
}

int popStack(nod **prim) {
	if (!(*prim))
		return -1;

	nod *aux = *prim;
	int result = (*prim)->value;
	*prim = (*prim)->next;
	delete aux;
	return result;
	nod *newStack = new nod;
}