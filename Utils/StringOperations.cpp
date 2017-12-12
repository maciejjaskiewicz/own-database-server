#include "StringOperations.h"

vector<string> STR_OPERATIONS::split(string str, char delim) {
    stringstream ss(str);
    vector<string> segList;
    string segment;

    while(getline(ss, segment, delim))
        segList.push_back(segment);

    return segList;
}

void STR_OPERATIONS::removeFirstAndLastChar(string &str) {
    str.erase(0, 1);
    str.erase(str.size()-1, 1);
}

string STR_OPERATIONS::XOR(string data, char *key, size_t keySize) {
    string xorString = data;

    for(int i=0; i<xorString.size(); i++) {
        xorString[i] = data[i] ^ key[i % (keySize / sizeof(char))];
    }
    return xorString;
}

string STR_OPERATIONS::PL(string str) {
    char plChars[18] = {'¹', 'æ', 'ê', '³', 'ñ', 'ó', 'œ', 'Ÿ', '¿',
                        '¹', 'Æ', 'Ê', '£', 'Ñ', 'Ó', 'Œ', '', '¯'};

    int ASCIIequivalent[18] = {165, 134, 169, 136, 228, 162, 152, 171, 190,
                           164, 143, 168, 157, 227, 224, 151, 141, 189};

    for(int i=0; i<str.size(); i++) {
        for(int j=0; j<18; j++) {
            if(str[i] == plChars[j]) str[i] = static_cast<char>(ASCIIequivalent[j]);
        }
    }
    return str;
}

string STR_OPERATIONS::fillSpaces(string str, int how_much) {
    stringstream ss;

    for(int i=str.length(); i<=how_much; i++) {
        ss<<" ";
    }

    return ss.str();
}

bool STR_OPERATIONS::is_number(const string &s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
