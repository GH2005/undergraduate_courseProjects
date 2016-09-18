// undirected graph.
#include <iostream>
#include <assert.h>
using namespace std;

typedef int* AnMartrixRow;

// ---------------------------  a LinkQueue definition. --------------------------

class QueueNode
{
private:
	int data;
	QueueNode* next;
	friend class LinkQueue;
public:
	QueueNode(int inData, QueueNode* inNext)
		: data(inData), next(inNext) {}
};

class LinkQueue
{
private:
	QueueNode* front;
	QueueNode* rear;
public:
	LinkQueue()
	{
		this->front = new QueueNode(-1, NULL);
		this->rear = front;
	}
	~LinkQueue()
	{
		do
		{
			this->rear = this->front->next;
			delete this->front;
			this->front = this->rear;
		}
		while (this->rear != NULL);
	}
	void PrintQueue()
	{
		for (QueueNode* currPt = this->front->next; currPt != NULL; currPt = currPt->next)
		{
			cout << currPt->data << ' ';
		}
	}
	void EnterQueue(int inData)
	{
		QueueNode* theNew = new QueueNode(inData, NULL);
		this->rear->next = theNew;
		this->rear = theNew;
	}
	void DeQueue()
	{
		assert(this->front != this->rear);
		QueueNode* backUp = this->front->next;
		if (this->front->next == this->rear)
		{
			this->rear = this->front;
		}
		this->front->next = backUp->next;
		delete backUp;
	}
	int GetHeadInt()
	{
		assert(this->front != this->rear);
		int haha = this->front->next->data;
		return haha;
	}
	bool IsEmpty()
	{
		if (this->rear == this->front)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

// --------------------------------------------------------------------------------

class UdgAdjMartrix
{
private:
	AnMartrixRow* martrix;
	char* cttVertexes;
	int cVertexes;
	void _DfsTraverse(char (UdgAdjMartrix::*Visit)(int vertexIndex), int currVertex, bool traversed[])
	{
		(this->*Visit)(currVertex);
		traversed[currVertex] = true;
		for (int i = 0; i < this->cVertexes; i ++)
		{
			if (this->martrix[currVertex][i] == 1 && traversed[i] == false)
			{
				_DfsTraverse(Visit, i, traversed);
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
	void DfsTraverse(char (UdgAdjMartrix::*Visit)(int vertexIndex), int whoIsBase)
	{
		cout << "DfsTraverse from v" << whoIsBase <<":";
		assert(whoIsBase < this->cVertexes && whoIsBase >= 0);
		bool* traversed = new bool[this->cVertexes];
		for (int i = 0; i < this->cVertexes; i ++)
		{
			traversed[i] = false;
		}
		this->_DfsTraverse(Visit, whoIsBase, traversed);
		delete[] traversed;
		cout << ".\n";
	}
	void BfsTraverse(char (UdgAdjMartrix::*Visit)(int vertexIndex), int whoIsBase)
	{
		cout << "BfsTraverse from v" << whoIsBase << ":";
		assert(whoIsBase < this->cVertexes && whoIsBase >= 0);
		bool* traversed = new bool[this->cVertexes];
		for (int i = 0; i < this->cVertexes; i ++)
		{
			traversed[i] = false;
		}
		LinkQueue lq;
		(this->*Visit)(whoIsBase);
		lq.EnterQueue(whoIsBase);
		traversed[whoIsBase] = true;
		int currTierIndx = 0;
		int lastTierSqr = 1;
		int newTierSqr = 0;
		int cDeQueue = 0;
		while (!lq.IsEmpty())
		{ // tiers additionally implemented.
			whoIsBase = lq.GetHeadInt();
			lq.DeQueue();
			cDeQueue ++;
			if (cDeQueue >= lastTierSqr)
			{
				cout << " <--" << currTierIndx << "--|";
				currTierIndx ++;				
				lastTierSqr = newTierSqr;
				newTierSqr = 0;
				cDeQueue = 0;
			}
			for (int j = 0; j < cVertexes; j ++)
			{
				if (!traversed[j] && this->martrix[whoIsBase][j] == 1)
				{
					(this->*Visit)(j);
					lq.EnterQueue(j);
					traversed[j] = true;
					newTierSqr ++;
				}
			}
		}
		delete[] traversed;
		cout << ".\n";
		cout << "final tier index == " << currTierIndx - 1 << '.' << endl;
	}
	char SeeOut(int vertexIndex)
	{
		cout << ' ' << cttVertexes[vertexIndex];
		return cttVertexes[vertexIndex];
	}
};

int main()
{
	{
		char inRel[10][4] = {"0-1", "1-2", "2-3", "0-3", "3-4", "4-5", "4-6", "6-7", "6-8", "7-8"};
		UdgAdjMartrix udgM(9, "ABCDEFGHI", 10, inRel);
		udgM.DfsTraverse(&UdgAdjMartrix::SeeOut, 3);
		udgM.DfsTraverse(&UdgAdjMartrix::SeeOut, 0);
		udgM.DfsTraverse(&UdgAdjMartrix::SeeOut, 7);
		cout << endl;
		udgM.BfsTraverse(&UdgAdjMartrix::SeeOut, 3);
		udgM.BfsTraverse(&UdgAdjMartrix::SeeOut, 0);
		udgM.BfsTraverse(&UdgAdjMartrix::SeeOut, 7);
	}
	system("pause");
	return 0;
}