// Adams Solution to ordinary differential equation of level four with prediction and
// correction, started with Runge-Kutta approach of level four.
// coded by 3010216107 Õı—Ó.

#include <iostream>
#include <iomanip>
using namespace std;

// I can't recognize an equation input from istream, so plz set the equation here:
// below, double dy = f(x, y).
// dy = -y + x + 1 is an example in page 300 of the textbook.

double Dy(double x, double y) {
	return -y + x + 1;
}

double RungeKutta4(double yn, double xn, double h) { // One step Runge-Kutta approach.
	double k1 = Dy(xn, yn);
	double k2 = Dy(xn + h / 2, yn + h * k1 / 2);
	double k3 = Dy(xn + h / 2, yn + h * k2 / 2);
	double k4 = Dy(xn + h, yn + h * k3);
	return yn + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
}

double Adams4PreCorr(double ynplus3, double fnplus3, double fnplus2, double fnplus1, 
	double fn, double h, double xnplus4) {	// Adams computing.
	double ypnplus4 = ynplus3 + h / 24 * (55 * fnplus3 - 59 * fnplus2 + 37 * fnplus1 - 9 * fn);
	double fpnplus4 = Dy(xnplus4, ypnplus4);
	return ynplus3 + h / 24 * (9 * fpnplus4 + 19 * fnplus3 - 5 * fnplus2 + fnplus1);
}


int main() {

	// set x0, y(x0) and h here.
	// same example in page 300 of the textbook.

	double x0 = 0.0f;
	double y_x0 = 1.0f;
	double h = 0.1f;

	// set the count of value points needed besides the four start point.

	int n = 20;

	// using Runge-Kutta apporach of level four to start.

	double* solutions = new double[n + 4];
	solutions[0] = y_x0;
	for (int i = 1; i <= 3; i++) {
		solutions[i] = RungeKutta4(solutions[i - 1], x0 + i * h, h);
	}

	// using Adams Solution to ordinary differential equation of level four 
	// with prediction and correction to compute the rest required points.

	for (int i = 4; i < 4 + n; i++) {

		// double Adams4PreCorr(double ynplus3, double fnplus3, double fnplus2, double fnplus1, 
		// double fn, double h, double xnplus4)

		solutions[i] = Adams4PreCorr(solutions[i - 1], Dy(x0 + (i - 1) * h, solutions[i - 1]),
			Dy(x0 + (i - 2) * h, solutions[i - 2]), Dy(x0 + (i - 3) * h, solutions[i - 3]),
			Dy(x0 + (i - 4) * h, solutions[i - 4]), h, x0 + i * h);
	}

	cout << "Solution (x, y(x)):\n";
	for (int i = 0; i < 4 + n; i++) {
		cout << " (" << fixed << setprecision(4) << x0 + i * h << ", " << solutions[i] << ")";
	}
	cout << "\n";

	delete[] solutions;
	system("pause");
	return 0;
}