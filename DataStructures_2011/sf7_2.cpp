// sf7_2.cpp: directed acycline graph.
#include <iostream>
#include <assert.h>
using namespace std;

class ListNode;

typedef ListNode* PListNode;

class ListNode
{ // represents an arc.
private:
	int indxVertex;
	int weight;
	PListNode nextArc;
	friend class DirectedAcyclineGraph;
public:
	ListNode(int targetedVertex, int inWght, PListNode inNextArc = nullptr)
		: indxVertex(targetedVertex), weight(inWght), nextArc(inNextArc) {}
};

class ListHead
{
private:
	char ctt;
	PListNode firstArc;
	friend class DirectedAcyclineGraph;
public:
	ListHead()
		: ctt('@'), firstArc(nullptr) {}
};

class DirectedAcyclineGraph
{ // adjacency list implementation.
private:
	ListHead* anHeads;
	int cHeads;
	int cRelations;
	typedef char* RelationExpression;
	RelationExpression* cttRelations;
	PListNode& GetRefNextMember(int nodeIndx, ListHead& inHead)
	{	// when nodeIndx == -2, it returns the last node's nextArc member.
		// think about validation please.
		assert(nodeIndx >= -2 && "nodeIndx constraint");
		PListNode* pforReturn = &inHead.firstArc;
		if (nodeIndx == -2)
		{		
			while (*pforReturn != nullptr)
			{
				pforReturn = &((*pforReturn)->nextArc);

			}
		}
		else
		{
			while (*pforReturn != nullptr && nodeIndx > -1)
			{
				pforReturn = &((*pforReturn)->nextArc);
				nodeIndx --;
			}
		}
		if (*pforReturn != nullptr)
		{
			cout << "the one got is " << (*pforReturn)->indxVertex << '.' << endl;
		}
		else
		{
			cout << "the one got is nullptr->indxVertex." << endl;
		}
		return *pforReturn;
	}
public:
	DirectedAcyclineGraph(int inCHeads, char inCttHeads[], int inCRelations, char inCttRelations[][8])
		: cHeads(inCHeads), anHeads(new ListHead[inCHeads]), cRelations(inCRelations), cttRelations(new RelationExpression[inCRelations])
	{ // cttRelations contains strings like this: "1->3--2".
		for (int k = 0; k < inCRelations; k ++)
		{ // to store the cttRelations.
			// some problem: const literal char strings, ignored this time. 
			this->cttRelations[k] = inCttRelations[k];
		}
		for (int i = 0; i < inCHeads; i ++)
		{
			this->anHeads[i].ctt = inCttHeads[i];
		}
		for (int j = 0; j < inCRelations; j ++)
		{
			// cttRelations[j][0] - 48: tail vertex; cttRelations[j][3] - 48: head vertex; this->GetRefNextMember(-2, tail vertex)...
			PListNode& ssd = this->GetRefNextMember(-2, this->anHeads[inCttRelations[j][0] - 48]);
			ssd = new ListNode(inCttRelations[j][3] - 48, inCttRelations[j][6] - 48);
			// to cout.
			cout << "newly constructed ListNode: " << inCttRelations[j][0] - 48 << "-->" << inCttRelations[j][3] -48 << ' ' << inCttRelations[j][6] - 48 << ".\n";
		}
		cout << endl;
	}
	~DirectedAcyclineGraph()
	{
		// to be implemented, many ListHeads and ListNodes.
	}
	void TopoLogicalSortAndCriticalPath(int frIndxSeq[], int frIndxNegaSeq[], int frCriticalPath[], int& frCCriticalVertexes)
	{ // need a reversed ListHeads->ListNodes structure.
		ListHead* anRvsdHeads = new ListHead[this->cHeads];
		for (int i = 0; i < this->cHeads; i ++)
		{
			anRvsdHeads[i].ctt = this->anHeads[i].ctt;
		}
		// add revsdRelations.
		for (int j = 0; j < this->cRelations; j ++)
		{
			// cttRelations[j][0] - 48: head vertex; cttRelations[j][3] - 48: tail vertex; this->GetRefNextMember(-2, tail vertex)...
			this->GetRefNextMember(-2, anRvsdHeads[this->cttRelations[j][3] - 48]) = new ListNode(this->cttRelations[j][0] - 48, 
										this->cttRelations[j][6] - 48);
			// to cout.
			cout << "newly constructed RvsdListNode: " << this->cttRelations[j][3] - 48 << "-->" << this->cttRelations[j][0] -48 << ' ' 
					<< this->cttRelations[j][6] - 48 << ".\n";
		}
		cout << endl;
		//
		// start to sort topologically.
		//
		bool* vertexIsValid = new bool[this->cHeads];
		for (int m = 0; m < this->cHeads; m ++)
		{
			vertexIsValid[m] = true;
		}
		int cValidVertexes = this->cHeads;
		//
		// valid, inner edge, delete, think of validation when searching.
		//
		int addToThisPos = 0;
		while (cValidVertexes > 0)
		{
			// to find a vertex that has no inner edge.
			for (int n = 0; n < cHeads; n ++)		// tooooo much complexity.
			{
				if (vertexIsValid[n])
				{
					bool thisHasNoInnerEdge = true;
					PListNode currRefNextMember = anRvsdHeads[n].firstArc;	// it's not a reference here.
					while (currRefNextMember != nullptr)
					{
						if (vertexIsValid[currRefNextMember->indxVertex])
						{
							cout << "in positive graph found inner edge " << currRefNextMember->indxVertex << "-->" << n << ".\n";
							thisHasNoInnerEdge = false;
							break;
						}
						currRefNextMember = currRefNextMember->nextArc;
					}
					if (thisHasNoInnerEdge)
					{
						cout << "vertex " << n << " has no inner edge." << endl;
						frIndxSeq[addToThisPos] = n;
						addToThisPos ++;
						vertexIsValid[n] = false;
						cValidVertexes --;
					}
				}
			}			
		}
		cout << endl;
		// start negative topological sort.
		for (int m = 0; m < this->cHeads; m ++)
		{
			vertexIsValid[m] = true;
		}
		cValidVertexes = this->cHeads;
		addToThisPos = 0;
		while (cValidVertexes > 0)
		{
			// to find a vertex that has no inner edge.
			for (int n = 0; n < cHeads; n ++)		// tooooo much complexity.
			{
				if (vertexIsValid[n])
				{
					bool thisHasNoInnerEdge = true;
					PListNode currRefNextMember = anHeads[n].firstArc;	// it's not a reference here.
					while (currRefNextMember != nullptr)
					{
						if (vertexIsValid[currRefNextMember->indxVertex])
						{
							cout << "in negative graph found inner edge " << currRefNextMember->indxVertex << "-->" << n << ".\n";
							thisHasNoInnerEdge = false;
							break;
						}
						currRefNextMember = currRefNextMember->nextArc;
					}
					if (thisHasNoInnerEdge)
					{
						cout << "vertex " << n << " has no inner edge." << endl;
						frIndxNegaSeq[addToThisPos] = n;
						addToThisPos ++;
						vertexIsValid[n] = false;
						cValidVertexes --;
					}
				}
			}			
		}
		cout << endl;
		//
		// compute the critical path. frIndxSeq, frIndxNegaSeq, int frCriticalPath[], int& frCCriticalVertexes.
		//
		int* ve = new int[this->cHeads];
		for (int p = 0; p < this->cHeads; p ++)
		{
			ve[p] = -100;
		}
		ve[frIndxSeq[0]] = 0;
		for (int o = 1; o < this->cHeads; o ++)
		{
			// ve[frIndxSeq[o]].
			// for o == (1) to (cHeads - 1), compute ve[frIndxSeq[o]].
			// use inverted Heads->ListNodes structure to get the result of proper order's.
			PListNode currRefNextMember = anRvsdHeads[frIndxSeq[o]].firstArc;	// it's not a reference here.
			while (currRefNextMember != nullptr)
			{
				int theNew = ve[currRefNextMember->indxVertex] + currRefNextMember->weight;
				if (ve[frIndxSeq[o]] < theNew)
				{
					ve[frIndxSeq[o]] = theNew;
				}
				currRefNextMember = currRefNextMember->nextArc;
			}
		}
		cout << "ve:";
		for (int q = 0; q < this->cHeads; q ++)
		{
			cout << " v" << q << "_" << ve[q];
		}
		cout << ".\n";
		//
		// inverted below.
		//
		int* vl = new int[this->cHeads];
		for (int r = 0; r < this->cHeads; r ++)
		{
			vl[r] = 100;
		}
		vl[frIndxNegaSeq[0]] = ve[frIndxSeq[this->cHeads - 1]];
		for (int s = 1; s < this->cHeads; s ++)
		{
			// vl[frIndxNegaSeq[s]].
			// for s == (1) to (cHeads - 1), compute vl[s].
			// use proper order Heads->ListNodes structure to get the result of inverted order's.
			PListNode currRefNextMember = anHeads[frIndxNegaSeq[s]].firstArc;	// it's not a reference here.
			while (currRefNextMember != nullptr)
			{
				int theNew = vl[currRefNextMember->indxVertex] - currRefNextMember->weight;
				if (vl[frIndxNegaSeq[s]] > theNew)
				{
					vl[frIndxNegaSeq[s]] = theNew;
				}
				currRefNextMember = currRefNextMember->nextArc;
			}
		}
		cout << "vl:";
		for (int t = 0; t < this->cHeads; t ++)
		{
			cout << " v" << t << "_" << vl[t];
		}
		cout << ".\n";
		// 
		// compute frCriticalPath, frCCriticalVertexes.
		//
		for (int u = 0; u < this->cHeads; u ++)
		{
			if (ve[u] == vl[u])
			{
				frCriticalPath[frCCriticalVertexes ++] = u;
			}
		}
		// delete.
		delete[] ve;
		delete[] vl;
	}
};

