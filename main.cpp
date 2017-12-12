#include <iostream>
#include "Networking/Server.h"

/// SERWER

using namespace std;

int main()
{
	Server MyServer(1121);
	while(true)
		MyServer.ListenForNewConnection();

	system("pause");
	return 0;
}
