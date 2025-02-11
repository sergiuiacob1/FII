// #pragma comment(linker, "/STACK:514572800")
// #pragma comment(linker, "/HEAP:714572800")

#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#define DMAX 5010
#define P_MUTATION 0.0075
#define P_CROSS 0.25
#define INF 2000000000
#define PI 3.1415
#define EPSILON 0.1
#define C 10000.0

using namespace std;

struct pack {
	double fitness, functionValue;
};

double prob[DMAX], probCumulated[DMAX];
int lgReprez[DMAX], sumLgReprez;
int discreteFactor;
bool chromosomeWillBeCrossed[DMAX];

bool comp(int a, int b) {
	return prob[a] > prob[b];
}

void RunFunction(int);

double DeJong(double[], int);
double SixHump(double[], int);
double Schwefel7(double[], int);
double Rastrigin(double[], int);

void BuildLgReprez(int, double[2], int);
double GeneticAlgorithm(double(*)(double[], int), int, double[][2]);
double RandomDouble(const double &, const double &);
int BinaryToInt(bool[], int);
void Copy(double[], double[], int);
void Copy(bool[], bool[], int);
void ValsToDouble(double[], bool[], int, double[][2]);
void BuildPartialProbabilities(double, double[], int);
struct pack Fitness(double(*testFunction)(double[], int), double[], int);
void GenerateRandomSolution(bool[][DMAX * sizeof(int)], int, int, double[][2]);
void CreateRandomChromosome(bool[], int);
bool PopulationIsEvoluating(int, int);
double EvaluatePopulation(bool[][DMAX * sizeof(int)], int, int, double(*testFunction)(double[], int), double[][2]);
void SelectNextPopulation(bool[][DMAX * sizeof(int)], int &, int);
void MutateChromosomes(bool[][DMAX * sizeof(int)], int, int);

void CrossChromosomes(bool[][DMAX * sizeof(int)], int, int);
void CrossIndividualChromosomes(bool[][DMAX * sizeof(int)], int, int, int);

int main() {
	int aux;
	srand((unsigned int)time(NULL));

	cout << "0 - DeJong, 1 - Rastrigin, 2 - Schwefel, 3 - SixHump\n";
	cin >> aux;
	RunFunction(aux);

	cin >> aux;//sa apara consola

	return 0;
}

void BuildLgReprez(int pos, double acceptedVals[2], int discreteFactor) {
	int lg;
	for (lg = 0; (acceptedVals[1] - acceptedVals[0]) * pow(10, discreteFactor) > pow(2, lg) - 1;)
		++lg;

	lgReprez[pos] = lg;
}


bool chromosomes[DMAX][DMAX * sizeof(int)];
int currentGeneration, lastBestGeneration;

double GeneticAlgorithm(double(*testFunction)(double[], int), int nrDims, double acceptedVals[][2]) {
	double bestSol, generationResult;
	int nrIterations, popSize;

	nrIterations = 1;
	popSize = 2000;
	bestSol = INF;
	for (int i = 0; i < nrIterations; ++i) {
		GenerateRandomSolution(chromosomes, popSize, nrDims, acceptedVals);
		currentGeneration = lastBestGeneration = 0;

		while (PopulationIsEvoluating(lastBestGeneration, currentGeneration)) {
			generationResult = EvaluatePopulation(chromosomes, popSize, nrDims, testFunction, acceptedVals);

			if (generationResult < bestSol) {
				bestSol = generationResult;
				lastBestGeneration = currentGeneration;
				cout << "Current Best solution: " << bestSol << '\n';
			}

			SelectNextPopulation(chromosomes, popSize, nrDims);
			CrossChromosomes(chromosomes, popSize, nrDims);
			MutateChromosomes(chromosomes, popSize, nrDims);

			++currentGeneration;
		}
	}

	return bestSol;
}

bool PopulationIsEvoluating(int lastBestGeneration, int currentGeneration) {
	if (currentGeneration - lastBestGeneration >= 100)
		return false;
	return true;
}

