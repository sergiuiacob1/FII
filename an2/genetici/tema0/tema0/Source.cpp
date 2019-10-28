#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>
#define DMAX 100
#define INF 999999999
#define PRECISION 0.1
#define PI 3.14159265

using namespace std;

double DeJong(double [], int);
double SixHump(double[], int);
double Schwefel7(double[], int);
double Rastrigin(double[], int);

double randomDouble(const double &, const double &);
void generateNeighbours(vector <double>, double, int);
int binaryToInt(char[], int);
void copy(double[], double[], int);
double generateOneNeighbour(double, int);

double HillClimb(double(*testFunction)(double[], int), double[][DMAX], int);
double SimulatedAnnealing(double(*testFunction)(double[], int), double[][DMAX], int);
double GetFunctionMin(double(*testFunction)(double[], int), double[][DMAX], int);

int main() {
	srand((unsigned int)time(NULL));
	double acceptedVals[DMAX][DMAX];
	acceptedVals[0][0] = -5.12; acceptedVals[0][1] = 5.12;
	acceptedVals[1][0] = -5.12; acceptedVals[1][1] = 5.12;
	acceptedVals[2][0] = -5.12; acceptedVals[2][1] = 5.12;
	cout << "Hill Climb, val. minima pentru DeJong: " << HillClimb(DeJong, acceptedVals, 3) << '\n';
	cout << "Functia mea, val. minima pentru DeJong: " << GetFunctionMin(DeJong, acceptedVals, 3) << '\n';

	cout << '\n';

	acceptedVals[0][0] = -500; acceptedVals[0][1] = 500;
	cout << "Hill Climb, val. minima pentru Schwefel 7: " << HillClimb(Schwefel7, acceptedVals, 1) << '\n';
	cout << "Functia mea, val. minima pentru Schwefel 7: " << GetFunctionMin(Schwefel7, acceptedVals, 1) << '\n';

	cout << '\n';

	acceptedVals[0][0] = -5.12; acceptedVals[0][1] = 5.12;
	acceptedVals[1][0] = -5.12; acceptedVals[1][1] = 5.12;
	cout << "Hill Climb, val. minima pentru Rastrigin: " << HillClimb(Rastrigin, acceptedVals, 2) << '\n';
	cout << "Functia mea, val. minima pentru Rastrigin: " << GetFunctionMin(Rastrigin, acceptedVals, 2) << '\n';

	cout << '\n';

	acceptedVals[0][0] = -3; acceptedVals[0][1] = 3;
	acceptedVals[1][0] = -2; acceptedVals[1][1] = 2;
	cout << "Hill Climb, val. minima pentru Six Hump Camel: " << HillClimb(SixHump, acceptedVals, 2) << '\n';
	cout << "Functia mea, val. minima pentru Six Hump Camel: " << GetFunctionMin(SixHump, acceptedVals, 2) << '\n';

	cout << '\n';

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

	functionValue = (4 - 2.1*v[0]*v[0] + v[0]*v[0]*v[0]*v[0]/3)*v[0]*v[0] + v[0]*v[1] + (-4 + 4*v[1]*v[1])*v[1]*v[1];

	return functionValue;
}

double Schwefel7(double v[], int nrVals) {
	double result = 0;
	for (int i = 0 ; i < nrVals; ++i)
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
		result += v[i] * v[i] - 10 * cos(2*PI*v[i]);

	return result;
}


double GetFunctionMin(double(*testFunction)(double[], int), double acceptedVals[][DMAX], int nrVals) {
	double v[DMAX], bestSol = INF, functionValue, lgInterval, bestValYet, sqrtValue;
	int nrIterations;

	nrIterations = 10000;
	for (int k = 0; k < nrIterations; ++k) {
		for (int i = 0; i < nrVals; ++i) {
			for (int j = i + 1; j < nrVals; ++j)
				v[j] = randomDouble(acceptedVals[j][0], acceptedVals[j][1]);

			lgInterval = acceptedVals[i][1] - acceptedVals[i][0];
			bestValYet = sqrt(lgInterval);

			for (sqrtValue = sqrt(lgInterval); acceptedVals[i][0] + sqrtValue <= acceptedVals[i][1]; sqrtValue += sqrt(lgInterval)) {
				v[i] = acceptedVals[i][0] + sqrtValue;
				functionValue = testFunction(v, nrVals);
				if (functionValue < bestSol) {
					bestSol = functionValue;
					bestValYet = sqrtValue;

				}
			}

			for (sqrtValue = bestValYet - sqrt(lgInterval);
				sqrtValue <= bestValYet + sqrt(lgInterval) && acceptedVals[i][0] + sqrtValue <= acceptedVals[i][1];
				sqrtValue += PRECISION) {
				v[i] = acceptedVals[i][0] + sqrtValue;
				functionValue = testFunction(v, nrVals);
				if (functionValue < bestSol) {
					bestSol = functionValue;
					bestValYet = sqrtValue;
				}
			}
			v[i] = acceptedVals[i][0] + bestValYet;
		}
	}

	return bestSol;
}

