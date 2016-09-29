#include "MyClient.h"
#include <ctime>

CMyClient::CMyClient(bool initSocket)
{
	this->outFileStream.open("MyClientLog.txt", std::ios::trunc);
	this->outFileStream.close();
	this->outFileStream.open("MyClientLog.txt", std::ios::app);
	if (initSocket) {
		this->OutFileStream("WSAStartup()", WSAStartup(MAKEWORD(2, 2), &this->wsaData));
	}
}

CMyClient::~CMyClient()
{
	if (this->bInitSocket) {
		OutFileStream("WSACleanup()", WSACleanup());
	}
	this->outFileStream.close();
}

void CMyClient::OutFileStream(const char* funcName, int code) {
	this->outFileStream 
		<< std::setw(20) << funcName << " returns: " << std::setw(6) << code << ";  "
		<< "WSAGetLastError(): " << std::setw(6) << WSAGetLastError() << ";  " 
		<< "GetLastError(): " << std::setw(6) << GetLastError() << ".\n";
}

int CMyClient::RequestForPing(const char* serverIpString, int serverPort) {
	// returns the ping value in ms.
	this->sct = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sain;
	sain.sin_family = AF_INET;
	sain.sin_addr.s_addr = inet_addr(serverIpString);
	sain.sin_port = htons(serverPort);
	this->OutFileStream("Ping connect()", 
		connect(this->sct, (SOCKADDR*)&sain, sizeof(sain)));
	this->OutFileStream("Ping request send()", send(this->sct, "0", 1, 0));

	time_t tBegin = clock();

	this->OutFileStream("Ping send()", send(this->sct, "p", 1, 0));
	char buf;
	this->OutFileStream("Ping recv()", recv(this->sct, &buf, 1, 0));

	closesocket(this->sct);
	if (buf == 'q') {
		time_t tEnd = clock();
		return (int)(double(tEnd - tBegin) / CLOCKS_PER_SEC * 1000);
	}
	else {
		return -100;
	}
}

char* CMyClient::RequestForFileList(const char* serverIpString, int serverPort, int* returnLen) {
	// returns buffer pointer.
	// FileList is in the heap and needs deleting.
	this->sct = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sain;
	sain.sin_family = AF_INET;
	sain.sin_addr.s_addr = inet_addr(serverIpString);
	sain.sin_port = htons(serverPort);
	this->OutFileStream("File Request connect()", 
		connect(this->sct, (SOCKADDR*)&sain, sizeof(sain)));
	this->OutFileStream("File request send()", send(this->sct, "1", 1, 0));

	// wait for file list.
	char* fileListBuffer= new char[10000];
	*returnLen = recv(this->sct, fileListBuffer, 10000, 0);
	this->OutFileStream("file list recv()", *returnLen);
	return fileListBuffer;
}

bool CMyClient::RequestForFileTransport(const char* fileName, bool needTrans) {
	if (!needTrans) {
		this->OutFileStream("deny trans send()", send(this->sct, "n", 1, 0));
		closesocket(this->sct);
		return true;
	}
	// real file transport.
	this->OutFileStream("ack trans send()", send(this->sct, "t", 1, 0));
	this->OutFileStream("file name send()", send(this->sct, fileName, strlen(fileName) + 1, 0));

	char recvBuf[102400];
	DWORD cBytesRecv;
	DWORD cBytesWritten;
	char filePath[200];
	filePath[0] = '\0';
	strcpy_s(filePath, "C:\\ClientDir\\");
	strcat_s(filePath, fileName);
	this->OutFileStream(filePath, 0);

	HANDLE hFile = CreateFile(filePath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 0);
	this->OutFileStream("CreateFile", (DWORD)hFile);
	while (1) {
		this->OutFileStream("file content recv()", cBytesRecv = recv(sct, recvBuf, 102400, 0));
		if (cBytesRecv == 0) {
			break;
		}
		else {
			this->OutFileStream("WriteFile", WriteFile(hFile, recvBuf, cBytesRecv, &cBytesWritten,
				NULL));
		}	
	}
	CloseHandle(hFile);
	closesocket(this->sct);
	return true;
}

bool CMyClient::RequestForChat(const char* serverIpString, int serverPort) {
	// return true if request succeeds.
	this->sct = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sain;
	sain.sin_family = AF_INET;
	sain.sin_addr.s_addr = inet_addr(serverIpString);
	sain.sin_port = htons(serverPort);
	this->OutFileStream("Chat Request connect()", 
		connect(this->sct, (SOCKADDR*)&sain, sizeof(sain)));
	this->OutFileStream("Chat request send()", send(this->sct, "2", 1, 0));
	char buf;
	this->OutFileStream("Chat request recv()", recv(this->sct, &buf, 1, 0));
	if (buf == 'd') {
		return false;
	}
	if (buf == 'a') {
		return true;
	}
}

bool CMyClient::SendChatMessage(const char* pstrMsg) {
	// when socket is closed, return false to let the caller end the iteration.
	DWORD sendRet = send(this->sct, pstrMsg, strlen(pstrMsg) + 1, 0);
	this->OutFileStream("chat message send()", sendRet);
	if (sendRet == SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool CMyClient::RecvChatMessage(char* pstrMsgToRet) {
	// if returns true, message receiving succeeds.
	// if returns false, chat has been terminated.
	// I need a 200 chars long buffer.
	int nBytesRecv = recv(this->sct, pstrMsgToRet, 200, 0);
	this->OutFileStream("chat message recv()", nBytesRecv);
	if (nBytesRecv == 0 || nBytesRecv == SOCKET_ERROR) {
		closesocket(this->sct);
		return false;
	}
	else {
		return true;
	}
}

void CMyClient::TerminateChat() {
	closesocket(this->sct);
}