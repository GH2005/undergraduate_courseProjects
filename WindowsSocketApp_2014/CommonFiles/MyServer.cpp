#include "MyServer.h"
#include <io.h>


CMyServer::CMyServer(const char* ipString, int portNumber, bool initSocket)
: bAccepting(false), hAcceptingThread(NULL), bInitSocket(initSocket)/*, cVec(0)*/
, bInChatAsServer(false), bInChatAsClient(false)
{
	this->outFileStream.open("MyServerLog.txt", std::ios::trunc);
	this->outFileStream.close();
	this->outFileStream.open("MyServerLog.txt", std::ios::app);

	if (initSocket) {
		this->OutFileStream("WSAStartup()", WSAStartup(MAKEWORD(2, 2), &this->wsaData));
	}

	this->mainSct = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(ipString);
	sa.sin_port = htons(portNumber);

	this->OutFileStream("bind()", bind(this->mainSct, (SOCKADDR*)&sa, sizeof(sa)));
	this->OutFileStream("listen()", listen(this->mainSct, 2));
}

CMyServer::~CMyServer()
{
	closesocket(this->mainSct);
	if (this->bInitSocket) {
		OutFileStream("WSACleanup()", WSACleanup());
	}
	this->outFileStream.close();
}

void CMyServer::OutFileStream(const char* funcName, int code) {
	this->outFileStream
		<< std::setw(20) << funcName << " returns: " << std::setw(6) << code << ";  "
		<< "WSAGetLastError(): " << std::setw(6) << WSAGetLastError() << ";  "
		<< "GetLastError(): " << std::setw(6) << GetLastError() << ".\n";
}

bool CMyServer::BeginAcceptances() {
	if (this->bAccepting) return false;
	this->bAccepting = true;
	this->hAcceptingThread = 
		chBEGINTHREADEX(NULL, 0, ::AcceptingThreadFunc, this, 0, NULL);
	this->OutFileStream("hAcceptingThread", (DWORD)this->hAcceptingThread);
	return true;
}

bool CMyServer::EndAcceptances() {
	if (this->bAccepting) {
		this->bAccepting = false;
		this->OutFileStream("CloseHandle(hAcceptingThread)", 
			CloseHandle(this->hAcceptingThread));
		return true;
	}
	else {
		return false;
	}
}