double EvaluatePopulation(bool chromosomes[][DMAX * sizeof(int)], int popSize, int nrDims, double(*testFunction)(double[], int), double acceptedVals[][2]) {
	double chromosomeFitness[DMAX], doubleVals[DMAX];
	double bestSol = INF, sumFitness = 0;
	struct pack result;

	for (int i = 0; i < popSize; ++i) {
		ValsToDouble(doubleVals, chromosomes[i], nrDims, acceptedVals);

		result = Fitness(testFunction, doubleVals, nrDims);
		chromosomeFitness[i] = result.fitness;
		bestSol = min(bestSol, result.functionValue);
		sumFitness += chromosomeFitness[i];
	}

	BuildPartialProbabilities(sumFitness, chromosomeFitness, popSize);

	return bestSol;
}

struct pack Fitness(double(*testFunction)(double[], int), double doubleVals[], int nrDims) {
	struct pack rez;

	rez.functionValue = testFunction(doubleVals, nrDims);

	if (testFunction == &Schwefel7)
		rez.fitness = abs(1 / (rez.functionValue + C));
	else
		rez.fitness = (1 / (rez.functionValue + EPSILON));
	return rez;
}

void BuildPartialProbabilities(double sumFitness, double chromosomeFitness[], int popSize) {
	for (int i = 0; i < popSize; ++i)
		prob[i] = chromosomeFitness[i] / sumFitness;

	probCumulated[0] = 0;
	for (int i = 1; i < popSize; ++i)
		probCumulated[i] = probCumulated[i - 1] + prob[i - 1];
	probCumulated[popSize] = 1.1;
}

void ValsToDouble(double doubleVals[], bool chromosome[], int nrDims, double acceptedVals[][2]) {
	int aux, sumLgReprez = 0;
	for (int i = 0; i < nrDims; ++i) {
		aux = BinaryToInt(chromosome + sumLgReprez, lgReprez[i]);
		doubleVals[i] = acceptedVals[i][0] + aux * (acceptedVals[i][1] - acceptedVals[i][0]) / (pow(2, lgReprez[i]) - 1);

		sumLgReprez += lgReprez[i];
	}
}

void GenerateRandomSolution(bool chromosomes[][DMAX * sizeof(int)], int popSize, int nrDims, double acceptedVals[][2]) {
	for (int i = 0; i < popSize; ++i) {
		CreateRandomChromosome(chromosomes[i], nrDims);
	}
}

void CreateRandomChromosome(bool chromosome[], int nrDims) {
	int i = 0, sumLgReprez = 0;
	for (int i = 0; i < nrDims; ++i) {
		for (int j = sumLgReprez; j < sumLgReprez + lgReprez[i]; ++j)
			chromosome[j] = rand() % 2;
		sumLgReprez += lgReprez[i];
	}
}

bool auxChromosomes[DMAX][DMAX * sizeof(int)];
void SelectNextPopulation(bool chromosomes[][DMAX * sizeof(int)], int &popSize, int nrDims) {
	double randomNr;
	int chosen[DMAX * 2];
	memset(chosen, 0, sizeof(chosen));

	//sel turneu
	/*for (int i = 0; i < popSize*2; ++i) {
		randomNr = rand() % popSize;
		chosen[i] = randomNr;
	}
	sort(chosen, chosen + popSize, comp);
	*/
	
	for (int i = 0; i < popSize; ++i) {
		randomNr = RandomDouble(0, 1);
		for (int j = 0; j < popSize; ++j)
			if (probCumulated[j] < randomNr && randomNr <= probCumulated[j + 1])
				chosen[i] = j;
	}
	
	for (int i = 0; i < popSize; ++i)
		Copy(auxChromosomes[i], chromosomes[i], sumLgReprez);

	int i, aux = popSize;
	popSize = 0;
	for (i = 0; i < aux; ++i)
		Copy(chromosomes[popSize++], auxChromosomes[chosen[i]], sumLgReprez);
}

