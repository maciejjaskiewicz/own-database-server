#include "PacketParser.h"

string PacketParser::ParseDbToTableNamesString(Database *db) {
    stringstream tableNamesString;
    tableNamesString<<"{";
    for(int i=0; i<db->getNumberOfTables(); i++) {
        tableNamesString<<db->getTable(i).getName();
        if(i != db->getNumberOfTables()-1) tableNamesString<<",";
    }
    tableNamesString<<"}";

    return tableNamesString.str();
}

string PacketParser::ParseTableToTableStringByName(Database *db, string name) {
    stringstream tableString;
    int tabId = db->getIndexOfName(name);
    if(tabId != -1) {
        tableString<<dbm.getStructString(db->getTable(tabId))<<" "<<dbm.getRecordsString(db->getTable(tabId));
    }

    return tableString.str();
}

Table PacketParser::GetTableFromTableString(string tableStr) {

    vector<string> segList, structSeg, tabColumns;
    string segment, tableLabel;
    TableStruct tabStruct;

    segList = STR_OPERATIONS::split(tableStr, ' ');

    segment = segList[0];
    STR_OPERATIONS::removeFirstAndLastChar(segment);
    tableLabel = segment.substr(0, segment.find('{'));
    segment.erase(0, segment.find('{'));

    tabStruct = dbm.getTableStructFromStr(segment);
    Table tab(tableLabel, tabStruct);

    return tab;
}

TableRecord PacketParser::getRecordFormRecordString(string recordStr, string &tableName) {
    TableRecord record;
    STR_OPERATIONS::removeFirstAndLastChar(recordStr);
    vector<string> segList;
    segList = STR_OPERATIONS::split(recordStr, ',');
    tableName = segList[0];
    for(int i=1; i<segList.size(); i++) {
        record.fields.push_back(segList[i]);
    }

    return record;
}
