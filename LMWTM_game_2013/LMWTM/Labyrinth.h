#pragma once

#include "CArrow.h"

enum Direction { NORTH, EAST, SOUTH, WEST };
struct PathBoxInfo
{
int x,y;
EDirection dir;
};
enum BoxIdentity
{
Space, Wall, Origin, Destination, Footprint
};
class CLabyrinth
{
private:
CArrow* pArrow;

int **maze;
int width,height;

Coordinate startingPoint, terminalPoint, arrowPoint;

PathBoxInfo *shortestPath;
int shortestPathLength;
PathBoxInfo *simulativePath;
int simulativePathLength;

Direction GetRelativeDirection(PathBoxInfo, PathBoxInfo);
Direction GetRelativeDirection(int,int,int,int);
void InitializeInstance();
void ResetMazeBox();
void KnockDownTheWall(int, int);
bool IsInMaze(int, int);
void ClearFootprint();
void AIVisit(int, int, bool&);

public:
CLabyrinth(void);
CLabyrinth(int width,int height);
~CLabyrinth(void);
void GenerateNewLabyrinth();
void PrintMaze();
void CalculateShortestPath();
int GetShortestPathLength();
PathBoxInfo GetShortestPathBoxInfo(int index);
int GetSimulativePathLength();
PathBoxInfo GetSimulativePathBoxInfo(int index);
void SimulateSearching();
BoxIdentity GetMazeBoxIdentity(int column,int row);
};