void MutateChromosomes(bool chromosomes[][DMAX * sizeof(int)], int popSize, int nrDims) {
	double randomNr;
	int currentDimension;

	for (int i = 0; i < popSize; ++i) {
		if (chromosomeWillBeCrossed[i]) continue;
		currentDimension = 0;
		for (int j = 0; j < sumLgReprez; ++j) {
			randomNr = RandomDouble(0, 1);

			if (currentGeneration - lastBestGeneration <= 10 && currentGeneration <= 10000 &&
				j - lgReprez[currentDimension] <= lgReprez[currentDimension]/2) {
				if (randomNr < P_MUTATION + 0.05)
					chromosomes[i][j] = 1 - chromosomes[i][j];
				continue;
			}
			else
				if (randomNr < P_MUTATION)
					chromosomes[i][j] = 1 - chromosomes[i][j];

			if (j > lgReprez[currentDimension])
				++currentDimension;
		}
	}
}

void CrossChromosomes(bool chromosomes[][DMAX * sizeof(int)], int popSize, int nrDims) {
	vector <int> chosenForCrossing;
	double randomNr;
	memset(chromosomeWillBeCrossed, 0, sizeof(chromosomeWillBeCrossed));

	for (int i = 0; i < popSize; ++i) {
		randomNr = RandomDouble(0, 1);

		if (currentGeneration >= 10000) {
			if (randomNr <= P_CROSS + 0.1) {
				chosenForCrossing.push_back(i);
				chromosomeWillBeCrossed[i] = true;
			}
			continue;
		}

		if (randomNr < P_CROSS) {
			chosenForCrossing.push_back(i);
			chromosomeWillBeCrossed[i] = true;
		}
	}

	if (chosenForCrossing.size() % 2) {
		chromosomeWillBeCrossed[chosenForCrossing[chosenForCrossing.size() - 1]] = false;
		chosenForCrossing.pop_back();
	}

	for (unsigned int i = 0; i < chosenForCrossing.size(); i += 2) {
		CrossIndividualChromosomes(chromosomes, nrDims, chosenForCrossing[i], chosenForCrossing[i + 1]);
	}

}

void CrossIndividualChromosomes(bool chromosomes[][DMAX * sizeof(int)], int nrDims, int pos1, int pos2) {
	int randomPoz;

	randomPoz = rand() % sumLgReprez;
	for (int j = randomPoz; j < sumLgReprez; ++j)
		swap(chromosomes[pos1][j], chromosomes[pos2][j]);
}

double DeJong(double v[], int nrVals) {
	double functionValue = 0;

	for (int i = 0; i < nrVals; ++i) {
		functionValue += v[i] * v[i];
		if (v[i] < -5.12 || v[i] > 5.12)
		{
			cout << "Bad input for DeJong!\n";
			return 0;
		}
	}

	return functionValue;
}

double SixHump(double v[], int nrVals) {
	double functionValue = 0;

	if (v[0] < -3 || v[0] > 3 || v[1] < -2 || v[1] > 2)
	{
		cout << "Bad input for SixHump!\n";
		return 0;
	}

	functionValue = (4 - 2.1*v[0] * v[0] + v[0] * v[0] * v[0] * v[0] / 3)*v[0] * v[0] + v[0] * v[1] + (-4 + 4 * v[1] * v[1])*v[1] * v[1];

	return functionValue;
}

double Schwefel7(double v[], int nrVals) {
	double result = 0;
	for (int i = 0; i < nrVals; ++i)
		if (v[i] < -500 || v[i] > 500) {
			cout << "Bad input for Schwefel 7!\n";
			return 0;
		}

	for (int i = 0; i < nrVals; ++i)
		result += -v[i] * sin(sqrt(abs(v[i])));

	return result;
}

