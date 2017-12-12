#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class STR_OPERATIONS{
public:
    static vector<string> split(string str, char delim);
    static void removeFirstAndLastChar(string &str);
    static string XOR(string data, char *key, size_t keySize);
    static string fillSpaces(string str, int how_much);
    static bool is_number(const string &s);
    static string PL(string str);
};


#endif // STRINGOPERATIONS_H
