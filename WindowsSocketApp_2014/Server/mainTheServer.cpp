#include "..\CommonFiles\MyServer.h"
#include "..\CommonFiles\MyServer.cpp"
#include <iostream>

int main() {
	char nativeIP[20];
	int nativePort;
	std::cout << "Input native IP and port:\n";
	std::cin >> nativeIP >> nativePort;

	CMyServer server(nativeIP, nativePort, true);
	server.BeginAcceptances();
	std::cout << "The server has started. To exit, input something.";
	std::cin >> nativeIP;

	server.EndAcceptances();
	return 0;
}