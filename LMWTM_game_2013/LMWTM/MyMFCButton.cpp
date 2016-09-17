// MyMFCButton.cpp : 实现文件
//

#include "stdafx.h"
#include "LMWTM.h"
#include "MyMFCButton.h"
#include "CController.h"


// CMyMFCButton

IMPLEMENT_DYNAMIC(CMyMFCButton, CMFCButton)

CMyMFCButton::CMyMFCButton()
{

}

CMyMFCButton::~CMyMFCButton()
{
}


BEGIN_MESSAGE_MAP(CMyMFCButton, CMFCButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMyMFCButton 消息处理程序




void CMyMFCButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	g_controller.ShowLine();

	CMFCButton::OnLButtonDown(nFlags, point);
}


void CMyMFCButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	g_controller.UndoShowLine();

	CMFCButton::OnLButtonUp(nFlags, point);
}
