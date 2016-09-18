// experiment task 2.2.
#include <iostream>
using namespace std;

void FiboNoRecur(int len)
{
	int i = 1;
	int j = 0;
	cout << "FiboNoRecur: ";
	for (int m = 0; m < len; m ++)
	{		
		int it = i + j;
		i = j;
		j = it;
		cout << j << ' ';
	}
	cout << endl;
}

void FiboRecur(int i, int j, int leftCount)
{
	if (leftCount == 0)	return;
	else
	{
		cout << i + j << ' ';
		FiboRecur(j, i + j, leftCount - 1);
	}
}

int main()
{
	FiboNoRecur(1);
	FiboNoRecur(2);
	FiboNoRecur(10);
	cout << "FiboRecur:   ";
	FiboRecur(1, 0, 1);
	cout << endl;
	cout << "FiboRecur:   ";
	FiboRecur(1, 0, 2);
	cout << endl;
	cout << "FiboRecur:   ";
	FiboRecur(1, 0, 10);
	cout << endl;
	system("pause");
	return 0;
}