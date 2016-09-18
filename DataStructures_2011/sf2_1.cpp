#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct
{
	int size;
	int len;
	int *basePt;
} SqList;

void InitList(SqList &list)
{
	cout << "To initialize the list, input size, then len:" << endl;
	int size = 0;
	int len = 0;
	cin >> size >> len;
	list.size = size;
	list.len = len;
	list.basePt = (int *)malloc(size * sizeof(int));
	if (list.basePt == NULL)
	{
		cout << "MemAlloc Fails." << endl;
		exit(1);
	}
	cout << "Input " << len << " integers:" << endl;
	for (int i = 0; i < len; i ++)
	{
		cin >> list.basePt[i];
	}
}

void PrintList(SqList &list)
{
	cout << "size == " << list.size << "; len == " << list.len << "; Elements:" << endl;
	for (int i = 0; i < list.len; i ++)
	{
		cout << list.basePt[i] << ' ';
	}
	cout << endl;
}

void Insert(SqList &list)
{
	cout << "To Insert an integer, input the postion, then the value:" << endl;
	int pos = 0;
	int value = 0;
	cin >> pos >> value;
	if (pos < 0 || pos > list.len)
	{
		cout << "Bad postion." << endl;
		exit(1);
	}
	else if (list.len == list.size)
	{
		cout << "list full." << endl;
		exit(1);
	}
	else
	{
		for (int i = list.len; i > pos; i --)
		{
			list.basePt[i] = list.basePt[i - 1];
		}
		list.basePt[pos] = value;
		list.len ++;
		cout << "Insert complete.";
		PrintList(list);
	}
}

int Find(SqList &list)
{
	cout << "To find by value, input 0; index, 1" << endl;
	bool findByIndex = 0;
	cin >> findByIndex;
	if (findByIndex)
	{
		cout << "Input the index:" << endl;
		int index = 0;
		cin >> index;
		cout << "Value " << list.basePt[index] << " found in pos " << index << endl;
		return index;
	}
	else
	{
		cout << "Input the value:" << endl;
		int targ = 0;
		cin >> targ;
		int foundPos = 0;
		while (foundPos <= list.len - 1 && targ != list.basePt[foundPos])
		{
			foundPos ++;
		}
		// last is right, foundPos == list.len - 1; wrong, foundPos == list.len.
		if (foundPos == list.len)
		{
			cout << "Value " << targ << " not found." << endl;
			exit(1);
		}
		else
		{
			cout << "Value " << targ << " found in pos " << foundPos << endl;
			return foundPos;
		}
	}
}

void Remove(SqList &list)
{
	cout << "Now you are removing an element. The program will go to Find() function first now." << endl;
	int pos = Find(list);
	for (int i = pos; i <= list.len - 2; i ++)
	{
		list.basePt[i] = list.basePt[i + 1];
	}
	list.len --;
	cout << "Remove complete.";
	PrintList(list);
}

int main()
{
	cout << "I'm not responsible for some program crashes caused by bad inputs." << endl;
	SqList testList;
	InitList(testList);
	PrintList(testList);
	Insert(testList);
	Find(testList);
	Remove(testList);
	system("pause");
	return 0;
}