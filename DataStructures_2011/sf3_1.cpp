#include <iostream>
#include <assert.h>
using namespace std;

template<class T> struct SqStack
{
private:
	T* ctt;
	int space;
	int len;
public:
	SqStack(int spc)
	{
		this->ctt = new T[spc];
		this->space = spc;
		this->len = 0;
		cout << "A SqStack Built." << endl << endl;
	}
	~SqStack()
	{
		delete[] ctt;
		cout << "A SqStack destroyed." << endl << endl;
	}
	void PrintStack()
	{
		cout << "Printing the stack:" << endl;
		for (int i = 0; i < len; i++)
		{
			cout << this->ctt[i] << ' ';
		}
		cout << endl;
	}
	void Push(T t)
	{
		cout << "Trying to push " << t << " to the stack top:" << endl;
		assert(this->len != this->space);
		this->ctt[len] = t;
		len++;
		cout << "Pushing ends, ";
		this->PrintStack();
		cout << endl;
	}
	void Pop()
	{
		cout << "Trying to pop the top element:" << endl;
		assert(this->len != 0);
		cout << this->ctt[len - 1] << " popped.";
		this->len --;
		this->PrintStack();
		cout << endl;
	}
	T GetTop()
	{
		cout << "The top element is " << this->ctt[len - 1] << '.' <<endl << endl;
		return this->ctt[len - 1];
	}
};

template<class T> struct StackNode
{
private:
	T ctt;
	StackNode<T>* prior;
	template<class T> friend struct LinkedStack;
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

int main()
{
	SqStack<char> sqS(6);
	sqS.Push('U');
	sqS.Push('w');
	sqS.Push('R');
	sqS.Push('o');
	sqS.Pop();
	sqS.GetTop();
	sqS.Pop();
	sqS.GetTop();
	LinkedStack<char> ls;
	ls.Push('U');
	ls.Pop();
	ls.Push('w');
	ls.Pop();
	ls.Push('R');
	ls.Push('o');
	ls.GetTop();
	system("pause");
	return 0;
}