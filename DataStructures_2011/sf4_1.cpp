// string.
#include <iostream>
#include <assert.h>
using namespace std;

class SqString
{
private:
	char* arrayName;
	int len;
	int space;
	bool MicroMatch(int sourceBase, SqString targ)
	{
		bool matched = true;
		for (int i = 0; i < targ.len; i ++)
		{
			if (this->arrayName[i + sourceBase] != targ.arrayName[i])
			{
				matched = false;
				break;
			}
		}
		return matched;
	}
	int* next;
public:
	SqString(int spc, int ln, char as[])
	{
		assert(spc >= ln);
		// assert(as[].length == ln), temporary like this.
		this->space = spc;
		this->len = ln;
		this->arrayName = as;
		cout << as << endl;
		//
		// next[].
		//
		this->next = new int[ln];
		this->next[0] = 0;
	}
	int MatchExhaustivity(SqString targ)
	{
		assert(targ.len <= this->len);
		int i = 0;
		bool succ = false;
		for (i = 0; i < this->len - targ.len + 1; i ++)
		{
			if (this->MicroMatch(i, targ))
			{
				succ = true;
				break;
			}
		}
		if (succ)
		{
			cout << "ExMatched at pos " << i << "." << endl; 
			return i;
		}
		else
		{
			cout << "ExMatch fails." << endl;
			return -1;
		}
	}
};

int main()
{
	SqString sqs(10, 5, "abcde");		//"abcde", 5 chars.
	SqString targSqs(10, 3, "abc");		//"bcd", 3 char.
	sqs.MatchExhaustivity(targSqs);
	system("pause");
	return 0;
}