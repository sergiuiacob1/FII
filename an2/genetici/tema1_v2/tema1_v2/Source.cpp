#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <map>
#define DMAX 100
#define INF 999999999
#define PRECISION 0.1
#define PI 3.14159265

using namespace std;

struct values {
	double functionValue;
	double dimensionValue;
};

struct localMinimum {
	vector <double> bazin;
	struct values;
};

vector <struct localMinimum> minPoints;
multimap <double, double> mapMinPoints;
map <double, bool> checkedValue;

struct values HillClimb(double(*testFunction)(double[], int), char[], int);
void generateNeighbours(char[][DMAX], char[], int );
void generateSolution(char[], int);
void intToBinary(char[], int);
int binaryToInt(char[], int);
void toNumbers(double[], char[], int);
void copy(char[], char[], int);
void runAlgorithm();

double function(double v[], int nrVals) {
	return (v[0] * v[0] * v[0] - 60 * v[0] * v[0] + 900 * v[0] + 100);
}

int main() {
	srand((unsigned int)time(NULL));

	runAlgorithm();

	double lastVal = -INF;
	for (auto it : mapMinPoints) {
		if (lastVal != it.first) {
			lastVal = it.first;
			cout << '\n' << it.first << " are bazinul: " << it.second << ' ';
		}
		else
			cout << it.second << ' ';
	}

	getchar();

	return 0;
}

struct values HillClimb(double(*testFunction)(double[], int), char currSol[], int nrVals) {
	char neighbours[DMAX][DMAX];
	int nrIterations = 100;
	double numbers[DMAX], bestSol = -INF, functionValue, bestDimension;
	bool local;
	
	for (int i = 0; i < nrIterations; ++i) {
		//generateSolution(currSol, nrVals);
		toNumbers(numbers, currSol, nrVals);
		bestSol = testFunction(numbers, nrVals);
		bestDimension = binaryToInt(currSol, 5);

		local = true;
		while (local) {
			local = false;
			generateNeighbours(neighbours, currSol, nrVals);
			
			for (int j = 0; j < 5; ++j) {
				toNumbers(numbers, neighbours[j], nrVals);

				//checkedValue[binaryToInt(neighbours[j], 5)] = true;
				functionValue = testFunction(numbers, nrVals);

				if (functionValue > bestSol) {
					local = true;
					bestSol = functionValue;
					bestDimension = binaryToInt(neighbours[j], 5);
					copy(currSol, neighbours[j], 5);
					//break;
				}
			}
		}

	}

	struct values rez;
	rez.dimensionValue = bestDimension;
	rez.functionValue = bestSol;
	return rez;
}

void generateNeighbours(char neighbours[][DMAX], char currSol[], int nrVals) {
	for (int i = 0; i < 5; ++i){
		currSol[i] = 1 - currSol[i];
		copy(neighbours[i], currSol, 5);
		currSol[i] = 1 - currSol[i];
	}
	/*char aux[DMAX], aux2[DMAX];
	copy(aux, currSol, 5);
	for (int i = 0; i < 5; ++i) {
		if (currSol[i] == 1)
			aux[i] = 0;
		else
		{
			aux[i] = 1;
			for (int j = i + 1; j < 5; ++j)
				aux[j] = currSol[j];
			break;
		}
	}
	copy(neighbours[0], aux, 5);*/
	return;
}

void toNumbers(double numbers[], char currSol[], int nrVals) {
	for (int i = 0; i < nrVals; ++i)
		numbers[i] = binaryToInt(currSol, 5);
}

void generateSolution(char currSol[], int nrVals) {
	for (int i = 0; i < nrVals; ++i)
		intToBinary(currSol, rand() % 32);
}

void intToBinary(char v[], int val) {
	int lg = 0;
	do {
		v[lg++] = val % 2;
		val /= 2;
	} while (val);

	while (lg != 5)
		v[lg++] = 0;
}

int binaryToInt(char binary[], int lg) {
	int rez, p2, i;

	for (rez = 0, p2 = 1, i = 0; i < lg; ++i, p2 *= 2)
		rez += p2*binary[i];

	return rez;
}

void copy(char unde[], char deUnde[], int cate) {
	for (int i = 0; i < cate; ++i)
		unde[i] = deUnde[i];
}

void runAlgorithm() {
	double bestSolYet = -INF;
	char sol[DMAX*DMAX];
	struct values rez;
	for (int i = 0; i < 32; ++i) {
		intToBinary(sol, i);
		if (checkedValue[i] == true) continue;
		checkedValue[i] = true;
		rez = HillClimb(function, sol, 1);
		mapMinPoints.insert(pair <double, double>(rez.functionValue, i));
	}
}