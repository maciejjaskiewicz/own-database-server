#include "Server.h"

Server::Server(int PORT, bool broadcastPublically)
{
    log.streamLog(ostringstream().flush()<<"Loading database from files", LOG_TYPE_INFO);

    dbm.loadDbFromFiles(&db);
    stringstream loadedTables;
    for(int i=0; i<db.getNumberOfTables(); i++) {
        loadedTables<<db.getTable(i).getName();
        if(i != db.getNumberOfTables()-1) loadedTables<<", ";
    }
    log.streamLog(ostringstream().flush()<<"Loaded tables: "<<console.PL(loadedTables.str()), LOG_TYPE_SUCCESS);

    log.streamLog(ostringstream().flush()<<"Startup WinSock", LOG_TYPE_INFO);
	WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if(WSAStartup(DLLVersion, &wsaData) != 0) {
        log.streamLog(ostringstream().flush()<<"WinSock startup failed", LOG_TYPE_ERROR);
        exit(1);
    }
    if (broadcastPublically)
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    else
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT); // Port
    addr.sin_family = AF_INET; // IPv4

    sListen = socket(AF_INET, SOCK_STREAM, NULL);
    if (bind(sListen, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        log.streamLog(ostringstream().flush()<<"Failed to bind the address to our listening socket. Winsock Error: "
                                             <<WSAGetLastError(), LOG_TYPE_ERROR);
		exit(1);
    }
    if (listen(sListen, SOMAXCONN) == SOCKET_ERROR) {
        log.streamLog(ostringstream().flush()<<"Failed to listen on listening socket. Winsock Error:"
                                             <<WSAGetLastError(), LOG_TYPE_ERROR);
		exit(1);
    }
    log.streamLog(ostringstream().flush()<<"Listen started at port: "<<PORT, LOG_TYPE_INFO);
    serverPtr = this;
}

bool Server::ListenForNewConnection() {
    SOCKET newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen);
    if (newConnection == 0) {
        log.streamLog(ostringstream().flush()<<"Failed to accept the client's connection", LOG_TYPE_WARNING);
		return false;
    } else {
        log.streamLog(ostringstream().flush()<<"New client connected! ID: "<<totalConnections<<", IP: "
                                             <<inet_ntoa(addr.sin_addr), LOG_TYPE_SUCCESS);
		connections[totalConnections].socket = newConnection;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(totalConnections), NULL, NULL);
		totalConnections += 1;
		return true;
    }
}

bool Server::ProcessPacket(int ID, Packet _packetType) {
    switch(_packetType) {
    case P_ConsoleMessage: {
        string message;
        if(!GetString(ID, message))
            return false;

        log.streamLog(ostringstream().flush()<<"[User message ID: "<<ID<<"] "<<message, LOG_TYPE_WARNING);
        break;
    }
	case P_TableRequestTableNamesString: {
        string dbName;
        if(!GetString(ID, dbName))
            return false;
        string tableNames = console.PL(parser.ParseDbToTableNamesString(&db));

        if (!SendString(ID, tableNames, P_TableTableNamesString))
            return false;
        break;
	}
	case P_TableRequestTableString: {
        string tableName;
        if(!GetString(ID, tableName))
            return false;
        string tableString = console.PL(parser.ParseTableToTableStringByName(&db, tableName));
        log.streamLog(ostringstream().flush()<<"User ID: "<<ID<<" requested table: "<<tableName, LOG_TYPE_INFO);
        if (!SendString(ID, tableString, P_TableTableString))
            return false;
        break;
	}
	case P_TableRequestAddNewTable: {
	    string newTableStr;
        if(!GetString(ID, newTableStr))
            return false;

        Table tab = parser.GetTableFromTableString(newTableStr);
        log.streamLog(ostringstream().flush()<<"User ID: "<<ID<<" added new table: "<<tab.getName()<<" to database", LOG_TYPE_INFO);
        db.addTable(tab);
        dbm.saveDbToFiles(db);
        break;
	}
	case P_TableRequestRemoveTable: {
        string tableNameToRemove;
        if(!GetString(ID, tableNameToRemove))
            return false;

        log.streamLog(ostringstream().flush()<<"User ID: "<<ID<<" removed table: "<<tableNameToRemove<<" from database", LOG_TYPE_INFO);

        db.removeTable(db.getIndexOfName(tableNameToRemove));
        dbm.saveDbToFiles(db);
        break;
	}
	case P_TableRequestAddNewRecordFormTable: {
        string newRecordStr;
        if(!GetString(ID, newRecordStr))
            return false;

        string tableName;
        TableRecord record = parser.getRecordFormRecordString(newRecordStr, tableName);
        record.table = db.getTable(db.getIndexOfName(tableName)).getStruct();

        log.streamLog(ostringstream().flush()<<"User ID: "<<ID<<" added new record to table: "<<tableName, LOG_TYPE_INFO);

        db.addRecordToTable(db.getIndexOfName(tableName), record);
        dbm.saveDbToFiles(db);
        break;
	}
	case P_TableRequestRemoveRecordFormTable: {
        string removeRecordStr;
        if(!GetString(ID, removeRecordStr))
            return false;

        STR_OPERATIONS::removeFirstAndLastChar(removeRecordStr);
        vector<string> splitSeg = STR_OPERATIONS::split(removeRecordStr, ',');

        log.streamLog(ostringstream().flush()<<"User ID: "<<ID<<" removed record from table: "<<splitSeg[0], LOG_TYPE_INFO);

        db.removeRecordFromTable(db.getIndexOfName(splitSeg[0]), atoi(splitSeg[1].c_str()));
        dbm.saveDbToFiles(db);
        break;
	}
    default:
        log.streamLog(ostringstream().flush()<<"Unrecognized packet "<<_packetType<<" form client ID: "<<ID, LOG_TYPE_WARNING);
        break;
    }

    return true;
}

