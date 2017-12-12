#include <iostream>
#include "DbFileManager.h"

using namespace std;

DbFileManager::DbFileManager() {
    scanDirectory();
}

void DbFileManager::loadDbFromFiles(Database *db) {
    for(int i=0; i<dbFiles.size(); i++) {
        vector<string> segList, structSeg, tabColumns;
        string segment, tableLabel;
        TableStruct tabStruct;

        segList = STR_OPERATIONS::split(getTableStringFormFile(dbFiles[i]), ' ');

        segment = segList[0];
        STR_OPERATIONS::removeFirstAndLastChar(segment);
        tableLabel = segment.substr(0, segment.find('{'));
        segment.erase(0, segment.find('{'));

        tabStruct = getTableStructFromStr(segment);

        Table tab(tableLabel, tabStruct);

        if(segList.size() == 2) {
            segment = segList[1];
            STR_OPERATIONS::removeFirstAndLastChar(segment);

            fillTableByRecords(segment, &tab);
        }
        db->addTable(tab);
    }
}

void DbFileManager::saveDbToFiles(Database db) {
    for(int i=0; i<db.getNumberOfTables(); i++) {
        Table tab = db.getTable(i);
        saveTable(tab);
    }

    for(int i=0; i<dbFiles.size(); i++) {
        bool deleteTableFile = true;

        for(int j=0; j<db.getNumberOfTables(); j++) {
            if(dbFiles[i] == getFileName(db.getTable(j)))
                deleteTableFile = false;
        }
        if(deleteTableFile)
            remove(dbFiles[i].c_str());
    }
}

TableStruct DbFileManager::getTableStructFromStr(string structStr) {
    vector<string> structSeg;
    string segment;
    TableStruct tabStruct;

    structSeg = STR_OPERATIONS::split(structStr, ':');

    segment = structSeg[0];
    STR_OPERATIONS::removeFirstAndLastChar(segment);
    tabStruct.columns = STR_OPERATIONS::split(segment, ',');

    segment = structSeg[1];
    STR_OPERATIONS::removeFirstAndLastChar(segment);
    tabStruct.types = STR_OPERATIONS::split(segment, ',');

    return tabStruct;
}

void DbFileManager::fillTableByRecords(string recordsStr, Table *tab) {
    string segment;
    vector<string> recordSeg;
    recordSeg = STR_OPERATIONS::split(recordsStr, ':');

    for(int i=0; i<recordSeg.size(); i++) {
        TableRecord tabRecord;
        tabRecord.table = tab->getStruct();
        vector<string> fields;

        segment = recordSeg[i];
        STR_OPERATIONS::removeFirstAndLastChar(segment);

        tabRecord.fields = STR_OPERATIONS::split(segment, ',');
        tab->addRecordToTable(tabRecord);
    }
}

void DbFileManager::saveTable(Table tab) {
    stringstream fileString;
    fileString<<getStructString(tab)<<" "<<getRecordsString(tab);
    string fileName = getFileName(tab);

    if(fileExist(tab.getName())) {
        file.open(fileName.c_str(), ios::out | ios::trunc);
        file.close();
    }

    file.open(fileName.c_str(), ios::out | ios::binary);

    if(file.is_open()) {
        file<<STR_OPERATIONS::XOR(fileString.str(), key, sizeof(key));
        file.close();
    }
}

string DbFileManager::getTableStringFormFile(string fileName) {
    stringstream fileString;

    file.open(fileName.c_str(), ios::in | ios::binary);

    if(file.is_open()) {
        fileString<<file.rdbuf();
        file.close();
    }

    return STR_OPERATIONS::XOR(fileString.str(), key, sizeof(key));
}

string DbFileManager::getFileName(Table tab) {
    stringstream fileName;
    fileName<<tab.getName()<<DB_FILE_EXTENSION;

    return fileName.str();
}

string DbFileManager::getStructString(Table tab) {
    stringstream ss;
    ss<<"["<<tab.getName()<<"{";

    for(int j=0; j<tab.getStruct().columns.size(); j++) {
        ss<<tab.getStruct().columns[j];
        if(j != tab.getStruct().columns.size()-1) ss<<",";
    }
    ss<<"}:{";

    for(int j=0; j<tab.getStruct().types.size(); j++) {
        ss<<tab.getStruct().types[j];
        if(j != tab.getStruct().types.size()-1) ss<<",";
    }
    ss<<"}]";

    return ss.str();
}

string DbFileManager::getRecordsString(Table tab) {
    stringstream ss;
    ss<<"[";

    for(int i=0; i<tab.getNumberOfRecords(); i++) {
        ss<<"{";
        for(int j=0; j<tab.getRecord(i).fields.size(); j++) {
            ss<<tab.getRecord(i).fields[j];
            if(j != tab.getRecord(i).fields.size()-1) ss<<",";
        }
        ss<<"}";
        if(i != tab.getNumberOfRecords()-1) ss<<":";
    }
    ss<<"]";

    return ss.str();
}

void DbFileManager::scanDirectory() {
    dbFiles.clear();

    DIR *dir = opendir(".");
    if(dir) {
        dirent *entry;
        while((entry = readdir(dir))!=NULL)
        {
            if(fileHasExtension(entry->d_name, DB_FILE_EXTENSION))
                dbFiles.push_back(entry->d_name);
        }
    }
}

bool DbFileManager::fileHasExtension(const string& s, const string& suffix) {
    return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());
}

bool DbFileManager::fileExist(string name) {
    scanDirectory();
    name+=DB_FILE_EXTENSION;

    for(int i=0; i<dbFiles.size(); i++) {
        if(dbFiles[i] == name) return true;
    }

    return false;
}
