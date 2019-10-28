#pragma once
struct nod {
	int value;
	nod *next;
};

typedef nod *Lista;

struct nodArbBinary {
	nodArbBinary *st, *dr;
	int value;
};

struct nodArb {
	nodArb *fii;
	nodArb *next;
	int value;
};

typedef nodArb *listaArbore;

int popStack(nod **prim);
void pushStack(nod **, const int &);
void pushQueue(nod **prim, nod **ultim, const int &);
inline nod * getLastNode(nod**);
int popQueue(nod **prim, nod **);

void pushQueue(nod **prim, nod **ultim, const int &value) {
	nod *newNode;

	newNode = new nod;
	newNode->value = value;
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
	int result = (*prim)->value;
	*prim = (*prim)->next;
	delete aux;

	if (!(*prim))
		*ultim = NULL;

	return result;
}

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