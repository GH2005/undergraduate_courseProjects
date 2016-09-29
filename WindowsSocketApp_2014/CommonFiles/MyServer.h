#pragma once
// CMyServer definition.
// only one instance is permitted to create among the whole program.

#include <fstream>
#include <iomanip>
#include <WinSock2.h>
#include <vector>
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

//struct SBuffer {
//	char*	pstrChatBuffer;
//	char*	pstrFileBuffer;
//	char*	pstrFileNameBuffer;
//	int		chatBufferLen;
//	int		fileBufferLen;
//	int		fileNameBufferLen;
//	int		thisIndexInVec;
//};

class CMyServer
{
private:
	WSADATA			wsaData;
	std::ofstream		outFileStream;
	SOCKET			mainSct;
	bool					bAccepting;
	HANDLE			hAcceptingThread;
	bool					bInitSocket;
	//int					cVec;
	//std::vector<SBuffer> vec;
	SOCKET			chatSocket;
public:
	bool					bInChatAsClient;
	bool					bInChatAsServer;
	CMyServer(const char*, int, bool);
	~CMyServer();
	bool BeginAcceptances();
	bool EndAcceptances();
	bool SendChatMessage(const char*);
	bool RecvChatMessage(char*);
	void TerminateChat();
protected:
	void OutFileStream(const char *, int);
	friend DWORD WINAPI AcceptingThreadFunc(PVOID pvMyServerObj);
	friend DWORD WINAPI ClientThreadFunc(PVOID pvInfo);
};

struct SClientInfo {
	SOCKADDR sa;
	SOCKET sct;
	int saLen;
	CMyServer* pServer;
};
