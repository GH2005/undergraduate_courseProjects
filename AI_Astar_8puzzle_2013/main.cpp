// practice of the course of AI fundamental.
// coded by 3010216107 Õı—Ó.

#include <iostream>
#include <iomanip>
#include <queue>									// for priority queue.
#include <assert.h>
#include <time.h>
using namespace std;

// a node in BFS.
struct State {
public:
	int	dim;											// martrix's side length.
	int *	details;										// real contents in details. 0 for the blank content.
	int * indexes;										// indexes for each content saved in this array.
	int	heuristicValue;							// the less, the good.

	State(int inDim) : dim(inDim), heuristicValue(0) {		// object state' s heuristicValue == 0;
		// this->details and this->indexes must be filled before usage.
		this->details = new int[dim * dim];
		this->indexes = new int[dim * dim];
	}
	~State() {
		delete[] this->details;
		delete[] this->indexes;
	}

	void Print() {
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				if (this->details[i * dim + j] == 0) {
					cout << setw(3) << ' ' << ' ';
				}
				else {
					cout << setw(3) << this->details[i * dim + j] << ' ';
				}
			}
			cout << endl;			
		}
		cout << "heuristicValue == " << this->heuristicValue << ".\n";
	}

	void SetHeuristicValue(State * inObjState) {
		assert(inObjState->dim == this->dim);

		// I think the module and quotient of difference between two numbers' indexes divided by
		// this->dim is suitable to be a Heuristic Value.

		for (int i = 0; i < this->dim * dim; i++) {
			this->heuristicValue += this->GetOneHeuristicValue(this->indexes[i], inObjState->indexes[i]);
		}
	}

	State * MovedNewState(State * inObjState, int detailOutOfBlank) {
		// every step is about position changing between details[0] and details[detailOutOfBlank].
		// return value is a State which is convenient to be added into a priority pq.

		State * pReturn = new State(this->dim);

		//copy values.
		for (int i = 0; i < this->dim * dim; i++) {
			pReturn->details[i] = this->details[i];
			pReturn->indexes[i] = this->indexes[i];
		}

		// switch values.
		int this0Index = this->indexes[0];
		int thisOutIndex = this->indexes[detailOutOfBlank];
		pReturn->indexes[0] = this->indexes[detailOutOfBlank];
		pReturn->indexes[detailOutOfBlank] = this->indexes[0];
		pReturn->details[this0Index] = this->details[thisOutIndex];
		pReturn->details[thisOutIndex] = this->details[this0Index];

		// recalculate heuristiacValue.
		pReturn->heuristicValue = this->heuristicValue - this->GetOneHeuristicValue(this->indexes[0], inObjState->indexes[0])
			- this->GetOneHeuristicValue(this->indexes[detailOutOfBlank], inObjState->indexes[detailOutOfBlank])
				+ this->GetOneHeuristicValue(pReturn->indexes[0], inObjState->indexes[0])
					+ this->GetOneHeuristicValue(pReturn->indexes[detailOutOfBlank], inObjState->indexes[detailOutOfBlank]);

		return pReturn;
	}

protected:
	int GetOneHeuristicValue(int index1, int index2) {
		int largerIndex, smallerIndex;
		if (index1 > index2) {
			largerIndex = index1;
			smallerIndex = index2;
		}
		else {
			largerIndex = index2;
			smallerIndex = index1;
		}
		return (largerIndex - smallerIndex) / this->dim + (largerIndex - smallerIndex) % this->dim;
	}

public:
	// operator = overloading.
	bool operator == (State & refOtherStt) {
		bool allSame = true;
		for (int i = 0; i < this->dim * this->dim; i++) {
			if (this->details[i] != refOtherStt.details[i]) {
				allSame = false;
				break;
			}
		}
		return allSame;
	}
};

// priority queues need a comparision function.
struct cmp {
	bool operator () (State * pState1, State * pState2) {
		if (pState1->heuristicValue > pState2->heuristicValue) return true;
		else return false;
	}
};

// used to generate random formation of a martrix.
struct RdmSeqList {
	int * contents;
	RdmSeqList(int inDim) {
		// it is possible to get the count of reversals, and I force it to be odd.
		// -_- need repairing.
		this->contents = new int[inDim * inDim];

		while (1) {
			int cReversals = 0;			
			for (int i = 0; i < inDim * inDim; i++) {
				this->contents[i] = i;
			}
			for (int i = 0; i < inDim * inDim; i++) {
				int rSelected = rand() % inDim * inDim;
				int temp = this->contents[i];
				this->contents[i] = this->contents[rSelected];
				this->contents[rSelected] = temp;
			}
			for (int i = 0; i < inDim * inDim - 1; i++) {
				for (int j = i + 1; j < inDim * inDim; j++) {
					if (contents[i] == 0 || contents[j] == 0)
						continue;
					if (contents[i] > contents[j])
						cReversals++;
				}
			}

			if (inDim % 2 == 1 && cReversals % 2 == 0) {
				break;
			}
			else if (inDim % 2 == 0) {
				// N is odd.
				int R = 0;
				while (contents[R] != 0) {
					R++;
				}
				R = R / inDim;
				if ((R + cReversals) % 2 == 0) {
					break;
				}
			}
		}
	}
	~RdmSeqList() {
		delete[] this->contents;
	}
};

