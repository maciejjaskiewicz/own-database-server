#include <iostream>
#include "Database.h"

using namespace std;

void Database::addTable(Table table) {
    Tables.push_back(table);
}

void Database::removeTable(int index) {
    Tables.erase(Tables.begin()+index);
}

Table Database::getTable(int index) {
    return Tables[index];
}

int Database::getNumberOfTables() {
    return Tables.size();
}

int Database::getIndexOfName(string name) {
    for(int i=0; i<Tables.size(); i++) {
        if(STR_OPERATIONS::PL(Tables[i].getName()) == STR_OPERATIONS::PL(name))
            return i;
    }
    return -1;
}

void Database::addRecordToTable(int tabIndex, TableRecord tabRecord) {
    Tables[tabIndex].addRecordToTable(tabRecord);
}

void Database::removeRecordFromTable(int tabIndex, int recordIndex) {
    Tables[tabIndex].removeRecodFromTable(recordIndex);
}

void Database::createExampleTables() {

    TableStruct exampleTableStruct;

    exampleTableStruct.types.push_back("int"); exampleTableStruct.types.push_back("string");
    exampleTableStruct.types.push_back("string"); exampleTableStruct.types.push_back("string");
    exampleTableStruct.types.push_back("char"); exampleTableStruct.types.push_back("string");

    exampleTableStruct.columns.push_back("Id"); exampleTableStruct.columns.push_back("Imie");
    exampleTableStruct.columns.push_back("Nazwisko"); exampleTableStruct.columns.push_back("Pesel");
    exampleTableStruct.columns.push_back("P³eæ"); exampleTableStruct.columns.push_back("Data_urodzenia");

    Table tab1("Przyk³adowa_tabela", exampleTableStruct);

    vector<string> fields;
    fields.push_back("1"); fields.push_back("Jan"); fields.push_back("Kowalski");
    fields.push_back("82041178912"); fields.push_back("M"); fields.push_back("11-04-1982");

    TableRecord record = {exampleTableStruct, fields};
    tab1.addRecordToTable(record);
    fields.clear();

    fields.push_back("2"); fields.push_back("Robert"); fields.push_back("Nowak");
    fields.push_back("91210383021"); fields.push_back("M"); fields.push_back("03-21-1991");

    TableRecord record1 = {exampleTableStruct, fields};
    tab1.addRecordToTable(record1);
    fields.clear();

    fields.push_back("3"); fields.push_back("Ma³gorzata"); fields.push_back("Kamiñska");
    fields.push_back("73130683021"); fields.push_back("K"); fields.push_back("06-13-1973");

    TableRecord record2 = {exampleTableStruct, fields};
    tab1.addRecordToTable(record2);
    fields.clear();

    addTable(tab1);

    TableStruct exampleTableStruc1;

    exampleTableStruc1.types.push_back("int"); exampleTableStruc1.types.push_back("string");
    exampleTableStruc1.types.push_back("string"); exampleTableStruc1.types.push_back("string");

    exampleTableStruc1.columns.push_back("Id"); exampleTableStruc1.columns.push_back("Imie");
    exampleTableStruc1.columns.push_back("Nazwisko"); exampleTableStruc1.columns.push_back("Pesel");

    Table tab2("Przyk³adowa_tabela2", exampleTableStruc1);
    fields.push_back("1"); fields.push_back("Jan"); fields.push_back("Kowalski");
    fields.push_back("82041178912");

    TableRecord record3 = {exampleTableStruc1, fields};
    tab2.addRecordToTable(record3);
    fields.clear();

    addTable(tab2);
}
