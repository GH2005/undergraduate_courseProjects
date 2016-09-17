#pragma once


// CMyMFCButton

class CMyMFCButton : public CMFCButton
{
	DECLARE_DYNAMIC(CMyMFCButton)

public:
	CMyMFCButton();
	virtual ~CMyMFCButton();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

protected:
	DECLARE_MESSAGE_MAP()
};


