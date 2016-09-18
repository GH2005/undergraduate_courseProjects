// experiment task 3.
#include <iostream>
#include <math.h>
#include <assert.h>
#include <sstream>
using namespace std;

// A linked stack defination ---------------------------------------------------------------------------------------------------

template<class T> struct StackNode
{
public:
	T ctt;
	StackNode<T>* prior;
public:
	StackNode(T t, StackNode<T>* theTruePrior)
	{
		this->ctt = t;
		this->prior = theTruePrior;
	}
};

template<class T> struct LinkedStack
{
private:
	StackNode<T>* top;	
public:
	LinkedStack()
	{
		this->top = NULL;		
		cout << "A LinkedStack Built." << endl << endl;
	}
	~LinkedStack()
	{
		if (top != NULL)
		{
			StackNode<T>* nx = top->prior;
			StackNode<T>* curr = this->top;
			do
			{
				delete curr;
				curr = nx;
				nx = nx->prior;
			} 
			while (nx != NULL);
			delete curr;
		}
		cout << "A LinkedStack destroyed." << endl << endl;
	}
	bool IsEmpty()
	{
		if (this->top == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void PrintStack()
	{
		cout << "Printing the stack from top to bottom:" << endl;
		for (StackNode<T>* currNodePt = this->top; currNodePt != NULL; currNodePt = currNodePt->prior)
		{
			cout << currNodePt->ctt << ' ';
		}
		cout << endl;
	}
	void Push(T t)
	{
		StackNode<T>* newNode = new StackNode<T>(t, this->top);
		this->top = newNode;
		cout << "Node " << t << " has been pushed into the LinkedStack.";
		this->PrintStack();
		cout << endl;
	}
	void Pop()
	{
		cout << "Trying to pop the top element:" << endl;
		assert(this->top != NULL);
		StackNode<T>* nx = top->prior;
		cout << top->ctt << " popped." << endl << endl;
		delete top;
		top = nx;
	}
	StackNode<T>* GetTop()
	{
		cout << "The top element is " << this->top->ctt << '.' <<endl << endl;
		return top;
	}
};

// -----------------------------------------------------------------------------------------------------------------------------------------

class TreeNode
{
public:
	char data;
	TreeNode* lchild;
	TreeNode* rchild;
	TreeNode(char inData)
		: data(inData), lchild(NULL), rchild(NULL) {}
	TreeNode()
		: data('\0'), lchild(NULL), rchild(NULL) {}
};

class CompleteBinaryTree
{
private:
	TreeNode* root;
	stringstream* ssPt;
	char SeeOut(TreeNode* tn)
	{
		*ssPt << tn->data << ' ';
		return tn->data;
	}
	char RCout(TreeNode* tn)
	{
		cout << tn->data << ' ';
		return tn->data;
	}
	void preOrderTraverse_noRecur(char (CompleteBinaryTree::* Visit)(TreeNode* tn))
	{		
		LinkedStack<TreeNode*> ls;
		TreeNode* curr = this->root;
		while(1)
		{
			if (curr != NULL)
			{
				ls.Push(curr);
				(this->*Visit)(curr);
				curr = curr->lchild;
			}
			else
			{
				if (ls.IsEmpty())
					break;
				curr = ls.GetTop()->ctt;
				ls.Pop();
				curr = curr->rchild;
			}
		}
	}
	void DoubleOrderTraversal_Recursion(char (CompleteBinaryTree::* Visit)(TreeNode* tn), TreeNode* curr)
	{
		if (curr != NULL)
		{
			(this->*Visit)(curr);
			DoubleOrderTraversal_Recursion(Visit, curr->lchild);
			(this->*Visit)(curr);
			DoubleOrderTraversal_Recursion(Visit, curr->rchild);
		}
	}
public:
	CompleteBinaryTree(int num, char t[])
	{
		cout << "Trying to construct a completeBinaryTree based on " << t << "." << endl;
		assert(num > 0 && t);
		int i = 0;
		int tIndi = 0;
		int nodeCount0 = int(pow(2, i));
		TreeNode* tnArray0 = new TreeNode[nodeCount0];
		this->root = tnArray0;
		tnArray0[0].data = t[tIndi];
		tIndi ++;
		int deepestIndex = int(log(double(num)) / log(2.0));
		for (i ++; i < deepestIndex + 1; i ++)
		{
			int nodeCount = int(pow(2, i));
			if (i == deepestIndex)
			{
				int fullBtCanBe = pow(2, deepestIndex + 1) - 1;
				int deepestCanHave = pow(2, deepestIndex);
				nodeCount = deepestCanHave - (fullBtCanBe - num); 
			}
			TreeNode* tnArray = new TreeNode[nodeCount];
			int newNodeIndi = 0;
			//
			// specify the relationships.
			//
			for (int j = 0; j < nodeCount0; j ++)
			{
				if (newNodeIndi >= nodeCount) break;
				tnArray0[j].lchild = &tnArray[newNodeIndi];
				newNodeIndi ++;
				if (newNodeIndi >= nodeCount) break;
				tnArray0[j].rchild = &tnArray[newNodeIndi];
				newNodeIndi ++;
			}
			// assign values.
			for (int k = 0; k < nodeCount; k ++)
			{
				tnArray[k].data = t[tIndi];
				tIndi ++;
			}
			tnArray0 = tnArray;
			nodeCount0 = nodeCount;
		}
		cout << "succeeds." << endl << endl;
		this->PreOrderPrint();
	}
	void PreOrderPrint()
	{
		cout << "Preparing for PreOrderPrint..." << endl;
		this->ssPt = new stringstream;
		this->preOrderTraverse_noRecur(&CompleteBinaryTree::SeeOut);
		cout << "PreOrder output: ";
		cout << ssPt->str() << endl;
		delete this->ssPt;
	}
	void DoubleOrderPrint()
	{
		cout << "DoubleOrder output: ";
		this->DoubleOrderTraversal_Recursion(&CompleteBinaryTree::RCout, this->root);
		cout << endl;
	}
};

int main()
{
	CompleteBinaryTree cbt(12, "abcdefghijkl");
	cbt.DoubleOrderPrint();
	system("pause");
	return 0;
}