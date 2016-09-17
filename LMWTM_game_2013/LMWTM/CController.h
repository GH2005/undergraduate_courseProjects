// CController.h:
//		class CController
//		enum EDirection
//		macro chMSG, chMB
#pragma once

#include "LMWTMDlg.h"
#include "Labyrinth.h"

class CController {
// class CController, management of the arrow, dialogex,
//	and the maze.
private:
	CLMWTMDlg *	m_pMainWnd;		// fuck, name existed.
	CLabyrinth *		m_Labyrinth;
	CArrow				m_pArrow;
	CSizer				m_sizer;
public:
	CController();
	~CController();
	void RefreshWindow();
	void RegisterWnd(CLMWTMDlg * inpWnd);
	void SetSizer(CSizer inSizer);
	CArrow * GetTheVeryArrow();
	CLabyrinth * GetTheVeryLabyrinth();

	// what the buttons do.
	BOOL GenerateMaze();
	BOOL ShowLine();
	BOOL UndoShowLine();
	BOOL Simulate();
};

extern CController g_controller;
