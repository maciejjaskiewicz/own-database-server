#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <string>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <iostream>

#include "../Database/Database.h"
#include "../Database/Table.h"
#include "../Database/DbFileManager.h"

#include "../UI/ConsoleManager.h"
#include "../UI/LogManager.h"

#include "PacketParser.h"

/// SERWER

using namespace std;

enum Packet {
    P_ConsoleMessage,
	P_TableRequestTableNamesString,
	P_TableTableNamesString,
	P_TableRequestTableString,
	P_TableTableString,
	P_TableRequestAddNewTable,
	P_TableRequestRemoveTable,
	P_TableRequestAddNewRecordFormTable,
	P_TableRequestRemoveRecordFormTable
};

struct Connection
{
	SOCKET socket;
};

class Server {
public:
    Server(int PORT, bool broadcastPublically = false);
	bool ListenForNewConnection();
private:
    bool SendAll(int ID, char *data, int totalBytes);
	bool RecvAll(int ID, char *data, int totalBytes);

	bool SendInt(int ID, int32_t _int);
	bool GetInt(int ID, int32_t &_int);

	bool SendPacketType(int ID, Packet _packetType);
	bool GetPacketType(int ID, Packet &_packetType);

	bool SendString(int ID, std::string &_string, Packet _packetType = P_ConsoleMessage);
	bool GetString(int ID, std::string &_string);

	bool ProcessPacket(int ID, Packet _packetType);

	static void ClientHandlerThread(int ID);

private:
    Connection connections[100];
	int totalConnections = 0;

    Database db;
    PacketParser parser;
    DbFileManager dbm;
	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	SOCKET sListen;
	ConsoleManager console;
	LogManager log;
};

static Server * serverPtr;

#endif // SERVER_H
