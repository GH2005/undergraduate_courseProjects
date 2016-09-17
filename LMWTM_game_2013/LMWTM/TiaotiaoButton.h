#pragma once
#include "afxbutton.h"
class CTiaotiaoButton :
	public CMFCButton
{
public:
	CTiaotiaoButton(void);
	~CTiaotiaoButton(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClicked();
};

