#include "stdafx.h"
#include "LMWTM.h"
#include "GenerateButton.h"
#include "CController.h"


CGenerateButton::CGenerateButton(void)
{
}


CGenerateButton::~CGenerateButton(void)
{
}
BEGIN_MESSAGE_MAP(CGenerateButton, CMFCButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CGenerateButton::OnBnClicked)
END_MESSAGE_MAP()


void CGenerateButton::OnBnClicked()
{
	// TODO: 在此添加控件通知处理程序代码
	CLMWTMDlg * pDlg = ((CLMWTMDlg * )theApp.m_pMainWnd);
	
	// set paint status and Keyboard availability.
	pDlg->SetMazeCanPaintStatus(TRUE);
	pDlg->SetArrowCanPaintStatus(FALSE);
	pDlg->SetLineCanPaintStatus(FALSE);
	pDlg->SetKeyboardCanUseStatus(FALSE);

	// set buttons' availability.
	pDlg->GetDlgItem(IDOK)->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDC_MFCBUTTON_GENERATE)
		->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDC_MFCBUTTON_SHOWLINE)
		->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDC_MFCBUTTON_TIAOTIAO)
		->EnableWindow(FALSE);

	// process.s
	g_controller.GenerateMaze();

	// useless.
	//// reset paint status and Keyboard availability.
	//pDlg->SetMazeCanPaintStatus(TRUE);
	//pDlg->SetArrowCanPaintStatus(TRUE);
	//pDlg->SetLineCanPaintStatus(FALSE);
	//pDlg->SetKeyboardCanUseStatus(TRUE);

	//// reset buttons' availability.
	//pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);
	//pDlg->GetDlgItem(IDC_MFCBUTTON_GENERATE)
	//	->EnableWindow(TRUE);
	//pDlg->GetDlgItem(IDC_MFCBUTTON_SHOWLINE)
	//	->EnableWindow(TRUE);
	//pDlg->GetDlgItem(IDC_MFCBUTTON_TIAOTIAO)
	//	->EnableWindow(TRUE);
	
	// try this. still useless.
	::PostMessageW(theApp.m_pMainWnd->GetSafeHwnd(), WM_MY_RESETBUTTONS, 0, 0);
}