int main()
{
	{
		// char initCttRelations[7][8] = {"0->2--2", "0->3--4", "1->3--5", "3->4--2", "3->5--3", "4->6--9", "5->6--7"};
		// char initCttRelations[7][8] = {"6->3--2", "6->5--4", "4->5--5", "5->1--2", "5->2--3", "1->0--9", "2->0--7"};
		char initCttRelations[11][8] = {"0->1--6", "0->2--4", "0->3--5", "1->4--1", "2->4--1", "3->5--2", "4->6--8", 
										"4->7--7", "5->7--4", "6->8--2", "7->8--4"};
		// weights can't be over 9.
		char initCttVertexes[10] = "ABCDEFGHI";
		DirectedAcyclineGraph dag(9, initCttVertexes, 11, initCttRelations);
		// do topological sorting.
		int sortedSeq[9] = {};
		int negaSortedSeq[9] = {};
		int criticalPath[9] = {};
		int cCriticalVertexes = 0;
		dag.TopoLogicalSortAndCriticalPath(sortedSeq, negaSortedSeq, criticalPath, cCriticalVertexes);
		cout << "topologically sorted:";
		for (int i = 0; i < 9; i ++)
		{
			cout << ' ' << sortedSeq[i];
		}
		cout << ".\n";
		cout << "topologically negatively sorted:";
		for (int j = 0; j < 9; j ++)
		{
			cout << ' ' << negaSortedSeq[j];
		}
		cout << ".\n";
		cout << "the critical path:";
		for (int k = 0; k < cCriticalVertexes; k ++)
		{
			cout << " v" << criticalPath[k] << "-" << initCttVertexes[criticalPath[k]];
		}
		cout << ".\n";
	} // memory leaks.
	system("pause");
	return 0;
}