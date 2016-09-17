
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持


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











