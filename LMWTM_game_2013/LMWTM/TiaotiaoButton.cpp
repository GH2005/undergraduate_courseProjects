#include "stdafx.h"
#include "LMWTM.h"
#include "TiaotiaoButton.h"
#include "CController.h"


CTiaotiaoButton::CTiaotiaoButton(void)
{
}


CTiaotiaoButton::~CTiaotiaoButton(void)
{
}
BEGIN_MESSAGE_MAP(CTiaotiaoButton, CMFCButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CTiaotiaoButton::OnBnClicked)
END_MESSAGE_MAP()


void CTiaotiaoButton::OnBnClicked()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_controller.Simulate();
}
