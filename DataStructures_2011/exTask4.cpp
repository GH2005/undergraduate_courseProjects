// experiment task 4.
#include <iostream>
#include <assert.h>
#include <sstream>
using namespace std;

typedef int* AnMartrixRow;

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
// -------------------------------------  BinaryTree --------------------------------------------------------------------------------------

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
	BinaryTree(TreeNode* inRoot)
	{
		this->root = inRoot;
		cout << "a BinaryTree constructed by a root TreeNode. \n\n";
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

// -----------------------------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------  graph --------------------------------------------------------------------------------------------

class UdgAdjMartrix
{
private:
	AnMartrixRow* martrix;
	char* cttVertexes;
	int cVertexes;
	void _DfsTraverseForBt(char (UdgAdjMartrix::*Visit)(int vertexIndex), int currVertex, bool traversed[], TreeNode* pPrior)
	{
		(this->*Visit)(currVertex);
		traversed[currVertex] = true;
		TreeNode* pLeft = pPrior;
		for (int i = 0; i < this->cVertexes; i ++)
		{
			if (this->martrix[currVertex][i] == 1 && traversed[i] == false)
			{
				if (pLeft == pPrior)
				{
					pLeft = new TreeNode(this->cttVertexes[i]);
					pPrior->lchild = pLeft;
				}
				else
				{
					pLeft->rchild = new TreeNode(this->cttVertexes[i]);
					pLeft = pLeft->rchild;
				}
				_DfsTraverseForBt(Visit, i, traversed, pLeft);
			}
		}
	}
public:
	UdgAdjMartrix(int inCVertexes, char inCttVertexes[], int inCRelations, char inRelations[][4])
		: cVertexes(inCVertexes)
	{
		assert(inCVertexes > 0 && inCttVertexes);
		this->martrix = new AnMartrixRow[inCVertexes];
		for (int j = 0; j < inCVertexes; j ++)
		{
			this->martrix[j] = new int[inCVertexes];
			for (int jj = 0; jj < inCVertexes; jj ++)
			{
				this->martrix[j][jj] = 0;
			}
		}
		this->cttVertexes = inCttVertexes;
		for (int i = 0; i < inCRelations; i ++)
		{// "horiVer-vertVer".
			int horiVer = inRelations[i][0] - 48;
			int vertVer = inRelations[i][2] - 48;
			this->martrix[horiVer][vertVer] = 1;
			this->martrix[vertVer][horiVer] = 1;
		}
		cout << "constructed." << endl;
	}
	~UdgAdjMartrix()
	{
		// ..................
		for (int i = 0; i < this->cVertexes; i ++)
		{
			delete[] this->martrix[i];
		}
		delete[] this->martrix;
	}	
	BinaryTree* DfsTraverseForBt(char (UdgAdjMartrix::*Visit)(int vertexIndex), int whoIsBase)
	{
		cout << "DfsTraverse from v" << whoIsBase <<" and construct a children left, brothers right binary tree:";
		assert(whoIsBase < this->cVertexes && whoIsBase >= 0);
		bool* traversed = new bool[this->cVertexes];
		for (int i = 0; i < this->cVertexes; i ++)
		{
			traversed[i] = false;
		}
		TreeNode* root = new TreeNode(this->cttVertexes[whoIsBase]);
		this->_DfsTraverseForBt(Visit, whoIsBase, traversed, root);
		delete[] traversed;
		cout << ".\n\n";
		BinaryTree* forReturn = new BinaryTree(root);
		return forReturn;
	}
	char SeeOut(int vertexIndex)
	{
		cout << ' ' << cttVertexes[vertexIndex];
		return cttVertexes[vertexIndex];
	}
};

// ------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	{
		char inRel[10][4] = {"0-1", "1-2", "2-3", "0-3", "3-4", "4-5", "4-6", "6-7", "6-8", "7-8"};
		UdgAdjMartrix udgM(9, "ABCDEFGHI", 10, inRel);
		BinaryTree* btGenerated = udgM.DfsTraverseForBt(&UdgAdjMartrix::SeeOut, 3);
		btGenerated->PreOrderPrint();
	}
	system("pause");
	return 0;
}