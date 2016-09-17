#include "stdafx.h"
#include "LMWTM.h"
#include "time.h"
#include <cstdlib>
#include <iostream>
#include "Labyrinth.h"
#include <Windows.h>
#include "CController.h"
#include "CArrow.h"
using namespace std;

#pragma region Private Methods
CLabyrinth::CLabyrinth(void):width(19),height(19)
{
	InitializeInstance();
}

CLabyrinth::CLabyrinth(int w,int h):width(w),height(h)
{
	if(w%2==0||h%2==0)
	{
		throw new exception("width and height must be odd number");
	}
	if(w<3||h<3)
	{
		throw new exception("width and height must be bigger than 1");
	}
	InitializeInstance();
}

CLabyrinth::~CLabyrinth(void)
{
	delete []simulativePath;
	delete []shortestPath;

	for(int i=0;i<height;i++)
	{
		delete []maze[i];
	}
	delete []maze;
}

void CLabyrinth::InitializeInstance()
{
	maze=new int*[height];
	for(int i=0;i<height;i++)
	{
		maze[i]=new int[width];
	}

	startingPoint.X=1;
	startingPoint.Y=1;
	terminalPoint.X=width-2;
	terminalPoint.Y=height-2;

	shortestPath=new PathBoxInfo[height*width];
	simulativePath=new PathBoxInfo[height*width];

	pArrow=NULL;
}

void CLabyrinth::GenerateNewLabyrinth()
{
	srand((unsigned int)time(0));
	ResetMazeBox();
	KnockDownTheWall(1,1);
	maze[startingPoint.Y][startingPoint.X]=BoxIdentity::Origin;
	maze[terminalPoint.Y][terminalPoint.X]=BoxIdentity::Destination;
	pArrow=g_controller.GetTheVeryArrow();
	pArrow->Set((EDirection)EAST,startingPoint.Y, startingPoint.X);
	g_controller.RefreshWindow();
}

void CLabyrinth::ResetMazeBox()
{
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			maze[i][j]=BoxIdentity::Wall;
		}
	}
}

bool CLabyrinth::IsInMaze(int x,int y)
{
	if(x>=0&&x<height&&y>=0&&y<width)
		return true;
    return false;
}

Direction CLabyrinth::GetRelativeDirection(PathBoxInfo a, PathBoxInfo b)
{	// a is anchored
	int x1=a.y, y1=a.x, x2=b.y, y2=b.x;
	return GetRelativeDirection(x1,y1,x2,y2);
}

Direction CLabyrinth::GetRelativeDirection(int x1,int y1,int x2,int y2)
{	// a is anchored
	if(x2==x1-1)
	{
		return NORTH;
	}
	if(y2==y1+1)
	{
		return EAST;
	}
	if(x2==x1+1)
	{
		return SOUTH;
	}
	if(y2==y1-1)
	{
		return WEST;
	}
	throw exception("function GetRelativeDirection: invalid parameters!"); 
}

void CLabyrinth::ClearFootprint()
{
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(maze[i][j]==BoxIdentity::Footprint)
			{
				maze[i][j]=BoxIdentity::Space;
			}
		}
	}
	maze[startingPoint.Y][startingPoint.X]=BoxIdentity::Origin;
	
}

void CLabyrinth::KnockDownTheWall(int x,int y)
{
		//PrintMaze();
		Sleep(20);
		g_controller.RefreshWindow();
		maze[x][y]=BoxIdentity::Space;
		int dirs[4]={NORTH, EAST, SOUTH, WEST};

        for(int i=0;i<4;++i)
        {
            int r=rand()&3;
            int temp=dirs[r];
            dirs[r]=dirs[i];
            dirs[i]=temp;
        }

        for(int i=0;i<4;++i)
        {
            int dx=0,dy=0;
            switch(dirs[i])
            {
                case NORTH:
                    dx=-1;
                    break;
                case SOUTH:
                    dx=1;
                    break;
                case EAST:
                    dy=1;
                    break;
                case WEST:
                    dy=-1;
                    break;
            }

            int x2=x+(dx<<1);
            int y2=y+(dy<<1);
            if(IsInMaze(x2,y2))
            {
				if(maze[x2][y2]==Wall)
                {
					maze[x2-dx][y2-dy]=BoxIdentity::Space; 
					KnockDownTheWall(x2,y2);
                }
             }
        }
}