double HillClimb(double(*testFunction)(double [], int), double acceptedVals[][DMAX], int nrVals) {
	double v[DMAX], bestSol = INF, functionValue, previousVal;
	vector <double> neighbours;
	int nrIterations = 10000, randomPoz;

	/*for (int j = 0; j < nrVals; ++j)
		v[j] = randomDouble(acceptedVals[j][0], acceptedVals[j][1]);
	bestSol = testFunction(v, nrVals);

	for (int i = 0; i < nrIterations; ++i) {
		randomPoz = rand() % nrVals;
		previousVal = v[randomPoz];
		v[randomPoz] = generateOneNeighbour(v[randomPoz], 2);

		functionValue = testFunction(v, nrVals);
		if (functionValue < bestSol)
			bestSol = functionValue;
		else
			v[randomPoz] = previousVal;
	}*/
	
	for (int i = 0; i < nrIterations; ++i) {
		for (int j = 0; j < nrVals; ++j)
			v[j] = randomDouble(acceptedVals[j][0], acceptedVals[j][1]);

		functionValue = testFunction(v, nrVals);
		if (functionValue < bestSol) bestSol = functionValue;

		for (int k = 0; k < nrVals; ++k) {

			neighbours.clear();
			generateNeighbours(neighbours, v[k], 2);

			previousVal = v[k];
			for (unsigned int k = 0; k < neighbours.size(); ++k)
			{
				v[k] = neighbours[k];
				functionValue = testFunction(v, nrVals);
				if (functionValue < bestSol) bestSol = functionValue;
			}

			v[k] = previousVal;
		}
	}

	return bestSol;
}

double SimulatedAnnealing(double(*testFunction)(double[], int), double acceptedVals[][DMAX], int nrVals) {
	double v[DMAX], bestSol = INF, functionValue, previousVal;
	vector <double> neighbours;
	int nrIterations;

	nrIterations = 10000;
	for (int i = 0; i < nrIterations; ++i) {
		for (int j = 0; j < nrVals; ++j)
			v[j] = randomDouble(acceptedVals[j][0], acceptedVals[j][1]);

		functionValue = testFunction(v, nrVals);
		if (functionValue < bestSol) bestSol = functionValue;

		for (int k = 0; k < nrVals; ++k) {

			neighbours.clear();
			generateNeighbours(neighbours, v[k], 2);

			previousVal = v[k];
			for (unsigned int k = 0; k < neighbours.size(); ++k)
			{
				v[k] = neighbours[k];
				functionValue = testFunction(v, nrVals);
				if (functionValue < bestSol) bestSol = functionValue;
			}

			v[k] = previousVal;
		}
	}

	return bestSol;
}

double randomDouble(const double &minVal, const double &maxVal) {
	double f;
	f = (double)rand() / RAND_MAX;
	return minVal + f * (maxVal - minVal);
}

void generateNeighbours(vector <double> neighbours, double value, int discreteFactor) {
	int integerValue, lg, p10 = 1;
	char binary[64] = { 0 };

	for (int i = 0; i < discreteFactor; ++i)
		p10 *= 10;

	//neighbours.clear();

	integerValue = (int)(value * p10);
	for (lg = 0; integerValue; ++lg) {
		binary[lg] = integerValue % 2;
		integerValue /= 2;
	}
	//if (!integerValue) lg = 1; AICI TREBUIE MODIFICAAAAAAAAAAAAAAAAAAAAAAAATFIFIFIFICATFICATFICAAAAAAAAAAAAAAT

	for (int i = 0; i < lg - 1; ++i) {//la ultimul bit daca e 0, nu il fac 1; posibil sa ies din intervalul valorilor acceptate
		binary[i] = 1 - binary[i];
		neighbours.push_back((double)binaryToInt(binary, lg)/p10);
		binary[i] = 1 - binary[i];
	}

	if (binary[lg - 1] == 1) {
		binary[lg - 1] = 0;
		neighbours.push_back((double)binaryToInt(binary, lg)/p10);
	}
}

double generateOneNeighbour(double value, int discreteFactor) {
	int integerValue, lg, p10 = 1, randomPoz;
	char binary[64] = { 0 };

	for (int i = 0; i < discreteFactor; ++i)
		p10 *= 10;

	integerValue = (int)(value * p10);
	for (lg = 0; integerValue; ++lg) {
		binary[lg] = integerValue % 2;
		integerValue /= 2;
	}

	if (!integerValue) lg = 1;

	randomPoz = rand() % lg; // ultimul bit il las la o parte, caz special
	binary[randomPoz] = 1 - binary[randomPoz];
	return (double)binaryToInt(binary, lg) / p10;
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