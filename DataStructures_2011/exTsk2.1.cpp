// experiment task 2.1.
#include <iostream>
#include <assert.h>
using namespace std;

class DoubleStack
{
private:
	char* arrayName;
	int top0;
	int top1;
	int space;
public:
	DoubleStack(int inSpace)
	{
		assert(inSpace > 0);
		this->arrayName = new char[inSpace];
		this->space = inSpace;
		this->top0 = -1;
		this->top1 = inSpace;
		cout << "a doublestack of " << inSpace << " spaces constructed." << endl;
	}
	void PrintDoubleStack()
	{
		cout << "stack 0: ";
		for (int i = 0; i <= top0; i ++)
		{
			cout << this->arrayName[i] << ' ';
		}
		cout << endl << "stack 1: ";
		for (int j = space - 1; j >= top1; j --)
		{
			cout << this->arrayName[j] << ' ';
		}
		cout << endl;
	}
	bool IsEmpty(int whichStack)
	{
		assert(whichStack == 0 || whichStack == 1);
		if (whichStack == 0)
		{
			if (top0 == -1)
			{
				cout << "Stack 0 is empty." << endl;
				return true;
			}
			else
			{
				cout << "Stack 0 is not empty." << endl;
				return false;
			}
		}
		else if (whichStack == 1)
		{
			if (top1 == this->space)
			{
				cout << "Stack 1 is empty." << endl;
				return true;
			}
			else
			{
				cout << "Stack 1 is not empty." << endl;
				return false;
			}
		}
	}
	bool IsFull()
	{
		if (top0 + 1 == top1)
		{
			cout << "DoubleStack is full." << endl;
			return true;
		}
		else
		{
			cout << "DoubleStack is not full." << endl;
			return false;
		}
	}
	void Insert(int whichStack, char content)
	{
		assert(!this->IsFull());
		assert(whichStack == 0 || whichStack == 1);
		if (whichStack == 0)
		{
			this->arrayName[++top0] = content;
		}
		else
		{
			this->arrayName[--top1] = content;
		}
		this->PrintDoubleStack();
	}
	void Pop(int whichStack)
	{
		assert(whichStack == 0 || whichStack == 1);
		if (whichStack == 0)
		{
			assert(!IsEmpty(0));
			top0 --;
		}
		else
		{
			assert(!IsEmpty(1));
			top1 ++;
		}
		this->PrintDoubleStack();
	}
};

int main()
{
	DoubleStack ds(5);
	ds.IsEmpty(0);
	ds.IsEmpty(1);
	ds.Insert(0, 's');
	ds.Insert(0, 'o');
	ds.Insert(1, 'i');
	ds.Insert(1, 'p');
	ds.Insert(0, 'j');
	ds.IsFull();
	ds.Pop(1);
	ds.Pop(0);
	system("pause");
	return 0;
}