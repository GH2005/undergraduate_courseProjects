// Columns' Main Elements Elimination.
// coded by 3010216107 Õı—Ó.

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {

	// input extended matrix.

	int dim = 0;
	cout << "Input the dimension of the coefficient matrix:\n";
	cin >> dim;
	
	typedef double* RowType;
	double ** eMartrix = new RowType[dim];
	for (int i = 0; i < dim; i++) {
		eMartrix[i] = new double[dim + 1];
		for (int j = 0; j < dim + 1; j++) {
			eMartrix[i][j] = 0.0f;
		}
	}

	cout << "Input the extended matrix for the formula group:\n";
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim + 1; j++) {
			cin >> eMartrix[i][j];
		}
	}

	// elimination.

	double det = 1.0f;
	for (int i = 0; i < dim - 1; i++) {	// for the ith scale.

		// get the max main element.
		 
		int rIdxMaxMainElement = i;
		double maxMainElementAbs = abs(eMartrix[i][i]);
		for (int j = i + 1; j < dim; j++) {
			if (abs(eMartrix[j][i]) > maxMainElementAbs) {
				rIdxMaxMainElement = j;
				maxMainElementAbs = abs(eMartrix[j][i]);
			}
		}

		// branches.
		
		if (maxMainElementAbs == 0) {
			cout << "maxMainElementAbs == 0 when scale " << i << endl;
			system("pause");
			return 1;
		}

		if (rIdxMaxMainElement != i) {
			RowType tempRow = eMartrix[rIdxMaxMainElement];
			eMartrix[rIdxMaxMainElement] = eMartrix[i];
			eMartrix[i] = tempRow;
			det = -det;
		}

		// core elimination.

		for (int j = i + 1; j < dim; j++) {
			double m = eMartrix[j][i] / eMartrix[i][i];
			for (int k = 0; k < dim + 1; k++) {
				eMartrix[j][k] -= m * eMartrix[i][k];
			}
		}

		det = eMartrix[i][i];
	}

	if (eMartrix[dim - 1][dim - 1] == 0) {
		cout << "maxMainElementAbs == 0 when scale " << dim - 1 << endl;
		system("pause");
		return 1;
	}

	// compute the solution.

	eMartrix[dim - 1][dim] = eMartrix[dim - 1][dim] / eMartrix[dim - 1][dim - 1];
	for (int i = dim - 2; i >= 0; i--) {
		double theSum = 0.0f;
		for (int j = i + 1; j < dim; j++) {
			theSum += eMartrix[i][j] * eMartrix[j][dim];
		}
		eMartrix[i][dim] = (eMartrix[i][dim] - theSum) / eMartrix[i][i];
	}

	det = eMartrix[dim - 1][dim - 1] * det;

	// output.

	cout << "The Solution Vector:";
	for (int i = 0; i < dim; i++) {
		cout << ' ' << fixed << setprecision(4) << eMartrix[i][dim];
	}
	cout << ".\n";

	// cleanups, I do not feel like implementing them.

	system("pause");
	return 0;
}