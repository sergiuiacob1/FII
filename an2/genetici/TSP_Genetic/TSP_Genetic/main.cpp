#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#define MAX_CITIES 1000
#define MAX_CHROMOSOMES 2000
#define INF 2000000000
#define P_MUTATION 0.25
#define P_CROSS 0.05
#define MAX_MUTATION_SWAPS 50

using namespace std;

struct BestRoad
{
	int road[MAX_CITIES];
	double lg;
};

struct pack
{
	double fitness, lg;
};

struct City
{
	static int nr;
	double x, y;
};

int City::nr;
City cities[MAX_CITIES];
double dist[MAX_CITIES][MAX_CITIES];

int chromosomes[MAX_CHROMOSOMES][MAX_CITIES];
double prob[MAX_CHROMOSOMES], probCumulated[MAX_CHROMOSOMES];
bool chromosomeWillBeCrossed[MAX_CHROMOSOMES];

void ReadData();
void CalcDistances();
double PointDistance(const City &, const City &);
struct BestRoad Genetic();
void GenerateRandomPopulation(int[][MAX_CITIES], int);
void CreateRandomChromosome(int[]);
bool PopulationIsEvoluating(int, int);
struct BestRoad EvaluatePopulation(int[][MAX_CITIES], int);
struct pack Fitness(int[]);
void BuildPartialProbabilities(double, double[], int);
void SelectNextPopulation(int[][MAX_CITIES], int &);
void MutateChromosomes(int[][MAX_CITIES], int);
void MutateChromosomesv2(int[][MAX_CITIES], int);

void CrossChromosomes(int[][MAX_CITIES], int);
void CrossIndividualChromosomes(int[][MAX_CITIES], int, int);
void CrossIndividualChromosomes2(int[][MAX_CITIES], int, int);

struct BestRoad Heuristic();

double CalcDistDrum(int[]);
void Copy(int[], int[], int);
double RandomDouble(const double &, const double &);

int main()
{
	int option;
	struct BestRoad rez;
	ofstream fout("data.out");
	srand((unsigned int)(time(NULL)));

	ReadData();
	CalcDistances();

	cout << "1 for Genetic, 2 for Heuristic: ";
	cin >> option;

	if (option == 1)
	{
		rez = Genetic();
		cout << "Best lg: " << rez.lg << '\n';
		for (int i = 0; i < City::nr; ++i)
			cout << rez.road[i] << ' ';
		cout << '\n';
	}

	if (option == 2)
	{
		rez = Heuristic();
		cout << "Best lg: " << rez.lg << '\n';
		for (int i = 0; i < City::nr; ++i)
			cout << rez.road[i] << ' ';
		cout << '\n';
	}

	getchar();
	getchar();
	return 0;
}

void ReadData()
{
	int nr;
	ifstream fin("data.in");

	City::nr = 0;
	while (fin >> nr)
	{
		--nr;
		fin >> cities[nr].x >> cities[nr].y;
		++City::nr;
	}
}

void CalcDistances()
{
	int i, j;
	for (i = 0; i < City::nr; ++i)
		for (j = i + 1; j < City::nr; ++j)
		{
			dist[i][j] = dist[j][i] = PointDistance(cities[i], cities[j]);
		}
}

