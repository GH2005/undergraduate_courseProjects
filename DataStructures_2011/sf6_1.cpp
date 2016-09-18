// binary tree.
#include <iostream>
#include <assert.h>
#include <sstream>
using namespace std;

// A linked stack definition ---------------------------------------------------------------------------------------------------

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
};

class BinaryTree
{
private:
	void CreateBiTree(TreeNode* &T)
	{
		char inData = '\0';
		cin.get(inData);
		if (inData != '@')
		{
			T = new TreeNode(inData);
			CreateBiTree(T->lchild);
			CreateBiTree(T->rchild);
		}
	}
	TreeNode* root;
	stringstream* ssPt;
	char SeeOut(TreeNode* tn)
	{
		*ssPt << tn->data << ' ';
		return tn->data;
	}
	void preOrderTraverse_noRecur(char (BinaryTree::*Visit)(TreeNode* tn))
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
public:
	BinaryTree()
	{
		cout << "Input PreOrder characters for constructing a binary tree, \nno blanks between characters, @ stands for null node,"<< endl;
		cout << "there must be accurate amount of @s to make sure the construction finally ends, " << endl;
		cout << "examples: SNL@M@@@TSO@@@P@@, ABC@@DE@G@@F@@@:" << endl;
		this->CreateBiTree(this->root);
		cout << "Construction succeeds." << endl;
	}
	~BinaryTree()
	{
		// to be implemented, based on PreTraverse.
	}
	void PreOrderPrint()
	{
		this->ssPt = new stringstream;
		this->preOrderTraverse_noRecur(&BinaryTree::SeeOut);
		cout << "PreOrder output: ";
		cout << ssPt->str() << endl;
		delete this->ssPt;
	}
};

int main()
{
	BinaryTree bt;
	bt.PreOrderPrint();
	system("pause");
	return 0;
}