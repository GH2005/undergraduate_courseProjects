// MyMFCButton.cpp : ʵ���ļ�
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



// CMyMFCButton ��Ϣ�������




void CMyMFCButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	g_controller.ShowLine();

	CMFCButton::OnLButtonDown(nFlags, point);
}


void CMyMFCButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	g_controller.UndoShowLine();

	CMFCButton::OnLButtonUp(nFlags, point);
}
