#include <iostream>
using namespace std;

struct nod
{
	char value;
	nod *next;
};

typedef nod *Lista;

void adauga(nod **prim, const char &value);
void sterge(nod **, const int &);
void afisare(nod **);
void sorteaza(nod **, int ordine = 1);
inline bool inOrder(nod *p1, nod *p2, const int &ordine);

int main()
{
	nod *L1 = NULL;
	adauga(&L1, '4');
	adauga(&L1, '3');
	adauga(&L1, '2');
	adauga(&L1, '1');
	afisare(&L1);
	cout << '\n';
	sorteaza(&L1);
	afisare(&L1);
	cout << '\n';
	getchar();
	return 0;
}

void adauga(nod **prim, const char &value)
{
	if (*prim == NULL) {
		*prim = new nod;
		(*prim)->value = value;
		(*prim)->next = NULL;
		return;
	}

	nod *p = *prim;
	nod *ant=p;
	while (p)
	{
		ant = p;
		p = p->next;
	}
	p = new nod;
	p->value = value;
	p->next = NULL;
	ant->next = p;
	return;
}

void afisare(nod **prim)
{
	if (*prim == NULL)
		return;
	nod *p;
	p = *prim;
	while (p) {
		cout << p->value << " ";
		p = p->next;
	}
}

void sterge(nod **prim, const int &indice)
{
	if (*prim == NULL)
		return;
	int i;
	nod *p, *previousP = NULL;
	for (i = 0, p = *prim; i < indice; ++i)
	{
		previousP = p;
		p = p->next;
	}
	previousP->next = p->next;
	delete p;
}

void sorteaza (nod **prim, int ordine)//-1 descrescator, 1 crescator
{
	if (*prim == NULL)
		return;
	nod *current, *comparator, *pAux;
	char aux;

	for (current = *prim; current->next; current = current->next)
	{
		pAux = current;
		for (comparator = current->next; comparator; comparator = comparator->next)
			if (inOrder(pAux, comparator, ordine))
				pAux = comparator;
		aux = current->value;
		current->value = pAux->value;
		pAux->value = aux;
	}
	return;
}

inline bool inOrder(nod *p1, nod *p2, const int &ordine)
{
	return (p1->value - p2->value)*ordine > 0;
}

void insertSort(nod **prim, const char &valueToInsert)
{
	nod *newNode;
	newNode = new nod;
	newNode->value = valueToInsert;

	if (*prim == NULL)
	{
		*prim = newNode;
		(*prim)->next = NULL;
		return;
	}

	if (valueToInsert < (*prim)->value)
	{
		newNode->next = *prim;
		return;
	}

	nod *comparator = *prim, *prevNode = *prim;
	while (comparator)
	{
		if (comparator->value > valueToInsert)
			break;
		prevNode = comparator;
		comparator = comparator->next;
	}
	prevNode->next = newNode;
	newNode->next = comparator;
	return;
}