#include "t3.h"

//SARBATORI FERICITEEEEEEEEEEEEEEEEEEEEEEEEEE
//MERRY CHRISTMAAAAAAAAAAAAAAASSSS
//FELIZ NAVIDAAAAAAAD
//JOYEUUUUUX NOEEEEEEEEEEEEEEEEEEELL

void addNodeBST(ArbBin **, const int &);
int DFS(ArbBin *);
inline int nodeIsSpecial(ArbBin *);

int nrNoduriSpeciale(int vectorNoduri[MAX_NODURI], int nrNoduri) {
	ArbBin *searchTree;
	searchTree = 0;
	int i;
	for (i = 0; i < nrNoduri; ++i)
		addNodeBST(&searchTree, vectorNoduri[i]);
	
	return DFS(searchTree);
}

void addNodeBST(ArbBin **root, const int &val) {
	ArbBin *iterator, *prevIterator, *newNode;

	newNode = new ArbBin;
	newNode->val = val;
	newNode->st = newNode->dr = 0;

	if (!(*root)) {
		*root = newNode;
		return;
	}

	iterator = prevIterator = *root;
	while (iterator) {
		prevIterator = iterator;
		if (val == iterator->val)
			return;

		if (val < iterator->val)
			iterator = iterator->st;
		else
			iterator = iterator->dr;
	}

	if (val < prevIterator->val)
		prevIterator->st = newNode;
	else
		prevIterator->dr = newNode;
	return;
}

int DFS(ArbBin *node) {
	if (!node)
		return 0;
	return nodeIsSpecial(node) + DFS(node->st) + DFS(node->dr);
}

inline int nodeIsSpecial(ArbBin *node) {
	if (!node->st || !node->dr)
		return 0;
	return (node->st->val) % 2 == 0 && (node->dr->val) % 2 == 0;
}

int nrOfNodes;

void buildMinHeap (nod *[]);
void combinare (nod *[], int);
nod *getMin (nod *[]);
void addHeapNode(nod *[], nod *);
void addQueueNode(nod **, nod**, const int &);

nod* combinareSortareListe(int nrListe, nod* liste[MAX_LISTE]) {
	nod *finalList, *endOfFinalList, *it;
	finalList = nullptr; endOfFinalList = nullptr;
	nod *minHeap[MAX_LISTE*MAX_NODURI + 10];
	nrOfNodes = 0;

	for (int i = 0; i < nrListe; ++i)
		for (it=liste[i]; it!=nullptr; it=it->urm)
			minHeap[nrOfNodes++] = it;

	buildMinHeap(minHeap);

	while (nrOfNodes) {
		addQueueNode (&finalList, &endOfFinalList, getMin(minHeap)->val);
		//addHeapNode(minHeap, endOfFinalList->urm);
	}

	return finalList;
}

void buildMinHeap (nod *minHeap[]) {
	int i;
	for (i = nrOfNodes / 2; i>=0; --i)
		combinare(minHeap, i);
	return;
}

void combinare(nod *minHeap[], int father) {
	int son = father * 2 + 1;
	nod *nodeToReposition = minHeap[father];
	
	while (son < nrOfNodes) {
		if (son + 1 < nrOfNodes &&
			minHeap[son + 1]->val < minHeap[son]->val)
			++son;

		if (nodeToReposition->val > minHeap[son]->val) {
			minHeap[father] = minHeap[son];
			father = son;
			son = father * 2 + 1;
		}
		else
			break;
	}
	minHeap[father] = nodeToReposition;
	return;
}

void addHeapNode(nod *minHeap[], nod *nodeToAdd) {
	if (!nodeToAdd)
		return;

	int father, son;
	son = nrOfNodes++;
	father = (son - 1) / 2;
	while (son && nodeToAdd->val < minHeap[father]->val) {
		minHeap[son] = minHeap[father];
		son = father;
		father = (son - 1) / 2;
	}
	minHeap[son] = nodeToAdd;
	return;
}

nod *getMin(nod *minHeap[]) {
	nod *result = minHeap[0];
	minHeap[0] = minHeap[--nrOfNodes];
	combinare(minHeap, 0);
	return result;
}

void addQueueNode(nod **list, nod **endOfList, const int &val) {
	nod *newNode = new nod;
	newNode->val = val; newNode->urm = nullptr;

	if (!(*list)) {
		*list = *endOfList = newNode;
		return;
	}
	(*endOfList)->urm = newNode;
	*endOfList = newNode;
	return;
}

void buildMatAdiac(bool[][MAX_NODURI + 10], int[][MAX_MUCHII], const int &);
void generateCompConexe(bool[][MAX_NODURI + 10], compConexe &, grafListaMuchii, const int &);
inline void saveCompConexa(compConexe &, const int&);
int subgraf[MAX_NODURI + 10], nrNoduriInSubgraf;
inline bool adiacent(bool[][MAX_NODURI + 10], const int &);

compConexe CompConexe(grafListaMuchii graf, int ordinCompConexe) {
	compConexe rez;
	rez.nrComponente = 0;

	bool matAdiac[MAX_NODURI + 10][MAX_NODURI + 10];
	buildMatAdiac(matAdiac, graf.muchii, graf.nrMuchii);

	nrNoduriInSubgraf = 1;
	for (int i = 2; i <= graf.nrNoduri; i += 2) {
		subgraf[0] = i;
		generateCompConexe(matAdiac, rez, graf, ordinCompConexe);
	}

	return rez;
}

