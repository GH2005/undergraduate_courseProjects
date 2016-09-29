#include "..\CommonFiles\MyClient.h"
#include "..\CommonFiles\MyClient.cpp"
#include "..\CommonFiles\MyServer.h"
#include "..\CommonFiles\MyServer.cpp"
#include <iostream>
#include <string>

DWORD WINAPI ServerChatRecvThreadFunc(PVOID pInServer) {
	CMyServer* pServer = (CMyServer*)pInServer;
	char recvBuffer[200];
	while (pServer->RecvChatMessage(recvBuffer)) {
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		std::cout << "--->" << st.wHour << ':' << st.wMinute << ':' << st.wSecond << ' ';
		std::cout << recvBuffer << std::endl;
		memset(recvBuffer, '\0', 200);
	}
	return 0;
}

DWORD WINAPI ClientChatRecvThreadFunc(PVOID clientObj) {
	CMyClient* pClient = (CMyClient*)clientObj;
	char recvBuffer[200];
	while (pClient->RecvChatMessage(recvBuffer)) {
		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		std::cout << "--->" << st.wHour << ':' << st.wMinute << ':' << st.wSecond << ' ';
		std::cout << recvBuffer << std::endl;
		memset(recvBuffer, '\0', 200);
	}
	return 0;
}

int main() {
	char nativeIP[20];
	int nativePort;
	std::cout << "Input native IP and port:\n";
	std::cin >> nativeIP >> nativePort;

	CMyServer server(nativeIP, nativePort, true);
	server.BeginAcceptances();

	int selection;
	while (1) {
		std::cout << "Input 0 ---> exit; 1 ---> chat; 2 ---> wait for connection:\n";
		std::cin >> selection;

		char nonsense;
		std::cin.get(nonsense);

		if (selection == 0) {
			break;
		}
		else if (selection == 1) {
			std::cout << "To talk with another peer, input its IP and port:\n";
			char targetIP[20];
			int targetPort;
			std::cin >> targetIP >> targetPort;
			std::cin.get(nonsense);

			CMyClient client(false);
			if (!client.RequestForChat(targetIP, targetPort)) {
				std::cout << "Request denied. Maybe the target is busy chatting.\n";
			}
			else {
				std::cout << "Request accepted. Begin chatting now:\n";
				server.bInChatAsClient = true;
				chBEGINTHREADEX(NULL, 0, ::ClientChatRecvThreadFunc, &client, 0, NULL);
				char chatSendBuffer[200];
				do {
					memset(chatSendBuffer, '\0', 200);
					std::cin.getline(chatSendBuffer, 200);
					if (std::string(chatSendBuffer) == "_ENDTHETALK") {
						client.TerminateChat();
					}
				} while (client.SendChatMessage(chatSendBuffer));
				server.bInChatAsClient = false;
				std::cout << "The chat has come to an end.\n";
			}
		}
		else if (selection == 2) {
			std::cout << "Ready for connection.\n";
			while (1) {
				if (server.bInChatAsServer) {
					std::cout << "Another peer has connected here. Begin chatting now.\n";
					chBEGINTHREADEX(NULL, 0, ::ServerChatRecvThreadFunc, &server, 0, NULL);

					char chatSendBuffer[200];
					do {
						memset(chatSendBuffer, '\0', 200);
						std::cin.getline(chatSendBuffer, 200);
						if (std::string(chatSendBuffer) == "_ENDTHETALK") {
							server.TerminateChat();
						}
					} while (server.SendChatMessage(chatSendBuffer));
					std::cout << "The chat has come to an end.\n";
					break;
				}
				Sleep(1000);
			}
		}
	}

	server.EndAcceptances();
	return 0;
}