#include "..\CommonFiles\MyClient.h"
#include "..\CommonFiles\MyClient.cpp"
#include <iostream>

int main() {
	CMyClient client(true);

	std::cout << "To connect to server, input the server's IP and port:\n";
	char serverIP[20];
	int serverPort;
	std::cin >> serverIP >> serverPort;

	int selection;
	while (1) {
		std::cout << "Input 0 ---> exit; 1 ---> test Ping; 2 ---> file transport:\n";
		std::cin >> selection;

		char nonsense;
		std::cin.get(nonsense);

		if (selection == 0) {
			break;
		}
		else if (selection == 1) {
			std::cout << "Ping in ms: " << client.RequestForPing(serverIP, serverPort) << '\n';
		}
		else if (selection == 2) {
			std::cout << "You should create a directory C:\\ClientDir\n";
			std::cout << "The list of files at the server's C:\\ServerDir:\n\n";
			int nFileListLen;
			char* pstrFileList = client.RequestForFileList(serverIP, serverPort, &nFileListLen);
			std::cout << (pstrFileList + 7);
			delete pstrFileList;
			std::cout << std::endl;
			std::cout << "Input the name of file you select above:\n";
			char fileName[100];
			std::cin >> fileName;
			client.RequestForFileTransport(fileName, true);
			std::cout << "If the file transport has succeeded, it should have been there.\n";
		}
	}
	return 0;
}