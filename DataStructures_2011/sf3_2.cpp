// 输出很多，自行调整 cmd 窗口的缓冲区大小。
// Sequenced(Round) Queue and Link Queue.
#include <iostream>
#include <assert.h>
#include <sstream>
#include <iomanip>
using namespace std;

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
		this->front = new QueueNode('_', NULL);
		this->rear = front;
		cout << "A Link Queue established." << endl << endl;
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
		cout << "Printing the Queue:" << endl;
		for (QueueNode* currPt = this->front->next; currPt != NULL; currPt = currPt->next)
		{
			cout << currPt->data << ' ';
		}
		cout << endl;
	}
	void EnterQueue(int inData)
	{
		cout << "Data " << inData << " entering the Queue:" << endl;
		QueueNode* theNew = new QueueNode(inData, NULL);
		this->rear->next = theNew;
		this->rear = theNew;
		cout << "Finished.";
		this->PrintQueue();
		cout << endl;
	}
	void DeQueue()
	{
		cout << "DeQueuing:" << endl;
		assert(this->front != this->rear);
		QueueNode* backUp = this->front->next;
		this->front->next = backUp->next;
		delete backUp;
		cout << "Finished.";
		this->PrintQueue();
		cout << endl;
	}
	int GetHeadInt()
	{
		assert(this->front != this->rear);
		int haha = this->front->next->data;
		cout << "The head int is " << haha << ".\n\n";
		return haha;
	}
};

// -----------------------------------------------------------------------------------

class RoundQueue
{
private:
	int* arrayName;
	int space;
	int len;
	int front;
	int rear;
public:
	RoundQueue(int inSpc)
		: arrayName(new int[inSpc]), space(inSpc), len(0), front(0), rear(0) 
	{
		cout << "A RoundQueue established." << endl << endl;
	}
	~RoundQueue()
	{
		delete[] arrayName;
	}
	void EnterQueue(int inData)
	{
		cout << inData << " entering the queue:" << endl;
		assert(len < space);
		arrayName[rear] = inData;
		rear = (rear + 1) % space;
		len ++;
		cout << "Finished.";
		this->PrintQueue();
		cout << endl;
	}
	void PrintQueue()
	{
		cout << "Printing the Queue:" << endl;
		for (int i = 0; i < len; i ++)
		{
			int realIndx = (front + i) % this->space;
			cout << arrayName[realIndx] << ' ';
		}
		cout << endl;
	}
	int DeQueue()
	{
		cout << "Dequeuing:" << endl;
		assert(len > 0);
		int that = this->arrayName[front];
		front = (front + 1) % this->space;
		len --;
		cout << "Finished.";
		this->PrintQueue();
		cout << endl;
		return that;
	}
	int GetHeadInt()
	{
		assert(len > 0);
		int haha = this->arrayName[this->front];
		cout << "The head int is " << haha << ".\n\n";
		return haha;
	}
};

// ------------------------------------------------------------------------

class YanghuiTri
{
public:
	static void Print(int lineCount)
	{
		cout << "||--------------------------------------------Preparing for outputting a YanghuiTri:" << endl;
		assert(lineCount > 0);
		RoundQueue rq(lineCount + 1);
		stringstream ss;
		rq.EnterQueue(1);
		for (int i = 0; i < lineCount - 1; i ++)
		{
			ss << setiosflags(ios::left) << setw(5) << ' ';
		}
		ss << 1 << endl;
		for (int i = 1; i < lineCount; i ++)
		{
			for (int j = 0; j < lineCount - 1 - i; j ++)
			{
				ss << setiosflags(ios::left) << setw(5) << ' ';
			}
			for (int j = 0; j < i + 1; j ++)
			{
				if (j == 0)
				{
					rq.EnterQueue(1);
					ss << setiosflags(ios::left) << setw(5) << 1 << setiosflags(ios::left) << setw(5) << ' ';
				}
				else if  (j == i)
				{
					rq.EnterQueue(1);
					ss << setiosflags(ios::left) << setw(5) << 1 << setiosflags(ios::left) << setw(5) << ' ';
					rq.DeQueue();
				}
				else
				{
					int that = rq.DeQueue();
					that += rq.GetHeadInt();
					rq.EnterQueue(that);
					ss << setiosflags(ios::left) << setw(5) << that << setiosflags(ios::left) << setw(5) << ' ';
				}				
			}
			ss << endl;		
		}
		cout << "||-----------------------------Printing a YanghuiTri of " << lineCount << " lines:" << endl;
		cout << ss.str();
	}
};


int main()
{
	LinkQueue lq;
	lq.PrintQueue();
	lq.EnterQueue('u');
	lq.EnterQueue('W');
	lq.GetHeadInt();
	lq.EnterQueue('t');
	lq.EnterQueue('L');
	lq.DeQueue();
	lq.DeQueue();
	lq.GetHeadInt();

	// --------------------------

	RoundQueue rq(6);
	rq.EnterQueue(2);
	rq.EnterQueue(4);
	rq.DeQueue();
	rq.GetHeadInt();
	rq.EnterQueue(3);
	rq.EnterQueue(5);
	rq.GetHeadInt();
	rq.DeQueue();
	rq.GetHeadInt();

	YanghuiTri::Print(1);
	YanghuiTri::Print(2);
	YanghuiTri::Print(9);

	system("pause");
	return 0;
}