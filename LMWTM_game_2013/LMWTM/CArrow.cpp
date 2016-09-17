// CArrow.cpp

#include "stdafx.h"
#include "LMWTM.h"
#include "CArrow.h"
#include "CController.h"
#include "Labyrinth.h"


CArrow::ECA CArrow::MoveUp() {
	if (this->m_ed != ED_UP) {
		m_ed = ED_UP;
		return CA_DIRECTIONCHANGED;
	}
	else if (g_controller.GetTheVeryLabyrinth()->
		GetMazeBoxIdentity(this->m_x, this->m_y - 1) == BoxIdentity::Wall) {
			return CA_BLOCKED;
	}
	else
	{
		this->m_y --;
		return CA_MOVED;
	}
}

CArrow::ECA CArrow::MoveDown() {
	if (this->m_ed != ED_DOWN) {
		m_ed = ED_DOWN;
		return CA_DIRECTIONCHANGED;
	}
	else if (g_controller.GetTheVeryLabyrinth()->
		GetMazeBoxIdentity(this->m_x, this->m_y + 1) == BoxIdentity::Wall) {
			return CA_BLOCKED;
	}
	else
	{
		this->m_y ++;
		return CA_MOVED;
	}
}

CArrow::ECA CArrow::MoveRight() {
	if (this->m_ed != ED_RIGHT) {
		m_ed = ED_RIGHT;
		return CA_DIRECTIONCHANGED;
	}
	else if (g_controller.GetTheVeryLabyrinth()->
		GetMazeBoxIdentity(this->m_x + 1, this->m_y) == BoxIdentity::Wall) {
			return CA_BLOCKED;
	}
	else
	{
		this->m_x ++;
		return CA_MOVED;
	}
}

CArrow::ECA CArrow::MoveLeft() {
	if (this->m_ed != ED_LEFT) {
		m_ed = ED_LEFT;
		return CA_DIRECTIONCHANGED;
	}
	else if (g_controller.GetTheVeryLabyrinth()->
		GetMazeBoxIdentity(this->m_x - 1, this->m_y) == BoxIdentity::Wall) {
			return CA_BLOCKED;
	}
	else
	{
		this->m_x --;
		return CA_MOVED;
	}
}

CArrow::CArrow(EDirection inEd, int inX, int inY)
	: m_ed(inEd), m_x(inX), m_y(inY) {}

CArrow::~CArrow() {}

void CArrow::Set(EDirection inEd, int inX, int inY) {
	this->m_ed = inEd;
	this->m_x = inX;
	this->m_y = inY;
}

EDirection CArrow::GetDirection() {
	return this->m_ed;
}

int CArrow::GetX() {
	return this->m_x;
}

int CArrow::GetY() {
	return this->m_y;
}