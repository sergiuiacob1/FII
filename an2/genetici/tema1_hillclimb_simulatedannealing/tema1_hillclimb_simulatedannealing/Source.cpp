#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#define DMAX 100
#define INF 999999999
#define PRECISION 0.1
#define PI 3.14159265

using namespace std;

struct pack {
	long double minValue, maxValue, average, deviation;
};
vector <long double> valIteration;

double DeJong(double[], int);
double SixHump(double[], int);
double Schwefel7(double[], int);
double Rastrigin(double[], int);
struct pack runFunction(double(*algorithm)(double(*testFunction)(double[], int), double[][2], int),
	double(*testFunction)(double[], int),
	int, int, double, double);

double randomDouble(const double &, const double &);
void generateNeighbours(vector <double>, double, int);
int binaryToInt(char[], int);
void copy(double[], double[], int);
double generateOneNeighbour(double, int);

double HillClimb(double(*testFunction)(double[], int), double[][2], int);
double SimulatedAnnealing(double(*testFunction)(double[], int), double[][2], int);
inline bool badValueIsAccepted(double delta, double temperature);

int main() {
	srand((unsigned int)time(NULL));
	struct pack rez;
	//double acceptedVals[DMAX][2];

	rez = runFunction(HillClimb, DeJong, 30, 100, -5.12, 5.12);
	cout << rez.minValue << ' ' << rez.average << ' ' << rez.maxValue << ' ' << rez.deviation << "\n\n";

	
	/*acceptedVals[0][0] = -500; acceptedVals[0][1] = 500;
	cout << "Hill Climb, val. minima pentru Schwefel 7: " << HillClimb(Schwefel7, acceptedVals, 1) << '\n';
	cout << "Simulated Annealing, val. minima pentru Schwefel 7: " << SimulatedAnnealing(Schwefel7, acceptedVals, 1) << '\n';

	cout << '\n';

	acceptedVals[0][0] = -5.12; acceptedVals[0][1] = 5.12;
	acceptedVals[1][0] = -5.12; acceptedVals[1][1] = 5.12;
	cout << "Hill Climb, val. minima pentru Rastrigin: " << HillClimb(Rastrigin, acceptedVals, 2) << '\n';
	cout << "Simulated Annealing, val. minima pentru Rastrigin: " << SimulatedAnnealing(Rastrigin, acceptedVals, 2) << '\n';

	cout << '\n';

	acceptedVals[0][0] = -3; acceptedVals[0][1] = 3;
	acceptedVals[1][0] = -2; acceptedVals[1][1] = 2;
	cout << "Hill Climb, val. minima pentru Six Hump Camel: " << HillClimb(SixHump, acceptedVals, 2) << '\n';
	cout << "Simulated Annealing, val. minima pentru Six Hump Camel: " << SimulatedAnnealing(SixHump, acceptedVals, 2) << '\n';

	cout << '\n';
	*/

	getchar();
	return 0;
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

double HillClimb(double(*testFunction)(double[], int), double acceptedVals[][2], int nrVals) {
	double v[DMAX], bestSol = INF, functionValue;
	vector <double> neighbours;
	int nrIterations = 10000, randomPoz;
	bool local;

	for (int i = 0; i < nrIterations; ++i) {
		for (int j = 0; j < nrVals; ++j)
			v[j] = randomDouble(acceptedVals[j][0], acceptedVals[j][1]);
		functionValue = testFunction(v, nrVals);
		bestSol = min(functionValue, bestSol);

		local = true;
		while (local) {
			randomPoz = rand() % nrVals;
			generateNeighbours(neighbours, v[randomPoz], 0);
			local = false;
			
			for (auto it : neighbours) {
				v[randomPoz] = it;
				functionValue = testFunction(v, nrVals);
				if (functionValue < bestSol) {
					bestSol = functionValue;
					local = true;
				}
			}
		}
	}

	return bestSol;
}

double SimulatedAnnealing(double(*testFunction)(double[], int), double acceptedVals[][2], int nrVals) {
	double v[DMAX], bestSol = INF, functionValue, temperature, bestNeighbourVal;
	double coolingRate, absoluteTemperature;
	vector <double> neighbours;
	int nrIterations = 1000, randomPoz;
	bool local;
	coolingRate = 2.1;
	absoluteTemperature = 0.00001;

	for (int i = 0; i < nrIterations; ++i) {
		for (int j = 0; j < nrVals; ++j)
			v[j] = randomDouble(acceptedVals[j][0], acceptedVals[j][1]);
		bestSol = min(bestSol, testFunction(v, nrVals));

		temperature = 50;//temperatura trebuie sa scada
		local = true;
		while (local && temperature > absoluteTemperature) {
			randomPoz = rand() % nrVals;
			generateNeighbours(neighbours, v[randomPoz], 0);
			local = false;
			bestNeighbourVal = INF;

			for (auto it : neighbours) {
				v[randomPoz] = it;
				functionValue = testFunction(v, nrVals);
				bestNeighbourVal = min(functionValue, bestNeighbourVal);

				if (functionValue < bestSol) {
					bestSol = functionValue;
					local = true;
				}
			}

			if (!local && badValueIsAccepted(bestSol - bestNeighbourVal, temperature))//nu mi s-a schimbat nimic
				local = true;

			temperature /= coolingRate;
		}
	}

	return bestSol;
}

inline bool badValueIsAccepted(double delta, double temperature) {
	return (randomDouble(0, 0.9999999999999) < exp(-delta / temperature));
}

double randomDouble(const double &minVal, const double &maxVal) {
	double f;
	f = (double)rand() / RAND_MAX;
	return minVal + f * (maxVal - minVal);
}

void generateNeighbours(vector <double> neighbours, double value, int discreteFactor) {
	int integerValue, lg, p10 = 1, semn;
	char binary[64] = { 0 };

	p10 = (int)pow(10, discreteFactor);

	integerValue = (int)(value * p10);

	if (integerValue < 0) semn = -1;
	else semn = 1;

	if (!integerValue)
		lg = 1;
	else
		lg = 0;

	integerValue *= semn;

	for (; integerValue; ++lg) {
		binary[lg] = integerValue % 2;
		integerValue /= 2;
	}

	for (int i = 0; i < lg - 1; ++i) {//la ultimul bit daca e 0, nu il fac 1; posibil sa ies din intervalul valorilor acceptate
		binary[i] = 1 - binary[i];
		neighbours.push_back(semn * (double)binaryToInt(binary, lg) / p10);
		binary[i] = 1 - binary[i];
	}

	if (binary[lg - 1] == 1) {
		binary[lg - 1] = 0;
		neighbours.push_back(semn *(double)binaryToInt(binary, lg) / p10);
	}
}

double generateOneNeighbour(double value, int discreteFactor) {
	int integerValue, lg, p10 = 1, randomPoz, semn;
	char binary[64] = { 0 };

	p10 = (int)pow(10, discreteFactor);
	integerValue = (int)(value * p10);
	if (integerValue < 0) semn = -1;
	else semn = 1;
	integerValue *= semn;

	if (!integerValue)	lg = 1;
	else lg = 0;

	for (; integerValue; ++lg) {
		binary[lg] = integerValue % 2;
		integerValue /= 2;
	}

	randomPoz = rand() % lg; // ultimul bit e caz special
	binary[randomPoz] = 1 - binary[randomPoz];
	return semn*((double)binaryToInt(binary, lg) / p10);
}

int binaryToInt(char binary[], int lg) {
	int rez, p2, i;

	for (rez = 0, p2 = 1, i = 0; i < lg; ++i, p2 *= 2)
		rez += p2*binary[i];

	return rez;
}

void copy(double unde[], double deUnde[], int cate) {
	for (int i = 0; i < cate; ++i)
		unde[i] = deUnde[i];
}

struct pack runFunction(
	double (*algorithm)(double(*testFunction)(double vals[], int nrVals), double [][2], int),
	double(*testFunction)(double vals[], int nrVals),
	int dimension, int nrRulari, double acceptedMin, double acceptedMax) {
	double acceptedVals[DMAX][2], minValue, maxValue, average, val;
	long double valSum, dispersion;
	struct pack rez;

	for (int i = 0; i < dimension; ++i) {
		acceptedVals[i][0] = acceptedMin;
		acceptedVals[i][1] = acceptedMax;
	}

	//acceptedVals[0][0] = -3; acceptedVals[0][1] = 3;
	//acceptedVals[1][0] = -2; acceptedVals[1][1] = 2;
	
	minValue = INF; maxValue = -INF; valSum = 0;
	valIteration.clear();
	dispersion = 0;

	for (int i = 0; i < nrRulari; ++i) {
		val = algorithm(testFunction, acceptedVals, dimension);
		minValue = min(minValue, val);
		maxValue = max(maxValue, val);
		valSum += val;
		valIteration.push_back(val);
	}
	average = valSum / nrRulari;

	rez.average = average; rez.minValue = minValue; rez.maxValue = maxValue;
	//aflu deviatia standard
	for (int i = 0; i < valIteration.size(); ++i) {
		dispersion += (valIteration[i] - rez.average) * (valIteration[i] - rez.average);
	}
	dispersion /= (dimension - 1);
	rez.deviation = sqrt(dispersion);
	return rez;
}