#include "t2.h"
#define INFINITE 4000000000

struct charNode {
	static unsigned int nrOfNodes;
	static charNode *firstNode;
	char value;
	struct charNode *urmator;
};
charNode *charNode::firstNode = NULL;
unsigned int charNode::nrOfNodes = 0;

unsigned int currentMinimum = INFINITE;
unsigned int nrOfMoves = 0;
unsigned int lgSirFinal;
char sirSolutie[MAX_SIR];

bool allowedLetters[MAX_SIR][30], pathBetweenLetters[30][30];
void buildAllowedLettersForEachPosition (const char []);
void buildPathBetweenLetters();

lista boysCards[15], girlsCards[35];
void filterCards(cartonas[MAX_CARTONASE], const unsigned int &);
void pushList(const cartonas &, lista &);
void popList(lista &);

void buildSolution (struct charNode **, const char [], unsigned int, lista *, rezultat &);
inline bool quickSolutionRejection(struct charNode **, const char &);
inline bool letterIsNotGood(const char &, const char &);
void updateBestSolution(lista *, rezultat &);

void addCharNode (struct charNode **, const char &);
void deleteCharNode (struct charNode **);

inline bool isDigit(const char &);
inline void reverseString(char [], const unsigned int &);

void codificareADN(long long nrIntreg, char sirADN[MAX_ADN]) {
	if (!nrIntreg) {
		sirADN[0] = 'A';
		sirADN[1] = NULL;
		return;
	}

	unsigned int sirADNLength = 0;
	int rest;

	while (nrIntreg) {
		rest = nrIntreg % 4;
		nrIntreg /= 4;
		if (rest == 3) {
			rest = -1;
			++nrIntreg;
		}

		if (rest == -2 || rest == -3) {
			--nrIntreg;
			rest += 4;
		}

		switch (rest) {
		case -1: sirADN[sirADNLength++] = 'T'; break;
		case 0: sirADN[sirADNLength++] = 'A'; break;
		case 1: sirADN[sirADNLength++] = 'C'; break;
		case 2: sirADN[sirADNLength++] = 'G'; break;
		}
	}
	sirADN[sirADNLength] = NULL;

	reverseString(sirADN, sirADNLength);
	return;
}

inline void reverseString(char s[], const unsigned int &sLength) {
	unsigned int st, dr;
	char aux;

	for (st = 0, dr = sLength - 1; st < dr; ++st, --dr) {
		aux = s[st];
		s[st] = s[dr];
		s[dr] = aux;
	}
}

long long decodificareADN(char sirADN[MAX_ADN]) {
	long long result, pow4, sirADNLength, valueOfCharacter;

	for (sirADNLength = 0; sirADN[sirADNLength]; ++sirADNLength);

	for (pow4 = 1, --sirADNLength, result = 0; sirADNLength >= 0; --sirADNLength, pow4 *= 4) {
		switch (sirADN[sirADNLength]) {
		case 'T': valueOfCharacter = -1; break;
		case 'A': valueOfCharacter = 0; break;
		case 'C': valueOfCharacter = 1; break;
		case 'G': valueOfCharacter = 2; break;
		}
		result += pow4*valueOfCharacter;
	}
	return result;
}

void adunareADN(char primulSir[MAX_ADN], char alDoileaSir[MAX_ADN], char suma[MAX_ADN]) {
	long long firstNumber, secondNumber;
	firstNumber = decodificareADN(primulSir);
	secondNumber = decodificareADN(alDoileaSir);
	codificareADN(firstNumber + secondNumber, suma);
	return;
}

void scadereADN(char primulSir[MAX_ADN], char alDoileaSir[MAX_ADN], char diferenta[MAX_ADN]) {
	long long firstNumber, secondNumber;
	firstNumber = decodificareADN(primulSir);
	secondNumber = decodificareADN(alDoileaSir);
	codificareADN(firstNumber - secondNumber, diferenta);
	return;
}

rezultat mutariJoc(cartonas vecCartonase[MAX_CARTONASE], unsigned int nCartonase, char literaStart, char sirFinal[MAX_SIR]) {
	rezultat rez;
	rez.sePoate = false; rez.nrMutari = 0;
	rez.mutari = NULL;

	filterCards(vecCartonase, nCartonase);
	buildAllowedLettersForEachPosition(sirFinal);
	buildPathBetweenLetters();

	lista currentMovesList = NULL;
	struct charNode *currentString = NULL;

	addCharNode(&currentString, literaStart);
	lgSirFinal = strlen(sirFinal);

	buildSolution(&currentString, sirFinal, 0, &currentMovesList, rez);

	deleteCharNode (&currentString);

	//rest of the cards
	if (rez.sePoate) {
		lista *endOfMovesList=&rez.mutari;
		if (rez.mutari)
			while ((*endOfMovesList)->urmator)
				endOfMovesList = &(*endOfMovesList)->urmator;
		
		cartonas aux;
		for (int i = 0; sirFinal[i]; ++i) {
			aux.sus = sirSolutie[i];
			aux.jos[0] = sirFinal[i]; aux.jos[1] = 0;

			if (!(*endOfMovesList))
				pushList(aux, *endOfMovesList);
			else
				pushList(aux, (*endOfMovesList)->urmator);
			endOfMovesList = &(*endOfMovesList)->urmator;
			++rez.nrMutari;
		}
	}
	return rez;
}

