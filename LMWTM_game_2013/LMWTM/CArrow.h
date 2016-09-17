#pragma once

enum EDirection { ED_UP, ED_RIGHT, ED_DOWN, ED_LEFT };

class CArrow {
private:
	EDirection m_ed;
	int m_x;
	int m_y;
public:
	enum ECA { CA_DIRECTIONCHANGED, CA_MOVED,
		CA_BLOCKED };
	ECA MoveUp();
	ECA MoveDown();
	ECA MoveRight();
	ECA MoveLeft();
public:
	CArrow(EDirection inEd, int inX, int inY);
	~CArrow();
	void Set(EDirection inEd, int inX, int inY);
	EDirection GetDirection();
	int GetX();
	int GetY();
};

struct CSizer
{
	int width, height;
	CSizer(int inWidth, int inHeight)
		: width(inWidth), height(inHeight) {}
};

struct Coordinate
{
	int X, Y;// column and row
};