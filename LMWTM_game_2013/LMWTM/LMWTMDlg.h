// LMWTMDlg.h : ͷ�ļ�
//

#pragma once
#include "CArrow.h"
#include "mymfcbutton.h"
#include "generatebutton.h"
#include "tiaotiaobutton.h"

#define PAINT_PADDING 10

#define StatementSetCanPaintStatus(para)				\
	void Set##para##CanPaintStatus(BOOL inBool);

#define StatementGetCanPaintStatus(para)				\
	BOOL Get##para##CanPaintStatus();

struct ScreenCoordinate {
	int scrX, scrY, scrSqrMidX, scrSqrMidY;
};

// CLMWTMDlg �Ի���
class CLMWTMDlg : public CDialogEx
{
// ����
public:
	CLMWTMDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
public:
	void SetSideLen(CSizer inSizer);
	ScreenCoordinate CToSC(Coordinate inC);

public:
	StatementSetCanPaintStatus(Maze)
	StatementSetCanPaintStatus(Arrow)
	StatementSetCanPaintStatus(Line)
	StatementGetCanPaintStatus(Maze)
	StatementGetCanPaintStatus(Arrow)
	StatementGetCanPaintStatus(Line)
	void SetKeyboardCanUseStatus(BOOL inBool);
	BOOL GetKeyboardCanUseStatus();

// �Ի�������
	enum { IDD = IDD_LMWTM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	void PaintMaze(CClientDC & cdc);
	void PaintArrow(CClientDC & cdc);
	void PaintLine(CClientDC & cdc);

private:
	CSizer m_sizer;
	int nSideLen;
	BOOL bMazeCanPaint;
	BOOL bArrowCanPaint;
	BOOL bLineCanPaint;
	BOOL bKeyboardCanUse;
//public:
//	afx_msg void OnBnClickedMfcbuttonGenerate();
private:
	CMyMFCButton m_myMfcButton;
	CGenerateButton m_generateButton;
	CTiaotiaoButton m_tiaotiaoButton;
//public:
//	afx_msg void OnBnClickedMfcbuttonTiaotiao();
protected:
	BOOL PreTranslateMessage(MSG * pMsg);

// ʵ��
protected:
	HICON m_hIcon;

	// try this.
    afx_msg LRESULT OnMyResetButtons(
		WPARAM wParam, LPARAM lParam); 

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
