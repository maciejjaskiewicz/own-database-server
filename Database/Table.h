#ifndef TABLE_H
#define TABLE_H

#include <vector>
using namespace std;

struct TableStruct {
    vector<string> types;
    vector<string> columns;
};

struct TableRecord {
    TableStruct table;
    vector<string> fields;
};

class Table {

private:
    string name;
    TableStruct tableStruct;
    vector<TableRecord> tableRecords;

public:
    Table(string _name, TableStruct _tableStruct);
    void addRecordToTable(TableRecord record);
    void removeRecodFromTable(int index);
    int getNumberOfRecords();
    TableStruct getStruct();
    TableRecord getRecord(int index);
    string getName();
};

#endif // TABLE_H
