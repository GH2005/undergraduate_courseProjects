#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

inline double f(double x) {
	return sqrt(x) * log(x);
}

inline double x(double k, double h) {
	return 0 + k * h;
}

int main() {

	// input the number of proportions and the scale of T-martrix for Romberg Integration.
	int cDivision = 0, scale = 0;
	cin >> cDivision >> scale;
	double h = double(1.0) / cDivision;

	// compute the compound trapezium formula.
	double ctfMid = 0;
	for (int i = 1; i <= cDivision - 1; i++) {
		ctfMid += f(x(i, h));
	}
	double reCTF = h / 2 * (f(0.000000000000000000000000000000000000000000000000000000000001L) + f(1) + 2 * ctfMid);
	cout << "Integration by Compound Trapezium Formula: " << fixed << reCTF << ".\n";

	// compute the compound simpson formula.
	double csfMid1 = 0;
	double csfMid2 = 0;
	for (int i = 0; i <= cDivision - 1; i++) {
		csfMid1 += f(x(double(i) + 0.5, h));
	}
	for (int i = 1; i <= cDivision - 1; i++) {
		csfMid2 += f(x(i, h));
	}
	double reCSF = h / 6 * (f(0.000000000000000000000000000000000000000000000000000000000001L) + f(1) + 4 * csfMid1 + 2 * csfMid2);
	cout << "Integration by Compound Simpson Formula: " << fixed << reCSF << ".\n";

	// compute the Romberg integration.
	typedef double * MartrixRow;
	MartrixRow * tmartrix = new MartrixRow[scale];
	for (int i = 0; i < scale; i++) {
		tmartrix[i] = new double[scale];
		for (int j = 0; j < scale; j++) {
			tmartrix[i][j] = 0L;
		}
	}

	h = 1.0L;
	cDivision = 1;

	// acquiring the first column: tmartrix[0 -> scale - 1][0].
	tmartrix[0][0] = h / 2 * (f(0.000000000000000000000000000000000000000000000000000000000001L) + f(1));
	for (int i = 1; i < scale; i++) {

		double riMid1 = 0;
		for (int j = 0; j < cDivision; j++) {
			f(x(double(j) + 0.5, h));
		}
		tmartrix[i][0] = tmartrix[i - 1][0] / 2 + h / 2 * riMid1;

		h /= 2;
		cDivision *= 2;
	}
	// acceleration.
	for (int j = 1; j < scale; j++) {
		for (int i = 0; i < scale - j; i++) {
			double theCom = pow(4.0, j);
			tmartrix[i][j] = theCom / (theCom - 1) * tmartrix[i + 1][j - 1] - 1.0 / (theCom - 1) * tmartrix[i][j - 1];
		}
	}
	cout << scientific << "The T[i][j] martrix: \n";
	for (int i = 0; i < scale; i++) {
		for (int j = 0; j < scale; j++) {
			cout << setw(12) << setprecision(4) << tmartrix[i][j] << ' ';
		}
		cout << endl;
	}

	cout << "Integration By Romberg Formula: " << tmartrix[0][scale - 1] << ".\n";

	for (int i = 0; i < scale; i++) {
		delete[] tmartrix[i];
	}
	delete[] tmartrix;

	system("pause");
	return 0;
}