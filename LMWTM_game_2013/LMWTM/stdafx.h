
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��


///////////////////////// Jeffrey Richter's mechanisms ///////////

/* 
Pragma message helper macro

When the compiler sees a line like this:
   #pragma chMSG(Fix this later)

it outputs a line like this:

  c:\CD\CmnHdr.h(82):Fix this later

You can easily jump directly to this line and examine the 
surrounding code.
*/

#define chSTR2(x) #x
#define chSTR(x)  chSTR2(x)			
// the macro following needs a translated complete macro.
#define chMSG(desc) message(__FILE__ "(" chSTR(__LINE__) "):" #desc)


/* Quick Messagebox Macro, wchar_t edition */
inline void chMB(PCWSTR szMsg) {
   wchar_t szTitle[MAX_PATH];
   GetModuleFileNameW(NULL, szTitle, _countof(szTitle));
   MessageBoxW(GetActiveWindow(), szMsg, szTitle, MB_OK);
}

////////////////////////////////////////////////////////////////////////