int main() {
	srand((unsigned int)time(NULL));
	// State.dims are restricted to an odd number.
	
	cout << "Sequentially input d for grids of dimension in 3, 4, 5 ... d, and n for calculating"
		<< " n times for each d to gain an average time spending, 3 <= d <= 10, 1 <= n <= 20:" << endl;
	int d = 0, nTimes = 0;
	cin >> d >> nTimes;
	cout << "Display every searching progress? 0 - No, 1 - Yes." << endl;
	bool displayProgress;
	cin >> displayProgress;
	assert(d >= 3 && d <= 10 && nTimes >= 1 && nTimes <= 20 && "d, n are restricted.");

	// time span collections.
	typedef double * oneDimSpans;
	double ** times = new oneDimSpans[d - 3 + 1];
	for (int i = 0; i < d - 3 + 1; i++) {
		times[i] = new double[nTimes + 1];
	}

	for (int currDim = 3; currDim <= d; currDim++) {
		cout << "----------------------------------------------->>> Computing " << nTimes << " rounds for " << currDim
			<< " * " << currDim << " grid:\n\n";
		for (int i = 0; i < nTimes; i++) {
			cout << "////////// round " << i + 1 << ": ";

			// randomly generating a grid.
			RdmSeqList startRSL(currDim);
			RdmSeqList endRSL(currDim);

			State * startST = new State(currDim);
			State * endST = new State(currDim);

			for (int j = 0; j < currDim * currDim; j++) {
				startST->details[j] = startRSL.contents[j];
				startST->indexes[startRSL.contents[j]] = j;
				endST->details[j] = endRSL.contents[j];
				endST->indexes[endRSL.contents[j]] = j;
			}
			startST->SetHeuristicValue(endST);
			cout << "The starting State and the object state:\n\n";
			startST->Print();
			cout << endl;
			endST->Print();
			cout << endl;

			// breadth first search with heuristic function.

			priority_queue<State *, vector<State *>, cmp> pq;
			vector<State *> vec;

			pq.push(startST);
			vec.push_back(startST);

			State * pCurrState = pq.top();
			pq.pop();

			if (displayProgress) {
				cout << "Searching process:\n";
				pCurrState->Print();
				cout << endl;
			}

			// clock set.
			clock_t start, finish;
			start = clock();

			while (pCurrState->heuristicValue > 0) {

				// decide whether (* pCurrState) is a blank-at-border one and push elements
				// into the pq.
				int zeroIndex = pCurrState->indexes[0];
				int nextDetails[4] = { pCurrState->details[zeroIndex - currDim], pCurrState->details[zeroIndex + 1],
					pCurrState->details[zeroIndex + currDim], pCurrState->details[zeroIndex - 1] };
				// searching order is the details to the top, right, bottom, left of the detail zero.

				// specify detail zero's index for every nextDetail, if can't be swaped with one nextDetail, make it -1.
				if (zeroIndex >= 0 && zeroIndex <= currDim - 1)
					nextDetails[0] = -1;
				if ((zeroIndex + 1) % currDim == 0)
					nextDetails[1] = -1;
				if (zeroIndex >= currDim * (currDim - 1) && zeroIndex < currDim * currDim)
					nextDetails[2] = -1;
				if (zeroIndex % currDim == 0)
					nextDetails[3] = -1;

				for (int j = 0; j < 4; j++) {
					if (nextDetails[j] != -1) {
						State * movedNewState = pCurrState->MovedNewState(endST, nextDetails[j]);
						// does this movedNewState exist in pq?
						// change a way to solve this: another list to save all searched State.
						bool inVec = false;
						for (int k = 0; k < vec.size(); k++) {
							if ( (*movedNewState) == (*vec[k]) ) {
								inVec = true;
								break;
							}
						}
						if (inVec) {
							delete movedNewState;
						}
						else {
							pq.push(movedNewState);
							vec.push_back(movedNewState);
						}
					}
				}

				pCurrState = pq.top();
				pq.pop();
				if (displayProgress) {
					pCurrState->Print();
					cout << endl;
				}

			}

			// clear vector.
			for (int j = 0; j < vec.size(); j++) {
				delete vec[j];
			}

			delete endST;

			// clock set.
			finish = clock();
			double secDuration = double(finish - start) / CLOCKS_PER_SEC;
			times[currDim - 3][i] = secDuration;
			cout << "////////// round " << i + 1 << " time span: " << fixed << setprecision(3)
				<< secDuration << " seconds.\n\n";
		}
		times[currDim - 3][nTimes] = 0.0;
		for (int i = 0; i < nTimes; i++) {
			times[currDim - 3][nTimes] += times[currDim - 3][i];
		}
		times[currDim - 3][nTimes] = times[currDim - 3][nTimes] / nTimes;
		cout << "----------------------------------------------->>> average time span of " << currDim
			<< " * " << currDim << " grid: " << fixed << setprecision(3)
			<< times[currDim - 3][nTimes] << " seconds.\n\n";
	}

	cout << "Time spans collection:\n";
	for (int i = 3; i <= d; i++) {
		cout << "grid " << i << " * " << i << ":";
		for (int j = 0; j < nTimes; j++) {
			cout << " " << fixed << setprecision(3) << times[i - 3][j];
		}
		cout << " seconds.\n";
		cout << "average: " << fixed << setprecision(3) << times[i - 3][nTimes] << " seconds."
			<< endl << endl;
	}

	system("pause");
	return 0;
}