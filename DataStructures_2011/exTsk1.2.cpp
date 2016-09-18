// experiment task 1.2.
#include <iostream>
#include <iomanip>
using namespace std;

struct LlistNode 
{
	LlistNode* next;
	long long coefficient;
	long long exponent;
};

LlistNode* InitList() 
{
	LlistNode* empBasePt = (LlistNode*)malloc(sizeof(LlistNode));
	empBasePt->exponent = -1;
	empBasePt->coefficient = -1;
	empBasePt->next = empBasePt;	// a round linked list.
	cout << "A new round linked list Initialized." << endl << endl;
	return empBasePt;
}

long long GetLen(LlistNode* empBasePt) 
{
	long long currLen = 0;
	LlistNode* currPt = empBasePt;
	while (currPt->next != empBasePt) 
	{
		currPt = currPt->next;
		currLen ++;
	}
	return currLen;
}

void PrlongLlist(LlistNode* empBasePt)
{
	cout << "The Llist now, " << "Len == " << GetLen(empBasePt) << " Details:\n";
	for (LlistNode* currPt = empBasePt->next; currPt != empBasePt; currPt = currPt->next)
	{
		cout << "coef == " << setiosflags(ios::left) << setw(5) << currPt->coefficient << "  expo == " << currPt->exponent << endl;
	}
}

void Insert(long long coe, long long exp, LlistNode* empBasePt) 
{
	cout << "Inserting node to the head, coefficient == " << coe << " and exponent == " << exp << ':' << endl;
	LlistNode* newOne = (LlistNode*)malloc(sizeof(LlistNode));
	newOne->coefficient = coe;
	newOne->exponent = exp;
	newOne->next = empBasePt->next;	// insert as head.
	empBasePt->next = newOne;			// insert as head.
	cout << "Insertion complete.";
	PrlongLlist(empBasePt);
	cout << endl;
}

// required function: calculate the value, x given.
long long Calc(long long x, LlistNode* empBasePt)
{
	long long result = 0;
	for (LlistNode* currPt = empBasePt->next; currPt != empBasePt; currPt = currPt->next)
	{
		result += currPt->coefficient * pow(double(x), currPt->exponent);
	}
	PrlongLlist(empBasePt);
	cout << "--------------------->> Value at x == " << x << " is " << result << endl << endl;
	return result;
}

LlistNode* FindPrevNodeByExp(LlistNode* baseNodePt, LlistNode* empBasePt)	// find the previous node of the node with exp.
{
	LlistNode* pt_theFound = baseNodePt;
	while (pt_theFound->next != empBasePt && pt_theFound->next->exponent != baseNodePt->exponent)
	{
		pt_theFound = pt_theFound->next;
	}
	return pt_theFound;		// if not found, return empBasePt's previous node.
							// remember to code an if...else.
}

void Delete(LlistNode* thePrevPt, LlistNode* empBasePt)		// use FindPrevNodeByExp() to locate and delete the node.
{
	cout << "Deleting node, coef == " << thePrevPt->next->coefficient << ", emp == " << thePrevPt->next->exponent << endl;
	LlistNode* backUp = thePrevPt->next->next;
	free(thePrevPt->next);
	thePrevPt->next = backUp;
	cout << "Deletetion complete.";
	PrlongLlist(empBasePt);
	cout << endl;
}

// required function: Calculate the product of two polynomials.
LlistNode* GetProduct(LlistNode* factorEmp1, LlistNode* factorEmp2)
{
	cout << "--------------------->> GetProduct of two polynomials: " << endl << endl;
	PrlongLlist(factorEmp1);
	PrlongLlist(factorEmp2);
	cout << endl;
	LlistNode* trgtEmpBasePt = InitList();
	// add node to the new linked list.
	for (LlistNode* currPt1 = factorEmp1->next; currPt1 != factorEmp1; currPt1 = currPt1->next)
	{
		for (LlistNode* currPt2 = factorEmp2->next; currPt2 != factorEmp2; currPt2 = currPt2->next)
		{
			Insert(currPt1->coefficient * currPt2->coefficient, currPt1->exponent + currPt2->exponent, trgtEmpBasePt);
		}
	}
	// merge nodes that have the same exponent.
	cout << "Merge nodes that have the same exponent." << endl << endl;
	for (LlistNode* currPt = trgtEmpBasePt->next; currPt != trgtEmpBasePt; currPt = currPt->next)
	{// there may be 3 or more nodes that have the same exponent.
		LlistNode* aPrev = FindPrevNodeByExp(currPt, trgtEmpBasePt);	// to delete, find its previous node.
		while (aPrev->next != trgtEmpBasePt)
		{
			currPt->coefficient += aPrev->next->coefficient;
			cout << "Delete node and get the sum of two coefficients." << endl;
			Delete(aPrev, trgtEmpBasePt);
			aPrev = FindPrevNodeByExp(currPt, trgtEmpBasePt);
		}
	}
	cout << "Proceeded. Final result:" << endl;
	PrlongLlist(trgtEmpBasePt);
	cout << endl;
	return trgtEmpBasePt;
}

int main()
{
	LlistNode* empBasePt1 = InitList();
	Insert(9, 9, empBasePt1);
	Insert(8, 6, empBasePt1);
	Calc(29, empBasePt1);

	LlistNode* empBasePt2 = InitList();
	Insert(4, 7, empBasePt2);
	Insert(3, 5, empBasePt2);
	Insert(5, 4, empBasePt2);
	Insert(1, 2, empBasePt2);
	Calc(29, empBasePt2);

	GetProduct(empBasePt1, empBasePt2);

	system("pause");
	return 0;
}