void CLabyrinth::AIVisit(int x,int y,bool& found)
{
	if(x==terminalPoint.Y&&y==terminalPoint.X)
	{
		//cout<<"destination found....."<<endl;
		found=true;
		maze[x][y]=Destination;
		return;
	}
	const int dirs[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
	for(int i=0;i<4;i++)
	{
		int nx=x+dirs[i][0], ny=y+dirs[i][1];
		if(IsInMaze(nx,ny)&&(maze[nx][ny]==Space||maze[nx][ny]==Destination))
		{
			simulativePathLength++;
			simulativePath[simulativePathLength].x=ny;
			simulativePath[simulativePathLength].y=nx;
			simulativePath[simulativePathLength-1].dir=
(EDirection)GetRelativeDirection(simulativePath[simulativePathLength-1],simulativePath[simulativePathLength]);
			
			pArrow->Set((EDirection)GetRelativeDirection(x,y,nx,ny),ny,nx);

			g_controller.RefreshWindow();
			Sleep(20);

			maze[nx][ny]=Footprint;
			AIVisit(nx, ny, found);
			if(found)
			{
				return;
			}	
			maze[nx][ny]=Space;
			
			pArrow->Set((EDirection)GetRelativeDirection(nx,ny,x,y),y,x);

			g_controller.RefreshWindow();
			Sleep(20);

			simulativePathLength--;
		}
	}
}
#pragma endregion

#pragma region Public Methods
BoxIdentity CLabyrinth::GetMazeBoxIdentity(int column,int row)
{
	if(column>=0&&column<width&&row>=0&&row<height)
	{
		return (BoxIdentity)(maze[row][column]);
	}
	throw new exception();
}

int CLabyrinth::GetShortestPathLength()
{
	return shortestPathLength;
}

int CLabyrinth::GetSimulativePathLength()
{
	return simulativePathLength;
}

PathBoxInfo CLabyrinth::GetShortestPathBoxInfo(int index)
{
	return shortestPath[index];
}

PathBoxInfo CLabyrinth::GetSimulativePathBoxInfo(int index)
{
	return simulativePath[index];
}

void CLabyrinth::PrintMaze()
{
	system("cls");
	int map[200][200];
	for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
			map[i][j]=maze[i][j];
        }
    }
	for(int i=0;i<shortestPathLength;i++)
	{
		if(shortestPath[i].dir==NORTH)
		{
			map[shortestPath[i].y][shortestPath[i].x]=100;
		}
		else if(shortestPath[i].dir==EAST)
		{
			map[shortestPath[i].y][shortestPath[i].x]=101;
		}
		else if(shortestPath[i].dir==SOUTH)
		{
			map[shortestPath[i].y][shortestPath[i].x]=102;
		}
		else if(shortestPath[i].dir==WEST)
		{
			map[shortestPath[i].y][shortestPath[i].x]=103;
		}
	}
	for(int i=0;i<simulativePathLength;i++)
	{
		if(simulativePath[i].dir==NORTH)
		{
			map[simulativePath[i].y][simulativePath[i].x]=200;
		}
		else if(simulativePath[i].dir==EAST)
		{
			map[simulativePath[i].y][simulativePath[i].x]=201;
		}
		else if(simulativePath[i].dir==SOUTH)
		{
			map[simulativePath[i].y][simulativePath[i].x]=202;
		}
		else if(simulativePath[i].dir==WEST)
		{
			map[simulativePath[i].y][simulativePath[i].x]=203;
		}
	}
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
			if(map[i][j]==Wall)
			{
				cout<<"#";
			}
			else if(map[i][j]==Space)
			{
				cout<<" ";
			}
			else if(map[i][j]==Origin)
			{
				cout<<"S";
			}
			else if(map[i][j]==Destination)
			{
				cout<<"T";
			}
			else if(map[i][j]==200)
			{
				cout<<"^";
			}
			else if(map[i][j]==201)
			{
				cout<<">";
			}
			else if(map[i][j]==202)
			{
				cout<<"V";
			}
			else if(map[i][j]==203)
			{
				cout<<"<";
			}
        }
        cout<<endl;
    }
}

void CLabyrinth::CalculateShortestPath()
{
	struct Node
	{
		int x, y, layer, parent;
	};
	Node *queue=new Node[width*height];

	int top=0;
	int *path=new int[width*height];

	int dirs[4][2]={{-1,0},{0,1},{1,0},{0,-1}};


	CArrow* pArow=g_controller.GetTheVeryArrow();
	int sx=pArow->GetY(),sy=pArow->GetX(),tx=terminalPoint.Y, ty=terminalPoint.X, head=0,tail=1;

	shortestPathLength=0;

	if(sx==tx&&sy==ty)
	{
		return;
	}

	queue[head].x=sx;
	queue[head].y=sy;
	queue[head].layer=0;
	queue[head].parent=-1;
	
	maze[sx][sy]=Footprint;

	bool found=false;
	while(head<tail&&found==false)
	{
		int cx=queue[head].x, cy=queue[head].y, clayer=queue[head].layer;
		for(int i=0;i<4;i++)
		{
			int nx=cx+dirs[i][0], ny=cy+dirs[i][1];
			if(maze[nx][ny]==Destination)
			{
				found=true;
				int current=head;
				path[top++]=current;
				while(queue[current].parent!=-1)
				{
					current=queue[current].parent;
					path[top++]=current;
				}
				break;
			}
			if(IsInMaze(nx,ny)&&maze[nx][ny]==Space)
			{
				queue[tail].x=nx;
				queue[tail].y=ny;
				queue[tail].layer=clayer+1;
				queue[tail].parent=head;
				tail++;

				maze[nx][ny]=Footprint;
			}
		}
		head++;
	}
	ClearFootprint();
	
	for(int i=top-1;i>=0;i--)
	{
		shortestPath[shortestPathLength].x=queue[path[i]].y;
		shortestPath[shortestPathLength].y=queue[path[i]].x;
		shortestPathLength++;
	}
	shortestPath[shortestPathLength].x=ty;
	shortestPath[shortestPathLength].y=tx;
	for(int i=0;i<shortestPathLength;i++)
	{
		shortestPath[i].dir=
			(EDirection)GetRelativeDirection(shortestPath[i],shortestPath[i+1]);
	}
	delete []path;
	delete []queue;
}

void CLabyrinth::SimulateSearching()
{
	//cout<<"simulatesearching called..."<<endl;
	bool found=false;

	pArrow=g_controller.GetTheVeryArrow();
	pArrow->Set(ED_DOWN,pArrow->GetX(),pArrow->GetY());

	simulativePath[0].x=pArrow->GetX();
	simulativePath[0].y=pArrow->GetY();
	simulativePathLength=0;
	

	g_controller.RefreshWindow();

	//ClearFootprint();
	AIVisit(pArrow->GetY(),pArrow->GetX(),found);
	g_controller.RefreshWindow();


	ClearFootprint();
}
#pragma endregion