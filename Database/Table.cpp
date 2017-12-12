#include <iostream>
#include "Table.h"

using namespace std;

Table::Table(string _name, TableStruct _tableStruct) {
    name = _name;
    tableStruct = _tableStruct;
}

void Table::addRecordToTable(TableRecord record) {
    tableRecords.push_back(record);
}

void Table::removeRecodFromTable(int index) {
    tableRecords.erase(tableRecords.begin() + index);
}

TableStruct Table::getStruct() {
    return tableStruct;
}

TableRecord Table::getRecord(int index) {
    return tableRecords[index];
}

int Table::getNumberOfRecords() {
    return tableRecords.size();
}

string Table::getName() {
    return name;
}