void generateCompConexe(bool matAdiac[][MAX_NODURI + 10], compConexe &rez, grafListaMuchii graf, const int &ordin) {
	if (nrNoduriInSubgraf == ordin) {
		saveCompConexa(rez, ordin);
		return;
	}

	for (int i = subgraf[nrNoduriInSubgraf - 1] + 2; i <= graf.nrNoduri; i += 2) {
		if (adiacent(matAdiac, i)) {
			subgraf[nrNoduriInSubgraf++] = i;
			generateCompConexe(matAdiac, rez, graf, ordin);
			--nrNoduriInSubgraf;
		}
	}
}

inline void saveCompConexa(compConexe &rez, const int &ordin) {
	for (int i = 0; i < ordin; ++i)
		rez.componente[rez.nrComponente][i] = subgraf[i];
	rez.nrComponente++;
}

void buildMatAdiac(bool matAdiac[][MAX_NODURI + 10], int muchii[][MAX_MUCHII], const int &nrMuchii) {
	int i, j, vf1, vf2;
	for (i = 0; i <= MAX_NODURI; ++i)
		for (j = 0; j <= MAX_NODURI; ++j)
			matAdiac[i][j] = false;

	for (i = 0; i < nrMuchii; ++i) {
		vf1 = muchii[0][i];
		vf2 = muchii[1][i];
		matAdiac[vf1][vf2] = matAdiac[vf2][vf1] = true;
	}
}

inline bool adiacent(bool matAdiac[][MAX_NODURI + 10], const int &x) {
	for (int i = 0; i < nrNoduriInSubgraf; ++i)
		if (matAdiac[x][subgraf[i]])
			return true;
	return false;
}

ArbBin *aux, *rez;
int nrNoduriAux, nrNoduriMax;
bool nodInArbore[MAX_NODURI];
void buildListeAdiac(nod *[], nod *[], int[][MAX_MUCHII], const int &);
void buildBT(nod *listeAdiac[], ArbBin **);
void clearBT(ArbBin **);
void updateSol (ArbBin **, ArbBin**);

ArbBin* maxArbBin(int nrNoduri, int nrMuchii, int muchii[2][MAX_MUCHII]) {
	rez = nullptr;
	aux = nullptr;
	nrNoduriMax = 0;

	nod *listeAdiac[MAX_NODURI], *endListeAdiac[MAX_NODURI];
	buildListeAdiac(listeAdiac, endListeAdiac, muchii, nrMuchii);

	for (int i = 1; i <= nrNoduri; ++i) {
		addNodeBST(&aux, i);
		nodInArbore[i] = true;
		buildBT(listeAdiac, &aux);
		clearBT(&aux);
		nodInArbore[i] = false;
	}

	nod *p, *prevP;
	for (int i = 0; i<MAX_NODURI; ++i)
		for (p = listeAdiac[i]; p;) {
			prevP = p;
			p = p->urm;
			delete prevP;
		}

	return rez;
}

void buildBT(nod *listeAdiac[], ArbBin **currentNode) {
	nod *i, *j;
	ArbBin *newNodeSt, *newNodeDr;

	if (nrNoduriAux > nrNoduriMax) {
		nrNoduriMax = nrNoduriAux;
		clearBT(&rez);
		updateSol (&aux, &rez);
	}

	for (i = listeAdiac[(*currentNode)->val]; i->urm; i = i->urm) {
		if (nodInArbore[i->val])
			continue;
		newNodeSt = new ArbBin; newNodeSt->st = newNodeSt->dr= nullptr;
		newNodeSt->val = i->val;
		(*currentNode)->st = newNodeSt;
		nodInArbore[i->val] = true;
		++nrNoduriAux;

		for (j = i->urm; j; j = j->urm) {
			if (nodInArbore[j->val])
				continue;
			newNodeDr = new ArbBin; newNodeDr->st = newNodeDr->dr = nullptr;
			newNodeDr->val = j->val;
			(*currentNode)->dr = newNodeDr;
			nodInArbore[j->val] = true;
			++nrNoduriAux;

			buildBT(listeAdiac, &(*currentNode)->dr);
			nodInArbore[j->val] = false;
			delete newNodeDr;
			--nrNoduriAux;
		}

		buildBT(listeAdiac, &(*currentNode)->st);

		clearBT(&(*currentNode)->st);
		clearBT(&(*currentNode)->dr);
		delete newNodeSt;
		nodInArbore[i->val] = false;
		--nrNoduriAux;
	}
}

void updateSol (ArbBin **aux, ArbBin **rez) {
	if (*aux == nullptr)
		return;

	*rez = new ArbBin;
	*rez = *aux;
	if ((*aux)->st) {
		(*rez)->st = new ArbBin;
		(*rez)->st = (*aux)->st;
		updateSol(&(*aux)->st, &(*rez)->st);
	}

	if ((*aux)->dr) {
		(*rez)->dr = new ArbBin;
		(*rez)->dr = (*aux)->dr;
		updateSol(&(*aux)->dr, &(*rez)->dr);
	}
}

void clearBT(ArbBin **currentNode) {
	if ((*currentNode) == nullptr)
		return;

	clearBT(&(*currentNode)->st);
	clearBT(&(*currentNode)->dr);
	delete *currentNode;
}

void buildListeAdiac(nod *listeAdiac[], nod *endListeAdiac[], int muchii[][MAX_MUCHII], const int &nrMuchii) {
	int i, vf1, vf2;
	for (i = 0; i < MAX_NODURI; ++i)
		listeAdiac[i] = endListeAdiac[i] = nullptr;

	for (i = 0; i < nrMuchii; ++i) {
		vf1 = muchii[0][i];
		vf2 = muchii[1][i];
		addQueueNode(&listeAdiac[vf1], &endListeAdiac[vf1], vf2);
		addQueueNode(&listeAdiac[vf2], &endListeAdiac[vf2], vf1);
	}
	return;
}