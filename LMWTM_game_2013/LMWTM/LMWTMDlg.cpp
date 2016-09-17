
// LMWTMDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LMWTM.h"
#include "CController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLMWTMDlg 对话框

CLMWTMDlg::CLMWTMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLMWTMDlg::IDD, pParent), m_sizer(0, 0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->nSideLen = 0;
	this->bMazeCanPaint = FALSE;
	this->bArrowCanPaint = FALSE;
	this->bLineCanPaint = FALSE;
	this->bKeyboardCanUse = FALSE;
}

void CLMWTMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON_SHOWLINE, m_myMfcButton);
	DDX_Control(pDX, IDC_MFCBUTTON_GENERATE, m_generateButton);
	DDX_Control(pDX, IDC_MFCBUTTON_TIAOTIAO, m_tiaotiaoButton);
}

BEGIN_MESSAGE_MAP(CLMWTMDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	/*ON_BN_CLICKED(IDC_MFCBUTTON_GENERATE, &CLMWTMDlg::OnBnClickedMfcbuttonGenerate)
	ON_BN_CLICKED(IDC_MFCBUTTON_TIAOTIAO, &CLMWTMDlg::OnBnClickedMfcbuttonTiaotiao)*/
	ON_MESSAGE(WM_MY_RESETBUTTONS, OnMyResetButtons)
END_MESSAGE_MAP()

// CLMWTMDlg 消息处理程序

BOOL CLMWTMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	g_controller.RegisterWnd(this);
	// set buttons' availability.
	this->GetDlgItem(IDOK)->EnableWindow(FALSE);
	this->GetDlgItem(IDC_MFCBUTTON_GENERATE)
		->EnableWindow(TRUE);
	this->GetDlgItem(IDC_MFCBUTTON_SHOWLINE)
		->EnableWindow(FALSE);
	this->GetDlgItem(IDC_MFCBUTTON_TIAOTIAO)
		->EnableWindow(FALSE);

	this->bMazeCanPaint = FALSE;
	this->bArrowCanPaint = FALSE;
	this->bLineCanPaint = FALSE;
	this->bKeyboardCanUse = FALSE;
	// g_controller.GetTheVeryLabyrinth()->GenerateNewLabyrinth();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLMWTMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		// Paint.
		CClientDC cdc(this);
		this->PaintMaze(cdc);
		this->PaintLine(cdc);
		this->PaintArrow(cdc);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLMWTMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLMWTMDlg::SetSideLen(CSizer inSizer) {
	this->m_sizer = inSizer;
	CRect clientRect;
	GetClientRect(&clientRect);
	this->nSideLen = (clientRect.Height() - PAINT_PADDING * 2) / this->m_sizer.height;
}

ScreenCoordinate CLMWTMDlg::CToSC(Coordinate inC) {
	ScreenCoordinate sc;
	sc.scrX = PAINT_PADDING + inC.X * this->nSideLen;
	sc.scrY = PAINT_PADDING + inC.Y * this->nSideLen;
	sc.scrSqrMidX = sc.scrX + this->nSideLen / 2;
	sc.scrSqrMidY = sc.scrY + this->nSideLen / 2;
	return sc;
}

#define DefinationSetCanPaintStatus(para)										\
	void CLMWTMDlg::Set##para##CanPaintStatus(BOOL inBool)	{\
		this->b##para##CanPaint = inBool;											\
	}

DefinationSetCanPaintStatus(Maze)
DefinationSetCanPaintStatus(Arrow)
DefinationSetCanPaintStatus(Line)

#define DefinationGetCanPaintStatus(para)										\
	BOOL CLMWTMDlg::Get##para##CanPaintStatus()					{\
		return this->b##para##CanPaint;											\
	}

DefinationGetCanPaintStatus(Maze)
DefinationGetCanPaintStatus(Arrow)
DefinationGetCanPaintStatus(Line)