DWORD WINAPI ClientThreadFunc(PVOID pvInfo) {
	SClientInfo* pci = (SClientInfo*)pvInfo;

	// now I want to divide my server's services into three parts.
	char buf;		// contract: '0'->ping; '1'->file transport; '2'->chat.
	pci->pServer->OutFileStream("Division recv()", recv(pci->sct, &buf, 1, 0));

	if (buf == '0') {
		pci->pServer->OutFileStream("Ping recv()", recv(pci->sct, &buf, 1, 0));
		if (buf == 'p') {
			// if the client send a 'p', it is normal that it is testing ping.
			buf = 'q';
			pci->pServer->OutFileStream("Ping send()", send(pci->sct, &buf, 1, 0));
		}
		closesocket(pci->sct);
		delete pci;
		return 0;
	}
	else if (buf == '1') {
		//SBuffer	vecEle;
		//vecEle.pstrFileNameBuffer = new char[100];
		//vecEle.fileNameBufferLen = 100;
		//vecEle.thisIndexInVec = pci->pServer->cVec;
		//pci->pServer->cVec++;
		//pci->pServer->vec.push_back(vecEle);

		// but how can the busy-requesting function locate the index.
		char fileListBuffer[10000];
		fileListBuffer[0] = '\0';
		long hFile;
		_finddata_t fileInfo;

		hFile = _findfirst("C:\\ServerDir\\*", &fileInfo);
		pci->pServer->OutFileStream("_findfirst()", hFile);
		if (hFile != -1) {
			do {
				strcat_s(fileListBuffer, fileInfo.name);
				strcat_s(fileListBuffer, ";\n");
			} while (_findnext(hFile, &fileInfo) == 0);
		}
		_findclose(hFile);

		pci->pServer->OutFileStream("filelist send()",
			send(pci->sct, fileListBuffer, strlen(fileListBuffer) + 1, 0));

		pci->pServer->OutFileStream("file transport flag recv()", recv(pci->sct, &buf, 1, 0));
		if (buf != 't') {
			closesocket(pci->sct);
			delete pci;
			return 0;
		}
		else {
			char fileToTransportName[100];
			fileToTransportName[0] = '\0';
			int fileNameLen = recv(pci->sct, fileToTransportName, 100, 0);
			pci->pServer->OutFileStream("filename recv()", fileNameLen);

			char filePath[200];
			filePath[0] = '\0';
			strcpy_s(filePath, "C:\\ServerDir\\");
			strcat_s(filePath, fileToTransportName);
			pci->pServer->OutFileStream(filePath, 0);
			HANDLE hFile = CreateFile(filePath, GENERIC_READ, 0, 0, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, 0);
			pci->pServer->OutFileStream("CreateFile", (int)hFile);

			char sendBuf[102400];
			DWORD dwRead;
			BOOL bRet;
			while (1) {
				pci->pServer->OutFileStream("ReadFile", 
					bRet = ReadFile(hFile, sendBuf, 102400, &dwRead, NULL));
				if (dwRead == 0) {
					break;
				}
				else {
					pci->pServer->OutFileStream("file content send()", send(pci->sct, sendBuf, 
						dwRead, 0));
				}
			}
			CloseHandle(hFile);
		}
		closesocket(pci->sct);
		delete pci;
		return 0;
	}
	else if (buf == '2') {
		if (!pci->pServer->bInChatAsServer && !pci->pServer->bInChatAsClient) {
			pci->pServer->bInChatAsServer = true;
			pci->pServer->chatSocket = pci->sct;
			pci->pServer->OutFileStream("Chat Request Acceptance send()", send(pci->sct,
				"a", 1, 0));
		}
		else {
			pci->pServer->OutFileStream("Chat Request Denial send()", send(pci->sct,
				"d", 1, 0));
			closesocket(pci->sct);
		}
		delete pci;
		return 0;
	}
	else {
		pci->pServer->OutFileStream("Divisioin recv() bad char. code", -100);
		closesocket(pci->sct);
		delete pci;
		return 0;
	}
}

DWORD WINAPI AcceptingThreadFunc(PVOID pvMyServerObj) {
	CMyServer* pMyServer = (CMyServer*)pvMyServerObj;
	while (pMyServer->bAccepting) {
		SClientInfo* pci = new SClientInfo;
		pci->saLen = sizeof(pci->sa);
		pci->sct = accept(pMyServer->mainSct, (SOCKADDR*)&pci->sa, &pci->saLen);
		pci->pServer = pMyServer;
		pMyServer->OutFileStream("accept()", pci->sct);

		if (pci->sct != INVALID_SOCKET) {
			// Accepted, create a new thread for this client.
			HANDLE hClientThread = 
				chBEGINTHREADEX(NULL, 0, ::ClientThreadFunc, pci, 0, NULL);
			pMyServer->OutFileStream("hClientThread", (DWORD)hClientThread);
			CloseHandle(hClientThread);		// I don't care for it.
		}
		else {
			closesocket(pci->sct);
			delete pci;
		}
	}
	pMyServer->OutFileStream("AcceptingThread Exit", 0);
	return 0;
}

bool CMyServer::SendChatMessage(const char* pstrMsg) {
	// when socket is closed, return false to let the caller end the iteration.
	DWORD sendRet = send(this->chatSocket, pstrMsg, strlen(pstrMsg) + 1, 0);
	this->OutFileStream("chat message send()", sendRet);
	if (sendRet == SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool CMyServer::RecvChatMessage(char* pstrMsgToRet) {
	// if returns true, message receiving succeeds.
	// if returns false, chat has been terminated.
	// I need a 200 chars long buffer.
	int nBytesRecv = recv(this->chatSocket, pstrMsgToRet, 200, 0);
	this->OutFileStream("chat message recv()", nBytesRecv);
	if (nBytesRecv == 0 || nBytesRecv == SOCKET_ERROR) {
		closesocket(this->chatSocket);
		this->bInChatAsServer = false;
		return false;
	}
	else {
		return true;
	}
}

void CMyServer::TerminateChat() {
	closesocket(this->chatSocket);
	this->bInChatAsServer = false;
}