void Server::ClientHandlerThread(int ID) {
    Packet packetType;
    while (true) {
		if (!serverPtr->GetPacketType(ID, packetType))
			break;
		if (!serverPtr->ProcessPacket(ID, packetType))
			break;
	}
	serverPtr->log.streamLog(ostringstream().flush()<<"Lost connection to client ID: "<<ID, LOG_TYPE_WARNING);
	closesocket(serverPtr->connections[ID].socket);
	return;
}

bool Server::SendAll(int ID, char * data, int totalBytes)
{
	int bytesSent = 0;
	while (bytesSent < totalBytes) {
		int retCheck = send(connections[ID].socket, data + bytesSent, totalBytes - bytesSent, NULL);
		if (retCheck == SOCKET_ERROR)
			return false;
		bytesSent += retCheck;
	}
	return true;
}

bool Server::RecvAll(int ID, char * data, int totalBytes)
{
	int bytesReceived = 0;
	while (bytesReceived < totalBytes) {
		int retCheck = recv(connections[ID].socket, data + bytesReceived, totalBytes - bytesReceived, NULL);
		if (retCheck == SOCKET_ERROR)
			return false;
		bytesReceived += retCheck;
	}
	return true;
}

bool Server::SendInt(int ID, int32_t _int) {
    _int = htonl(_int); // Host Byte Order to Network Byte Order
    if (!SendAll(ID, (char*)&_int, sizeof(int32_t)))
		return false;
	return true;
}

bool Server::GetInt(int ID, int32_t &_int) {
    if (!RecvAll(ID, (char*)&_int, sizeof(int32_t)))
		return false;
    _int = ntohl(_int);
	return true;
}

bool Server::SendPacketType(int ID, Packet _packetType) {
    if (!SendInt(ID, _packetType))
        return false;
    return true;
}

bool Server::GetPacketType(int ID, Packet &_packetType) {
    int packetType;
    if (!GetInt(ID, packetType))
        return false;
    _packetType = (Packet)packetType;
    return true;
}

bool Server::SendString(int ID, string &_string, Packet _packetType) {
    if(!SendPacketType(ID, _packetType))
        return false;

    int bufferLength = _string.size();
    if(!SendInt(ID, bufferLength))
        return false;

    if (!SendAll(ID, (char*)_string.c_str(), bufferLength))
        return false;

    return true;
}

bool Server::GetString(int ID, string &_string) {
    int bufferLength;
    if(!GetInt(ID, bufferLength))
        return false;

    char *buffer = new char[bufferLength+1];
    buffer[bufferLength] = '\0';

    if (!RecvAll(ID, buffer, bufferLength)) {
		delete[] buffer;
		return false;
	}
	_string = buffer;
	delete[] buffer;
	return true;
}