double PointDistance(const City &a, const City &b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct BestRoad Genetic()
{
	struct BestRoad bestSol, generationResult;
	int nrIterations, currentGeneration, lastBestGeneration;
	int popSize;

	nrIterations = 1;
	popSize = 1000;
	bestSol.lg = INF;

	for (int i = 0; i < nrIterations; ++i)
	{
		GenerateRandomPopulation(chromosomes, popSize);
		currentGeneration = lastBestGeneration = 0;
		while (PopulationIsEvoluating(lastBestGeneration, currentGeneration))
		{
			generationResult = EvaluatePopulation(chromosomes, popSize);

			if (generationResult.lg < bestSol.lg)
			{
				bestSol.lg = generationResult.lg;
				Copy(bestSol.road, generationResult.road, City::nr);
				lastBestGeneration = currentGeneration;
				cout << "Current Best solution: " << bestSol.lg << '\n';
				/*for (int i = 0; i < City::nr; ++i)
					cout << bestSol.road[i] + 1 << ", ";
				cout << '\n';*/
			}

			SelectNextPopulation(chromosomes, popSize);
			CrossChromosomes(chromosomes, popSize);
			//MutateChromosomes(chromosomes, popSize);
			MutateChromosomesv2(chromosomes, popSize);

			++currentGeneration;
		}
	}

	return bestSol;
}

void GenerateRandomPopulation(int chromosomes[][MAX_CITIES], int popSize)
{
	for (int i = 0; i < popSize; ++i)
	{
		CreateRandomChromosome(chromosomes[i]);
	}
}

void CreateRandomChromosome(int chromosome[])
{
	int i, swapNr;
	for (i = 0; i < City::nr; ++i)
		chromosome[i] = i;

	swapNr = 100;
	for (i = 0; i < swapNr; ++i)
	{
		swap(chromosome[rand() % City::nr], chromosome[rand() % City::nr]);
	}
}

bool PopulationIsEvoluating(int lastBestGeneration, int currentGeneration)
{
	if (currentGeneration - lastBestGeneration >= 1000)
		return false;
	return true;
}

struct BestRoad EvaluatePopulation(int chromosomes[][MAX_CITIES], int popSize)
{
	double chromosomeFitness[MAX_CITIES];
	double sumFitness = 0;
	struct pack result;
	struct BestRoad bestRoad;

	bestRoad.lg = INF;

	for (int i = 0; i < popSize; ++i)
	{
		result = Fitness(chromosomes[i]);
		chromosomeFitness[i] = result.fitness;
		if (result.lg < bestRoad.lg)
		{
			Copy(bestRoad.road, chromosomes[i], City::nr);
			bestRoad.lg = result.lg;
		}
		sumFitness += chromosomeFitness[i];
	}

	BuildPartialProbabilities(sumFitness, chromosomeFitness, popSize);

	return bestRoad;
}

struct pack Fitness(int chromosome[])
{
	struct pack rez;
	rez.lg = CalcDistDrum(chromosome);
	rez.fitness = 1 / rez.lg;
	return rez;
}

double CalcDistDrum(int drum[])
{
	double lg = 0;

	for (int i = 0; i < City::nr - 1; ++i)
	{
		lg += dist[drum[i]][drum[i + 1]];
	}
	lg += dist[drum[City::nr - 1]][drum[0]];
	return lg;
}

void BuildPartialProbabilities(double sumFitness, double chromosomeFitness[], int popSize)
{
	for (int i = 0; i < popSize; ++i)
		prob[i] = chromosomeFitness[i] / sumFitness;

	probCumulated[0] = 0;
	for (int i = 1; i < popSize; ++i)
		probCumulated[i] = probCumulated[i - 1] + prob[i - 1];
	probCumulated[popSize] = 1.1;
}

int auxChromosomes[MAX_CHROMOSOMES][MAX_CITIES];
void SelectNextPopulation(int chromosomes[][MAX_CITIES], int &popSize)
{
	double randomNr;
	int chosen[MAX_CHROMOSOMES];
	memset(chosen, 0, sizeof(chosen));

	for (int i = 0; i < popSize; ++i)
	{
		randomNr = RandomDouble(0, 1);
		for (int j = 0; j < popSize; ++j)
			if (probCumulated[j] < randomNr && randomNr <= probCumulated[j + 1])
				chosen[i] = j;
	}

	for (int i = 0; i < popSize; ++i)
		Copy(auxChromosomes[i], chromosomes[i], City::nr);

	int i, aux = popSize;
	popSize = 0;
	for (i = 0; i < aux; ++i)
		Copy(chromosomes[popSize++], auxChromosomes[chosen[i]], City::nr);
}

void CrossChromosomes(int chromosomes[][MAX_CITIES], int popSize)
{
	vector<int> chosenForCrossing;
	double randomNr;
	memset(chromosomeWillBeCrossed, 0, sizeof(chromosomeWillBeCrossed));

	for (int i = 0; i < popSize; ++i)
	{
		randomNr = RandomDouble(0, 1);

		if (randomNr < P_CROSS)
		{
			chosenForCrossing.push_back(i);
			chromosomeWillBeCrossed[i] = true;
		}
	}

	if (chosenForCrossing.size() % 2)
	{
		chromosomeWillBeCrossed[chosenForCrossing[chosenForCrossing.size() - 1]] = false;
		chosenForCrossing.pop_back();
	}

	for (unsigned int i = 0; i < chosenForCrossing.size(); i += 2)
	{
		CrossIndividualChromosomes2(chromosomes, chosenForCrossing[i], chosenForCrossing[i + 1]);
		//CrossIndividualChromosomes(chromosomes, chosenForCrossing[i], chosenForCrossing[i + 1]);
	}
}

void CrossIndividualChromosomes(int chromosomes[][MAX_CITIES], int pos1, int pos2)
{
	int start = -1, end = -1, i1, i2;
	bool haveChromosome1[MAX_CITIES], haveChromosome2[MAX_CITIES];
	int newChromosome1[MAX_CITIES], newChromosome2[MAX_CITIES];
	memset(haveChromosome1, 0, sizeof(haveChromosome1));
	memset(haveChromosome2, 0, sizeof(haveChromosome2));

	start = rand() % City::nr;
	end = rand() % (City::nr - start);
	end += start;

	for (int i = start; i <= end; ++i)
	{
		newChromosome1[i] = chromosomes[pos1][i]; //identic
		newChromosome2[i] = chromosomes[pos2][i]; //identic
		haveChromosome1[newChromosome1[i]] = true;
		haveChromosome2[newChromosome2[i]] = true;
	}

	i1 = i2 = 0;
	for (int i = 0; i < City::nr; ++i)
	{
		if (i == start)
		{
			i = end;
			continue;
		}

		//copy in the first chromosome
		while (haveChromosome1[chromosomes[pos2][i2]] == true && i2 < City::nr)
			++i2;
		newChromosome1[i] = chromosomes[pos2][i2];
		haveChromosome1[newChromosome1[i]] = true;

		while (haveChromosome2[chromosomes[pos1][i1]] == true && i1 < City::nr)
			++i1;
		newChromosome2[i] = chromosomes[pos1][i1];
		haveChromosome2[newChromosome2[i]] = true;
	}

	Copy(chromosomes[pos1], newChromosome1, City::nr);
	Copy(chromosomes[pos2], newChromosome2, City::nr);
}

void CrossIndividualChromosomes2(int chromosomes[][MAX_CITIES], int pos1, int pos2)
{
	int split = -1, i1, i2;
	int newChromosome1[MAX_CITIES], newChromosome2[MAX_CITIES];

	split = rand() % City::nr;

	for (int i = 0; i <= City::nr; ++i)
	{
		newChromosome1[i] = chromosomes[pos1][i];
		newChromosome2[i] = chromosomes[pos2][i];
	}

	for (int i = 0; i < split; ++i)
	{
		i1 = i2 = 0;
		while (newChromosome1[i2] != chromosomes[pos2][i] && i2 < City::nr)
			++i2;
		newChromosome1[i2] = newChromosome1[i];
		newChromosome1[i] = chromosomes[pos2][i];

		while (newChromosome2[i1] != chromosomes[pos1][i] && i1 < City::nr)
			++i1;
		newChromosome2[i1] = newChromosome2[i];
		newChromosome2[i] = chromosomes[pos1][i];
	}

	Copy(chromosomes[pos1], newChromosome1, City::nr);
	Copy(chromosomes[pos2], newChromosome2, City::nr);
}

void MutateChromosomesv2(int chromosomes[][MAX_CITIES], int popSize)
{
	double randomNr, lgInitial;
	int randomPos1, randomPos2;

	for (int i = 0; i < popSize; ++i)
	{
		if (chromosomeWillBeCrossed[i])
			continue;

		randomNr = RandomDouble(0, 1);
		if (randomNr <= P_MUTATION)
		{
			lgInitial = CalcDistDrum(chromosomes[i]);
			for (int j = 0; j < MAX_MUTATION_SWAPS / 5; ++j)
			{
				randomPos1 = rand() % City::nr;
				randomPos2 = rand() % City::nr;

				if (randomPos2 < randomPos1)
					swap(randomPos1, randomPos2);

				int st, dr;
				for (st = randomPos1, dr = randomPos2; st < dr; ++st, --dr)
					swap(chromosomes[i][st], chromosomes[i][dr]);

				if (CalcDistDrum(chromosomes[i]) < lgInitial)
					continue;

				for (st = randomPos1, dr = randomPos2; st < dr; ++st, --dr)
					swap(chromosomes[i][st], chromosomes[i][dr]);
			}

			/*for (int j = 0; j < MAX_MUTATION_SWAPS ; ++j) {
				randomPos1 = rand() % City::nr;
				randomPos2 = rand() % City::nr;

				swap(chromosomes[i][randomPos1], chromosomes[i][randomPos2]);

				if (CalcDistDrum(chromosomes[i]) < lgInitial)
					continue;

				swap(chromosomes[i][randomPos1], chromosomes[i][randomPos2]);
			}*/
		}
	}
}

void MutateChromosomes(int chromosomes[][MAX_CITIES], int popSize)
{
	double randomNr;

	for (int i = 0; i < popSize; ++i)
	{
		if (chromosomeWillBeCrossed[i])
			continue;

		randomNr = RandomDouble(0, 1);
		if (randomNr <= P_MUTATION)
			swap(chromosomes[i][rand() % City::nr], chromosomes[i][rand() % City::nr]);

		/*for (int j = 0; j < City::nr; ++j) {
			randomNr = RandomDouble(0, 1);
			if (randomNr <= P_MUTATION) {
				swap(chromosomes[i][j], chromosomes[i][rand() % City::nr]);
			}
		}*/
	}
}

void Copy(int unde[], int deUnde[], int cate)
{
	for (int i = 0; i < cate; ++i)
		unde[i] = deUnde[i];
}

double RandomDouble(const double &minVal, const double &maxVal)
{
	double f;
	f = (double)rand() / RAND_MAX;
	return minVal + f * (maxVal - minVal);
}

struct BestRoad Heuristic()
{
	int drum[MAX_CITIES], lgDrum;
	bool haveCity[MAX_CITIES];
	double bestDist, distDrum;
	int bestNeighbour;
	struct BestRoad rez;

	rez.lg = INF;

	for (int startVf = 0; startVf < City::nr; ++startVf)
	{

		memset(haveCity, 0, sizeof(haveCity));
		drum[0] = startVf;
		haveCity[drum[0]] = true;

		for (lgDrum = 1; lgDrum < City::nr; ++lgDrum)
		{
			//pick nearest city, not taken
			bestDist = INF;

			for (int i = 0; i < City::nr; ++i)
				if (!haveCity[i] && dist[drum[lgDrum - 1]][i] < bestDist)
				{
					bestDist = dist[drum[lgDrum - 1]][i];
					bestNeighbour = i;
				}

			drum[lgDrum] = bestNeighbour;
			haveCity[bestNeighbour] = true;
		}

		distDrum = CalcDistDrum(drum);
		if (distDrum < rez.lg)
		{
			rez.lg = distDrum;
			Copy(rez.road, drum, City::nr);
		}
	}

	return rez;
}