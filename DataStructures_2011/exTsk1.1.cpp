// experiment task 1.1.
#include <iostream>
using namespace std;

typedef struct nodee 
{
	nodee* next;	// meaningful next.
	int value;
} LlistNode;

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

// function: traverse right k steps.
void TraverseRight(LlistNode* &pr, LlistNode* &p, int stepCount, LlistNode* empBasePt)
{
	if (pr == empBasePt)
		cout << "pr points to NULL";
	else
		cout << "pr points to " << pr->value;
	cout << " and p points to ";
	if (p == NULL)
		cout << "NULL" << endl;
	else
		cout << p->value << endl;
	for (int i = 0; i < stepCount; i ++)
	{
		if (p == NULL)
			break;
		LlistNode* backup = pr;
		pr = p;
		p = p->next;
		pr->next = backup;
	}
	cout << "TraverseRight " << stepCount << " steps complete. Post condition:" << endl;
	if (pr == empBasePt)
		cout << "pr points to NULL";
	else
		cout << "pr points to " << pr->value;
	cout << " and p points to ";
	if (p == NULL)
		cout << "NULL" << endl;
	else
		cout << p->value << endl;
	cout << endl;
}

// function: traverse left k steps.
void TraverseLeft(LlistNode* &pr, LlistNode* &p, int stepCount, LlistNode* empBasePt)
{
	if (pr == empBasePt)
		cout << "pr points to NULL";
	else
		cout << "pr points to " << pr->value;
	cout << " and p points to ";
	if (p == NULL)
		cout << "NULL" << endl;
	else
		cout << p->value << endl;
	for (int i = 0; i < stepCount; i ++)
	{
		if (pr == empBasePt)
			break;
		LlistNode* backup = p;
		p = pr;
		pr = pr->next;
		p->next = backup;
	}
	cout << "TraverseLeft " << stepCount << " steps complete. Post condition:" << endl;
	if (pr == empBasePt)
		cout << "pr points to NULL";
	else
		cout << "pr points to " << pr->value;
	cout << " and p points to ";
	if (p == NULL)
		cout << "NULL" << endl;
	else
		cout << p->value << endl;
	cout << endl;
}

int main()
{// it is demanded that I must traverse right from the beginning at first.
	LlistNode* empBasePt1 = InitList();
	Insert(4, 0, empBasePt1);
	Insert(10, 0, empBasePt1);
	Insert(2, 2, empBasePt1);
	Insert(12, 3, empBasePt1);
	Insert(14, 3, empBasePt1);
	Insert(4, 5, empBasePt1);
	Insert(9, 4, empBasePt1);
	// to get any position p and pr, we must traverse there.
	LlistNode* someP = empBasePt1->next;
	LlistNode* somePr = empBasePt1;
	TraverseRight(somePr, someP, 1, empBasePt1);
	TraverseRight(somePr, someP, 2, empBasePt1);
	TraverseRight(somePr, someP, 3, empBasePt1);
	TraverseRight(somePr, someP, 3, empBasePt1);
	TraverseRight(somePr, someP, 3, empBasePt1);
	TraverseLeft(somePr, someP, 1, empBasePt1);
	TraverseLeft(somePr, someP, 2, empBasePt1);
	TraverseLeft(somePr, someP, 3, empBasePt1);
	TraverseLeft(somePr, someP, 3, empBasePt1);
	TraverseLeft(somePr, someP, 3, empBasePt1);
	system("pause");
	return 0;
}