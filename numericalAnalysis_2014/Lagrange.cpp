#include <iostream>
using namespace std;

struct SPair {
	double x;
	double y;
};

int main() {
	SPair nodes[9];

	// input.
	for (int i = 0; i < 9; i++) {
		double a, b;
		cin >> a >> b;
		nodes[i].x = a;
		nodes[i].y = b;
	}

	cout << "L8(x) =";
	double coefficients[9] = {};
	for (int i = 0; i < 9; i++) {
		cout << " +" << nodes[i].x;
		for (int j = 0; j < 9; j++) {
			if (j == i) continue;
			cout << "*(x-" << nodes[j].x << ")/(" << nodes[i].x << "-" << nodes[j].x << ")";
		}
	}

	/*	// input self-variable.
	double xtarg;
	cin >> xtarg;

	// get all minorls.
	double minorls[9];
	for (int i = 0; i < 9; i ++) {
	minorls[i] = 1;
	for (int j = 0; j < 9; j ++) {
	if (j == i) continue;
	minorls[i] *= (xtarg - nodes[j].x) / (nodes[i].x - nodes[j].x);
	}
	}

	// get result.
	double result = 0;
	for (int i = 0; i < 9; i ++) {
	result += nodes[i].y * minorls[i];
	}

	cout << result << endl;
	*/

	system("pause");
	return 0;
}