double Rastrigin(double v[], int nrVals) {
	double result = 0;

	for (int i = 0; i < nrVals; ++i)
		if (v[i] < -5.12 || v[i] > 5.12) {
			cout << "Bad input for Rastrigin!\n";
			return 0;
		}

	result = 10 * nrVals;
	for (int i = 0; i < nrVals; ++i)
		result += v[i] * v[i] - 10 * cos(2 * PI*v[i]);

	return result;
}

int BinaryToInt(bool binary[], int lg) {
	int rez, p2, i;

	for (rez = 0, p2 = 1, i = 0; i < lg; ++i, p2 *= 2)
		rez += p2*binary[i];

	return rez;
}

void Copy(double unde[], double deUnde[], int cate) {
	for (int i = 0; i < cate; ++i)
		unde[i] = deUnde[i];
}

void Copy(bool unde[], bool deUnde[], int cate) {
	for (int i = 0; i < cate; ++i)
		unde[i] = deUnde[i];
}

double RandomDouble(const double &minVal, const double &maxVal) {
	double f;
	f = (double)rand() / RAND_MAX;
	return minVal + f * (maxVal - minVal);
}

void RunFunction(int function) {
	double fRez;
	double fRezMin = INF, fRezMax = -INF, fRezMed, sum = 0;
	double acceptedVals[DMAX][2];
	int nrDims, discreteFactor;

	nrDims = 30; discreteFactor = 8;

	if (function <= 1)
		discreteFactor = 2;
	for (int i = 0; i < nrDims; ++i) {
		acceptedVals[i][0] = -5.12;
		acceptedVals[i][1] = 5.12;
	}

	if (function == 2) {
		discreteFactor = 6;
		for (int i = 0; i < nrDims; ++i) {
			acceptedVals[i][0] = -500;
			acceptedVals[i][1] = 500;
		}
	}
	if (function == 3) {
		nrDims = 2;
		acceptedVals[0][0] = -3; acceptedVals[0][1] = 3;
		acceptedVals[1][0] = -2; acceptedVals[1][1] = 2;
	}

	for (int i = 0; i < nrDims; ++i) {
		BuildLgReprez(i, acceptedVals[i], discreteFactor);
		sumLgReprez += lgReprez[i];
	}

	switch (function) {
	case 0:
		for (int i = 0; i < 15; ++i) {
			fRez = GeneticAlgorithm(DeJong, nrDims, acceptedVals);
			sum += fRez;
			fRezMin = min(fRez, fRezMin);
			fRezMax = max(fRez, fRezMax);
		}
		fRezMed = sum / 15;

		cout << "De Jong, " << nrDims << " dimensions: ";
		break;
	case 1:
		for (int i = 0; i < 15; ++i) {
			fRez = GeneticAlgorithm(Rastrigin, nrDims, acceptedVals);
			sum += fRez;
			fRezMin = min(fRez, fRezMin);
			fRezMax = max(fRez, fRezMax);
		}
		fRezMed = sum / 15;
		cout << "Rastrigin, " << nrDims << " dimensions: ";
		break;
	case 2:
		for (int i = 0; i < 15; ++i) {
			fRez = GeneticAlgorithm(Schwefel7, nrDims, acceptedVals);
			sum += fRez;
			fRezMin = min(fRez, fRezMin);
			fRezMax = max(fRez, fRezMax);
		}
		fRezMed = sum / 15;
		cout << "Schwefel7, " << nrDims << " dimensions: ";
		break;
	case 3:
		for (int i = 0; i < 15; ++i) {
			fRez = GeneticAlgorithm(SixHump, nrDims, acceptedVals);
			sum += fRez;
			fRezMin = min(fRez, fRezMin);
			fRezMax = max(fRez, fRezMax);
		}
		fRezMed = sum / 15;
		cout << "Six Hump, " << nrDims << " dimensions: ";
		break;
	}

	cout << fRezMin << " " << fRezMed << " " << fRezMax << '\n';
}