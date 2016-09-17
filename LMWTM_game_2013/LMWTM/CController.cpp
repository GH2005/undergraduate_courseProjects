// CController.cpp

#include "stdafx.h"
#include "LMWTM.h"
#include  "CController.h"

CController g_controller;

void CController::RefreshWindow()
{
	SendMessageW(this->m_pMainWnd->GetSafeHwnd(), WM_PAINT, 0, 0);
}

void CController::RegisterWnd(CLMWTMDlg * inpWnd) {
	this->m_pMainWnd = inpWnd;
	this->m_pMainWnd->SetSideLen(this->m_sizer);
}

CController::CController()
	: m_pArrow(ED_LEFT, 0, 0), m_sizer(49, 49), m_pMainWnd(NULL) {
		this->m_Labyrinth = new CLabyrinth(m_sizer.width, m_sizer.height);
}

CController::~CController() {
	this->m_Labyrinth->~CLabyrinth();
}

void CController::SetSizer(CSizer inSizer) {
	this->m_sizer = inSizer;
}

CArrow * CController::GetTheVeryArrow() {
	return &(this->m_pArrow);
}

CLabyrinth * CController::GetTheVeryLabyrinth() {
	return this->m_Labyrinth;
}

BOOL CController::GenerateMaze() {
	// it can be inferred that messages sent during generating has been stored until
	// this function returned.

	// process.
	this->m_Labyrinth->GenerateNewLabyrinth();

	return TRUE;
}

BOOL CController::ShowLine() {
	// set paint status.
	this->m_pMainWnd->SetLineCanPaintStatus(TRUE);

	// process.
	this->m_Labyrinth->CalculateShortestPath();

	// paint.
	this->RefreshWindow();

	return TRUE;
}

BOOL CController::UndoShowLine() {
	// set paint status.
	this->m_pMainWnd->SetLineCanPaintStatus(FALSE);

	// paint.
	this->RefreshWindow();

	return TRUE;
}

BOOL CController::Simulate() {
	// set paint status and Keyboard availability.
	this->m_pMainWnd->SetKeyboardCanUseStatus(FALSE);

	// set buttons' availability.
	this->m_pMainWnd->GetDlgItem(IDOK)->EnableWindow(FALSE);
	//this->m_pMainWnd->GetDlgItem(IDC_MFCBUTTON_GENERATE)
	//	->EnableWindow(FALSE);
	//this->m_pMainWnd->GetDlgItem(IDC_MFCBUTTON_SHOWLINE)
	//	->EnableWindow(FALSE);
	//this->m_pMainWnd->GetDlgItem(IDC_MFCBUTTON_TIAOTIAO)
	//	->EnableWindow(FALSE);

	// save the arrow.
	int saveX = this->m_pArrow.GetX();
	int saveY = this->m_pArrow.GetY();
	EDirection saveED = this->m_pArrow.GetDirection();

	// process.
	this->m_Labyrinth->SimulateSearching();

	// restore the arrow.
	this->m_pArrow.Set(saveED, saveX, saveY);
	Sleep(50);
	this->RefreshWindow();

	// set paint status and Keyboard availability.
	this->m_pMainWnd->SetKeyboardCanUseStatus(TRUE);

	// set buttons' availability. useless.
	/*this->m_pMainWnd->GetDlgItem(IDOK)->EnableWindow(TRUE);*/
	//this->m_pMainWnd->GetDlgItem(IDC_MFCBUTTON_GENERATE)
	//	->EnableWindow(TRUE);
	//this->m_pMainWnd->GetDlgItem(IDC_MFCBUTTON_SHOWLINE)
	//	->EnableWindow(TRUE);
	//this->m_pMainWnd->GetDlgItem(IDC_MFCBUTTON_TIAOTIAO)
	//	->EnableWindow(TRUE);

	return TRUE;
}