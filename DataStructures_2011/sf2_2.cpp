// linked list.
#include <iostream>
using namespace std;

struct LlistNode 
{
	LlistNode* next;
	int value;
};

LlistNode* InitList() 
{
	LlistNode* empBasePt = (LlistNode*)malloc(sizeof(LlistNode));
	empBasePt->value = -1;
	empBasePt->next = NULL;
	cout << "Initialized." << endl << endl;
	return empBasePt;
}

int GetLen(LlistNode* empBasePt) 
{
	int currLen = 0;
	LlistNode* currPt = empBasePt;
	while (currPt->next != NULL) 
	{
		currPt = currPt->next;
		currLen ++;
	}
	return currLen;
}

LlistNode* GetNodeByPos(int pos, LlistNode* empBasePt) 
{
	// assume that var-pos is a good one.
	LlistNode* aimPt = empBasePt;
	int currPos = -1;
	while (currPos < pos) 
	{
		currPos ++;
		aimPt = aimPt->next;
	}
	cout << "Value " << aimPt->value << " found in pos " << pos << '.' << endl;
	return aimPt;
}

void PrintLlist(LlistNode* empBasePt)
{
	cout << "The Llist now, " << "Len == " << GetLen(empBasePt) << endl << "Details: ";
	for (LlistNode* currPt = empBasePt->next; currPt != NULL; currPt = currPt->next)
	{
		cout << currPt->value << ' ';
	}
	cout << endl << endl;
}

void Insert(int val, int pos, LlistNode* empBasePt) 
{
	cout << "Inserting value " << val << " to pos " << pos << ':' << endl;
	if (pos < 0 || pos > GetLen(empBasePt)) 
	{
		cout << "Invalid pos." << endl;
		system("pause");
		exit(1);
	}
	else 
	{
		LlistNode* pt_prevNode = GetNodeByPos(pos - 1, empBasePt);
		LlistNode* pt_newNode = (LlistNode*)malloc(sizeof(LlistNode));
		pt_newNode->value = val;
		pt_newNode->next = pt_prevNode->next;
		pt_prevNode->next = pt_newNode;
		cout << "Insertion complete.";
		PrintLlist(empBasePt);
	}
}

LlistNode* FindPrev(int val, LlistNode* empBasePt)
{
	LlistNode* pt_theFound = empBasePt;
	while (pt_theFound-> != NULL && pt_theFound->next->value != val)
	{
		pt_theFound = pt_theFound->next;
	}
	return pt_theFound;
}

void DeleteByValue(int val, LlistNode* empBasePt)
{
	cout << "Deleting node, value == " << val << " :" << endl;
	LlistNode* pt_foundPrev = FindPrev(val, empBasePt);
	LlistNode* backUp = pt_foundPrev->next->next;
	free(pt_foundPrev->next);
	pt_foundPrev->next = backUp;
	cout << "Deletetion complete.";
	PrintLlist(empBasePt);
}

int main() 
{
	LlistNode* empBasePt1 = InitList();
	Insert(4, 0, empBasePt1);
	Insert(10, 0, empBasePt1);
	Insert(2, 2, empBasePt1);
	Insert(12, 3, empBasePt1);
	Insert(14, 3, empBasePt1);
	DeleteByValue(10, empBasePt1);
	DeleteByValue(12, empBasePt1);
	DeleteByValue(2, empBasePt1);
	Insert(19, 2, empBasePt1);
	system("pause");
	return 0;
}