void CLMWTMDlg::SetKeyboardCanUseStatus(BOOL inBool) {
	this->bKeyboardCanUse = inBool;
}

BOOL CLMWTMDlg::GetKeyboardCanUseStatus() {
	return this->bKeyboardCanUse;
}

void CLMWTMDlg::PaintMaze(CClientDC & cdc) {
	if (this->bMazeCanPaint == FALSE) {
		return;
	}
	CBrush spaceBrush(RGB(230, 230, 230));
	CBrush wallBrush(RGB(49, 23, 23));
	CBrush originBrush(RGB(230, 36, 4));
	CBrush destBrush(RGB(29, 50, 205));
	CBrush footBrush(RGB(150, 150, 150));

	// begin painting.
	for (int x = 0; x < this->m_sizer.width; x ++) {
		for (int y = 0; y < this->m_sizer.height; y ++) {
			Coordinate everyC = { x, y };
			ScreenCoordinate everySc = this->CToSC(everyC);
			CRect everyRect(everySc.scrX, everySc.scrY, everySc.scrX
				+ this->nSideLen, everySc.scrY + this->nSideLen);
			BoxIdentity bi = g_controller.GetTheVeryLabyrinth()->GetMazeBoxIdentity(x, y);
			switch (bi)
			{
			case BoxIdentity::Space:
				cdc.FillRect(&everyRect, &spaceBrush);
				break;
			case BoxIdentity::Wall:
				cdc.FillRect(&everyRect, &wallBrush);
				break;
			case BoxIdentity::Origin:
				cdc.FillRect(&everyRect, &originBrush);
				break;
			case BoxIdentity::Destination:
				cdc.FillRect(&everyRect, &destBrush);
				break;
			case BoxIdentity::Footprint:
				cdc.FillRect(&everyRect, &footBrush);
				break;
			default:
				chMB(L"棋盘绘制出现异常.");
			}
		}
	}
}

void CLMWTMDlg::PaintArrow(CClientDC & cdc) {
	if (this->bArrowCanPaint == FALSE) {
		return;
	}
	int oneThirdSideLen = this->nSideLen / 2;
	Coordinate theC = { g_controller.GetTheVeryArrow()->GetX(),
		g_controller.GetTheVeryArrow()->GetY() };
	ScreenCoordinate theSC = this->CToSC(theC);
	int littleTop = theSC.scrSqrMidY - oneThirdSideLen;
	int littleBottom = theSC.scrSqrMidY + oneThirdSideLen;
	int littleLeft = theSC.scrSqrMidX - oneThirdSideLen;
	int littleRight = theSC.scrSqrMidX + oneThirdSideLen;

	CPen pen(PS_SOLID, 2, RGB(74, 55, 75));
	cdc.SelectObject(&pen);

	switch (g_controller.GetTheVeryArrow()->GetDirection())
	{
	case ED_UP:
		cdc.MoveTo(littleLeft, theSC.scrSqrMidY);
		cdc.LineTo(theSC.scrSqrMidX, littleTop);
		cdc.LineTo(littleRight, theSC.scrSqrMidY);
		cdc.MoveTo(theSC.scrSqrMidX, littleTop);
		cdc.LineTo(theSC.scrSqrMidX, littleBottom);
		break;
	case ED_DOWN:
		cdc.MoveTo(littleLeft, theSC.scrSqrMidY);
		cdc.LineTo(theSC.scrSqrMidX, littleBottom);
		cdc.LineTo(littleRight, theSC.scrSqrMidY);
		cdc.MoveTo(theSC.scrSqrMidX, littleBottom);
		cdc.LineTo(theSC.scrSqrMidX, littleTop);
		break;
	case ED_RIGHT:
		cdc.MoveTo(theSC.scrSqrMidX, littleTop);
		cdc.LineTo(littleRight, theSC.scrSqrMidY);
		cdc.LineTo(theSC.scrSqrMidX, littleBottom);
		cdc.MoveTo(littleRight, theSC.scrSqrMidY);
		cdc.LineTo(littleLeft, theSC.scrSqrMidY);
		break;
	case ED_LEFT:
		cdc.MoveTo(theSC.scrSqrMidX, littleTop);
		cdc.LineTo(littleLeft, theSC.scrSqrMidY);
		cdc.LineTo(theSC.scrSqrMidX, littleBottom);
		cdc.MoveTo(littleLeft, theSC.scrSqrMidY);
		cdc.LineTo(littleRight, theSC.scrSqrMidY);
		break;
	default:
		chMB(L"这应该永远看不到才是.");
	}
}

