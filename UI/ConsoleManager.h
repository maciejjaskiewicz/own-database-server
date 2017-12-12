#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <windows.h>
#include <cstring>
#include <conio.h>

#define CONSOLE_COLOR_BLACK 0x0
#define CONSOLE_COLOR_BLUE 0x01
#define CONSOLE_COLOR_GREEN 0x02
#define CONSOLE_COLOR_AQUA 0x03
#define CONSOLE_COLOR_RED 0x04
#define CONSOLE_COLOR_PURPLE 0x05
#define CONSOLE_COLOR_YELLOW 0x06
#define CONSOLE_COLOR_WHITE 0x07
#define CONSOLE_COLOR_GRAY 0x08

#define CONSOLE_COLOR_LIGHT_BLUE 0x09
#define CONSOLE_COLOR_LIGHT_GREEN 0x0A
#define CONSOLE_COLOR_LIGHT_AQUA 0x0B
#define CONSOLE_COLOR_LIGHT_RED 0x0C
#define CONSOLE_COLOR_LIGHT_PURPLE 0x0D
#define CONSOLE_COLOR_LIGHT_YELLOW 0x0E
#define CONSOLE_COLOR_BRIGHT_WHITE 0x0F

#define CONSOLE_COLOR_BG_BLACK 0x0
#define CONSOLE_COLOR_BG_BLUE 0x10
#define CONSOLE_COLOR_BG_GREEN 0x20
#define CONSOLE_COLOR_BG_AQUA 0x30
#define CONSOLE_COLOR_BG_RED 0x40
#define CONSOLE_COLOR_BG_PURPLE 0x50
#define CONSOLE_COLOR_BG_YELLOW 0x60
#define CONSOLE_COLOR_BG_WHITE 0x70
#define CONSOLE_COLOR_BG_GRAY 0x80

#define CONSOLE_COLOR_LIGHT_BG_BLUE 0x90
#define CONSOLE_COLOR_LIGHT_BG_GREEN 0xA0
#define CONSOLE_COLOR_LIGHT_BG_AQUA 0xB0
#define CONSOLE_COLOR_LIGHT_BG_RED 0xC0
#define CONSOLE_COLOR_LIGHT_BG_PURPLE 0xD0
#define CONSOLE_COLOR_LIGHT_BG_YELLOW 0xE0
#define CONSOLE_COLOR_BRIGHT_BG_WHITE 0xF0

using namespace std;

struct CSIZE {
    int columns;
    int rows;
};

class ConsoleManager {

private:
    COORD cord;
    HANDLE hConsoleOut;
    CONSOLE_CURSOR_INFO hCCI;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    WORD defaultConsoleColors;
    DWORD written;
public:
    ConsoleManager();
    void setCP1250();
    void setCP852();
    string PL(string str);
    void setCursor(int x, int y);
    COORD getCursorPosition();
    void hideCursor();
    void showCursor();
    void setColorAttribute(WORD color);
    void restoreDefaultColors();
    void clearConsole();
    CSIZE getConsoleSize();
};

#endif // CONSOLEMANAGER_H
