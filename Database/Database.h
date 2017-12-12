#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "Table.h"

#include "../Utils/StringOperations.h"

using namespace std;

class Database {

    private:
    vector<Table> Tables;

    public:
    void addTable(Table table);
    void removeTable(int index);
    Table getTable(int index);
    int getNumberOfTables();
    int getIndexOfName(string name);
    void addRecordToTable(int tabIndex, TableRecord tabRecord);
    void removeRecordFromTable(int tabIndex, int recordIndex);
    void createExampleTables();
};

#endif // DATABASE_H