void CLMWTMDlg::PaintLine(CClientDC & cdc) {
	if (this->bLineCanPaint == FALSE) {
		return;
	}
	CPen pen(PS_SOLID, 2, RGB(75, 0, 0));
	cdc.SelectObject(&pen);
	
	for (int i = 0; i < g_controller.GetTheVeryLabyrinth()->GetShortestPathLength(); i ++) {
		Coordinate theC = { g_controller.GetTheVeryLabyrinth()
			->GetShortestPathBoxInfo(i).x,  g_controller.GetTheVeryLabyrinth()
			->GetShortestPathBoxInfo(i).y };
		EDirection theED = g_controller.GetTheVeryLabyrinth()
			->GetShortestPathBoxInfo(i).dir;
		ScreenCoordinate theSC = this->CToSC(theC);

		cdc.MoveTo(theSC.scrSqrMidX, theSC.scrSqrMidY);

		switch (theED)
		{
		case ED_UP:
			cdc.LineTo(theSC.scrSqrMidX, theSC.scrSqrMidY - this->nSideLen);
			break;
		case ED_DOWN:
			cdc.LineTo(theSC.scrSqrMidX, theSC.scrSqrMidY + this->nSideLen);
			break;
		case ED_RIGHT:
			cdc.LineTo(theSC.scrSqrMidX + this->nSideLen, theSC.scrSqrMidY);
			break;
		case ED_LEFT:
			cdc.LineTo(theSC.scrSqrMidX - this->nSideLen, theSC.scrSqrMidY);
			break;
		default:
			chMB(L"这应该永远看不到才是.");
		}
	}
}

//void CLMWTMDlg::OnBnClickedMfcbuttonGenerate()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	g_controller.GenerateMaze();
//}
//
//void CLMWTMDlg::OnBnClickedMfcbuttonTiaotiao()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	g_controller.Simulate();
//}

BOOL CLMWTMDlg::PreTranslateMessage(MSG* pMsg)       
{     
   if (pMsg->message == WM_KEYDOWN)
   {
		if (this->bKeyboardCanUse == FALSE) {
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		switch (pMsg->wParam)
		{
		case VK_UP:
			g_controller.GetTheVeryArrow()->MoveUp();
			break;
		case VK_DOWN:
			g_controller.GetTheVeryArrow()->MoveDown();
			break;
		case VK_RIGHT:
			g_controller.GetTheVeryArrow()->MoveRight();
			break;
		case VK_LEFT:
			g_controller.GetTheVeryArrow()->MoveLeft();
			break;
		}
		g_controller.RefreshWindow();
   }     
   return CDialogEx::PreTranslateMessage(pMsg); 

}

LRESULT CLMWTMDlg::OnMyResetButtons(WPARAM, LPARAM) {
	// reset paint status and Keyboard availability.
	CLMWTMDlg * pDlg = this;
	pDlg->SetMazeCanPaintStatus(TRUE);
	pDlg->SetArrowCanPaintStatus(TRUE);
	pDlg->SetLineCanPaintStatus(FALSE);
	pDlg->SetKeyboardCanUseStatus(TRUE);

	// reset buttons' availability.
	pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_MFCBUTTON_GENERATE)
		->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_MFCBUTTON_SHOWLINE)
		->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_MFCBUTTON_TIAOTIAO)
		->EnableWindow(TRUE);

	return 311;
}