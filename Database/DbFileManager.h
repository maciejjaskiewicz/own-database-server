#ifndef DBFILEMANAGER_H
#define DBFILEMANAGER_H

#define DB_FILE_EXTENSION ".sdb"

#include <sstream>
#include <fstream>
#include <dirent.h>
#include <algorithm>
#include <vector>
#include "Table.h"
#include "Database.h"

#include "../Utils/StringOperations.h"

using namespace std;

class DbFileManager {
public:
    DbFileManager();
    void saveDbToFiles(Database db);
    void loadDbFromFiles(Database *db);

    string getStructString(Table tab);
    string getRecordsString(Table tab);
    string getTableStringFormFile(string fileName);
    string getFileName(Table tab);

    void fillTableByRecords(string recordsStr, Table *tab);
    TableStruct getTableStructFromStr(string structSeg);
private:
    vector<string> dbFiles;
    fstream file;
    char key[5] = {'C','B','F','3','6'};


    void saveTable(Table tab);
    void scanDirectory();
    bool fileHasExtension(const string &s, const string &suffix);
    bool fileExist(string name);
};

#endif // DBFILEMANAGER_H
