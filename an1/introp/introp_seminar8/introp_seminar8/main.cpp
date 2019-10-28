#include <iostream>
#include "header.h"

using namespace std;

void preOrdine (Lista);
void inOrdine(Lista);
void afisare(nodArbBinary *nod);

int main() {

	return 0;
}

void parcurgere(nodArbBinary *root) {
	void *parcurgeri[3];
	parcurgeri[0] = &afisare(root);
	parcurgeri[0] = &afisare(root->st);
	parcurgeri[0] = &afisare(root->dr);
}

//auto rez

nodArbBinary *heapSearch(nodArbBinary *heap, const int &value) {
	if (!heap)
		return NULL;
	if (heap->value == value)
		return heap;
	nodArbBinary *leftResult = heapSearch(heap->st, value);
	return leftResult ? leftResult : heapSearch(heap->dr, value);
}

nodArb *heapSearch(nodArb *root, const int &value) {
	if (root == NULL)
		return;

	if (root->value == value)
		return root;

	nodArb *iterator;
	nodArb *result;
	for (iterator = root->fii; iterator; iterator = iterator->next) {
		result = heapSearch (iterator, value);
		if (result)
			return result;
	}
	return NULL;
}

nodArbBinary *heapSearchOptimized(nodArbBinary *root, const int &value) {
	if (root == NULL)
		return NULL;
	if (root->value == value)
		return root;
	if (value < root->value)
		return heapSearchOptimized(root->st, value);
	return heapSearchOptimized(root->dr, value);
}

void preOrdine(nodArbBinary *root) {
	if (!root)
		return;
	afisare(root);
	inOrdine(root->st);
	inOrdine(root->dr);
}

void postOrdine(nodArbBinary *root) {
	if (!root)
		return;
	inOrdine(root->st);
	inOrdine(root->dr);
	afisare(root);
}

void inOrdine(nodArbBinary *root) {
	if (!root)
		return;
	inOrdine(root->st);
	afisare(root);
	inOrdine(root->dr);
}

void afisare(nodArbBinary *nod) {
	cout << nod->value << ' ';
}