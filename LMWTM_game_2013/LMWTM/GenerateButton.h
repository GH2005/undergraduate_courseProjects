#pragma once
#include "afxbutton.h"
class CGenerateButton :
	public CMFCButton
{
public:
	CGenerateButton(void);
	~CGenerateButton(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClicked();
};