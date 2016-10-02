#include <iostream>
using namespace std;

struct Spair{
	double x;
	double y;
};

int main() {
	Spair nodes[9];

	// input.
	for (int i = 0; i < 9; i++) {
		cin >> nodes[i].x >> nodes[i].y;
	}

	double f0tilt, fntilt;
	cin >> f0tilt >> fntilt;

	// intermediete variables.
	double h[8];
	for (int i = 0; i < 8; i++) {
		h[i] = nodes[i + 1].x - nodes[i].x;
	}

	double u[9], r[8], d[9];		// u[8], r[0] and d[0]d[8] need to be got later. u[0] is of no use.
	for (int i = 1; i < 8; i++) {
		u[i] = h[i - 1] / (h[i - 1] - h[i]);
		r[i] = h[i] / (h[i - 1] + h[i]);
		double diff1 = (nodes[i].y - nodes[i + 1].y) / (nodes[i].x - nodes[i + 1].x);
		double diff2 = (nodes[i - 1].y - nodes[i].y) / (nodes[i - 1].x - nodes[i].x);
		d[i] = 6 * (diff1 - diff2) / (h[i - 1] + h[i]);
	}
	r[0] = 1;
	u[8] = 1;		// this indicates the first border requisite.
	d[0] = 6 / h[0] * ((nodes[0].y - nodes[1].y) / (nodes[0].x - nodes[1].x) - f0tilt);
	d[8] = 6 / h[7] * (fntilt - (nodes[7].y - nodes[8].y) / (nodes[7].x - nodes[8].x));

	// to solve the three-corner relevant martrix.
	double M[9], ctilt[8], dtilt[9];
	ctilt[0] = r[0] / 2;
	dtilt[0] = d[0] / 2;

	for (int i = 1; i < 8; i++) {
		ctilt[i] = r[i] / (2 - ctilt[i - 1] * u[i]);
		dtilt[i] = (d[i] - dtilt[i - 1] * u[i]) / (2 - ctilt[i - 1] * u[i]);
	}
	dtilt[8] = (d[8] - dtilt[7] * u[8]) / (2 - ctilt[7] * u[8]);

	M[8] = dtilt[8];
	for (int i = 7; i >= 0; i--) {
		M[i] = dtilt[i] - ctilt[i] * M[i + 1];
	}

	// output result.
	for (int i = 0; i < 8; i++) {
		cout << "S" << i << "(x) = " << M[i] / 6 / h[i] << "(" << nodes[i + 1].x << "-x)^3"
			<< " + " << M[i + 1] / 6 / h[i] << "(x-" << nodes[i].x << ")^3"
			<< " + " << (nodes[i].y - M[i] * h[i] * h[i] / 6) / h[i] << "(" << nodes[i + 1].x << "-x)"
			<< " + " << (nodes[i + 1].y - M[i + 1] * h[i] * h[i] / 6) / h[i] << "(x-" << nodes[i].x << ")\n";
	}

	system("pause");
	return 0;
}