#pragma once
// CMyClient definition.
// only one instance permitted.

#include <fstream>
#include <iomanip>
#include <WinSock2.h>
#include <process.h>

// This macro function calls the C runtime's _beginthreadex function. 
// The C runtime library doesn't want to have any reliance on Windows' data 
// types such as HANDLE. This means that a Windows programmer needs to cast
// values when using _beginthreadex. Since this is terribly inconvenient, 
// I created this macro to perform the casting.
typedef unsigned(__stdcall *PTHREAD_START) (void *);

#define chBEGINTHREADEX(psa, cbStackSize, pfnStartAddr, \
	pvParam, dwCreateFlags, pdwThreadId)                 \
	((HANDLE)_beginthreadex(                          \
	(void *)        (psa),                         \
	(unsigned)      (cbStackSize),                 \
	(PTHREAD_START) (pfnStartAddr),                \
	(void *)        (pvParam),                     \
	(unsigned)      (dwCreateFlags),               \
	(unsigned *)    (pdwThreadId)))

class CMyClient
{
private:
	WSADATA			wsaData;
	std::ofstream		outFileStream;
	bool					bInitSocket;
	SOCKET			sct;
public:
	CMyClient(bool);
	~CMyClient();
	void OutFileStream(const char*, int);
	int RequestForPing(const char*, int);
	char* RequestForFileList(const char*, int, int*);
	bool RequestForFileTransport(const char* fileName, bool);
	bool RequestForChat(const char*, int);
	bool SendChatMessage(const char*);
	bool RecvChatMessage(char*);
	void TerminateChat();
};