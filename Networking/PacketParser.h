#ifndef PACKETPARSER_H
#define PACKETPARSER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "../Database/Database.h"
#include "../Database/Table.h"
#include "../Database/DbFileManager.h"
#include "../Utils/StringOperations.h"

using namespace std;

class PacketParser {
public:
    string ParseDbToTableNamesString(Database *db);
    string ParseTableToTableStringByName(Database *db, string name);
    Table GetTableFromTableString(string tableStr);
    TableRecord getRecordFormRecordString(string recordStr, string &tableName);

private:
    DbFileManager dbm;
};


#endif // PACKETPARSER_H