void buildSolution(struct charNode **currentString,
	const char sirFinal[],
	unsigned int k,
	lista *currentMovesList,
	rezultat &rez){

	if (!sirFinal[k] && *currentString == NULL) {
		updateBestSolution(currentMovesList, rez);
		return;
	}

	if (quickSolutionRejection(currentString, sirFinal[k]))
		return;

	if (allowedLetters[k][(*currentString)->value-'A']) {
		buildSolution(&(*currentString)->urmator, sirFinal, k + 1, currentMovesList, rez);
	}

	char valueCopy = (*currentString)->value;
	lista iterator;

	for (iterator = girlsCards[(*currentString)->value - 'A']; iterator; iterator = iterator->urmator) {
		if (letterIsNotGood((*currentString)->value, sirFinal[k]))
			continue;

		(*currentString)->value = iterator->nod.jos[0];
		if (iterator->nod.jos[1])
			addCharNode(currentString, iterator->nod.jos[1]);
		pushList(iterator->nod, *currentMovesList);
		++nrOfMoves;

		if (allowedLetters[k][(*currentString)->value-'A'])
			buildSolution(&(*currentString)->urmator, sirFinal, k + 1, currentMovesList, rez);
		buildSolution(currentString, sirFinal, k, currentMovesList, rez);//same, but different (iterator changes)

		popList(*currentMovesList);
		--nrOfMoves;
		(*currentString)->value = valueCopy;
		if (iterator->nod.jos[1])
			deleteCharNode(&(*currentString)->urmator);
	}
	return;
}

inline bool quickSolutionRejection(struct charNode **currentString, const char &ch) {
	return nrOfMoves >= currentMinimum || charNode::nrOfNodes > lgSirFinal || *currentString == NULL
		|| letterIsNotGood ((*currentString)->value, ch);
}

void updateBestSolution(lista *currentMovesList, rezultat &rez) {
	while (rez.mutari)
		popList(rez.mutari);

	for (lista iterator = *currentMovesList; iterator; iterator = iterator->urmator)
		pushList(iterator->nod, rez.mutari);

	charNode *iterator; unsigned int i;
	for (iterator = charNode::firstNode, i=0; i < charNode::nrOfNodes; ++i, iterator = iterator->urmator)
		sirSolutie[i] = iterator->value;
	sirSolutie[i] = 0;

	currentMinimum = nrOfMoves;
	rez.sePoate = true;
	rez.nrMutari = currentMinimum;
	return;
}

void filterCards(cartonas vecCartonase[MAX_CARTONASE], const unsigned int &nCartonase) {
	unsigned int i;

	for (i = 0; i < 10; ++i)
		boysCards[i] = NULL;
	for (i = 0; i < 30; ++i)
		girlsCards[i] = NULL;

	for (i = 0; i<nCartonase; ++i)
		if (isDigit(vecCartonase[i].jos[0]))
			pushList(vecCartonase[i], boysCards[vecCartonase[i].jos[0] - '0']);
		else
			pushList(vecCartonase[i], girlsCards[vecCartonase[i].sus - 'A']);
	return;
}

void buildAllowedLettersForEachPosition(const char sirFinal[]) {
	unsigned int i;
	lista iterator;
	for (i = 0; sirFinal[i]; ++i)
		for (iterator = boysCards[sirFinal[i] - '0']; iterator; iterator = iterator->urmator)
			allowedLetters[i][iterator->nod.sus - 'A'] = true;//pe pozitia i pot avea litera respectiva
	return;
}

void buildPathBetweenLetters() {
	bool parsedLetters[30];
	unsigned int i, j, k;
	for (i = 0; i < 30; ++i)
		parsedLetters[i] = false;

	for (i = 0; i < 30; ++i)
		for (lista iterator = girlsCards[i]; iterator; iterator = iterator->urmator)
			pathBetweenLetters[i][iterator->nod.jos[0] - 'A'] = true;

	for (k = 0; k < 30; ++k) {
		pathBetweenLetters[k][k] = true;
		for (i = 0; i < 30; ++i)
			for (j = 0; j < 30; ++j)
				if (pathBetweenLetters[i][k] && pathBetweenLetters[k][j]) {
					pathBetweenLetters[i][j] = true;
				}
	}
	return;
}

inline bool letterIsNotGood(const char &ch, const char &digit) {
	lista iterator;
	for (iterator = boysCards[digit - '0']; iterator; iterator = iterator->urmator)
		if (pathBetweenLetters[ch-'A'][iterator->nod.sus - 'A'])
			return false;
	return true;
}

void addCharNode(struct charNode **L, const char &value) {
	struct charNode *newNode = new charNode;
	newNode->value = value;
	newNode->urmator = NULL;
	++charNode::nrOfNodes;

	if (*L == NULL) {
		*L = newNode;
		charNode::firstNode = newNode;
		return;
	}

	newNode->urmator = (*L)->urmator;
	(*L)->urmator = newNode;
}


void deleteCharNode(struct charNode **L) {
	if (*L == NULL)
		return;

	--charNode::nrOfNodes;

	if (*L == charNode::firstNode) {
		charNode::firstNode = (*L)->urmator;
		delete *L;
		*L = charNode::firstNode;
		return;
	}

	charNode *prevIterator, *iterator;
	for (prevIterator = NULL, iterator = charNode::firstNode; iterator != *L; ) {
		prevIterator = iterator;
		iterator = iterator->urmator;
	}

	prevIterator->urmator = iterator->urmator;
	L = &(*L)->urmator;
	delete iterator;
}

void popList(lista &L) {
	if (L == NULL)
		return;
	lista copyL = L;
	L = L->urmator;
	delete copyL;
	return;
}

void pushList (const cartonas &card, lista &L) {
	lista newNode;

	newNode = new mutare;
	newNode->nod = card;
	newNode->urmator = NULL;

	if (!L) {
		L = newNode;
		return;
	}

	newNode->urmator = L;
	L = newNode;
}

inline bool isDigit(const char &ch) {
	return '0' <= ch && ch <= '9';
}