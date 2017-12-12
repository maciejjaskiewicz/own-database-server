#include <iostream>
#include "ConsoleManager.h"

using namespace std;

ConsoleManager::ConsoleManager() {
    cord.X = 0; cord.Y = 0;
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

    defaultConsoleColors = csbiInfo.wAttributes;
}

void ConsoleManager::setCP1250() {
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
    setlocale(LC_ALL, "1250");
}

void ConsoleManager::setCP852() {
    SetConsoleCP(852);
    SetConsoleOutputCP(852);
    setlocale(LC_ALL, "852");
}

string ConsoleManager::PL(string str) {
    char plChars[18] = {'π', 'Ê', 'Í', '≥', 'Ò', 'Û', 'ú', 'ü', 'ø',
                        'π', '∆', ' ', '£', '—', '”', 'å', 'è', 'Ø'};

    int ASCIIequivalent[18] = {165, 134, 169, 136, 228, 162, 152, 171, 190,
                           164, 143, 168, 157, 227, 224, 151, 141, 189};

    for(int i=0; i<str.size(); i++) {
        for(int j=0; j<18; j++) {
            if(str[i] == plChars[j]) str[i] = static_cast<char>(ASCIIequivalent[j]);
        }
    }
    return str;
}


void ConsoleManager::setCursor(int x, int y) {
    cord.X = x; cord.Y = y;
    SetConsoleCursorPosition(hConsoleOut, cord);
}

COORD ConsoleManager::getCursorPosition() {
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
    COORD coord = {csbiInfo.dwCursorPosition.X, csbiInfo.dwCursorPosition.Y};
    return coord;
}

void ConsoleManager::hideCursor() {
    GetConsoleCursorInfo(hConsoleOut,&hCCI);
    if(hCCI.bVisible != FALSE) {
        hCCI.bVisible = FALSE;
        SetConsoleCursorInfo(hConsoleOut,&hCCI);
    }
}

void ConsoleManager::showCursor() {
    GetConsoleCursorInfo(hConsoleOut,&hCCI);
    if(hCCI.bVisible != TRUE) {
        hCCI.bVisible = TRUE;
        SetConsoleCursorInfo(hConsoleOut,&hCCI);
    }
}

void ConsoleManager::setColorAttribute(WORD color) {
    SetConsoleTextAttribute(hConsoleOut, color);
}

void ConsoleManager::restoreDefaultColors() {
    SetConsoleTextAttribute(hConsoleOut, defaultConsoleColors);
}

void ConsoleManager::clearConsole() {
    cord.X = 0; cord.Y = 0;
    while(kbhit()) getch();

    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

    restoreDefaultColors();

    FillConsoleOutputCharacterA(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, cord, &written);
    FillConsoleOutputAttribute(hConsoleOut, defaultConsoleColors, csbiInfo.dwSize.X * csbiInfo.dwSize.Y, cord, &written);
    SetConsoleCursorPosition(hConsoleOut, cord);
}

CSIZE ConsoleManager::getConsoleSize() {
    CSIZE csize;
    csize.columns = csbiInfo.srWindow.Right - csbiInfo.srWindow.Left + 1;
    csize.rows = csbiInfo.srWindow.Bottom - csbiInfo.srWindow.Top + 1;

    return csize;
}

