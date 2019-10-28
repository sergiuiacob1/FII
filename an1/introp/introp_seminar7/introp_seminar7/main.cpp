#include <iostream>

using namespace std;

struct nod
{
	int value;
	nod *next;
};

typedef nod *Lista;

void pushQueue (nod **prim, nod **ultim, const int &);
inline nod * getLastNode(nod**);
int popQueue(nod **prim, nod **);

int popStack(nod **prim);
void pushStack(nod **, const int &);

void stackToQueue(nod **stack, nod **, nod **);

void afisare(nod **);

nod *prim, *ultim, *stack;

int main() {
	unsigned int i;
	
	for (i = 0; i < 10; ++i)
		pushStack(&stack, i);

	stackToQueue(&stack, &prim, &ultim);

	afisare(&prim);
		
	getchar();
	return 0;
}

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

void stackToQueue(nod **stack, nod **first, nod **last) {
	int valueToPushBack;
	nod *newStack = NULL;
	*first = *last = NULL;

	while (*stack) {
		pushStack(&newStack, popStack (stack));
	}

	while (newStack) {
		valueToPushBack = popStack(&newStack);
		pushQueue(first, last, valueToPushBack);
		pushStack(stack, valueToPushBack);
	}

	return;
}

void interclasare(nod **prim1, nod **ultim1, nod **prim2, nod **ultim2, nod **stack) {
	*stack = NULL;

	int valueQueue1, valueQueue2;
	while (*prim1 != NULL && *prim2 != NULL) {
		valueQueue1 = popQueue(prim1, ultim1);
		valueQueue2 = popQueue(prim2, ultim2);
		if (valueQueue1 < valueQueue2) {
			pushStack(stack, valueQueue1);
			pushStack(stack, valueQueue2);
		}
		else {
			pushStack(stack, valueQueue2);
			pushStack(stack, valueQueue1);
		}
	}

	while (*prim1)
		pushStack(stack, popQueue(prim1, ultim1));

	while (*prim2)
		pushStack(stack, popQueue(prim2, ultim2));

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