#include "ConsoleManager.h"
#include <iostream>

using namespace std;

void ConsoleManager::setCursorPosition(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

COORD ConsoleManager::getConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD size = { csbi.srWindow.Right - csbi.srWindow.Left + 1,
                   csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
    return size;
}

bool ConsoleManager::isInBounds(int x, int y) {
    COORD size = getConsoleSize();
    return (x >= 0 && x < size.X && y >= 0 && y < size.Y);
}

void ConsoleManager::clearLine(int y) {
    COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(console, &csbi);
    coord.X = 0;
    coord.Y = y;
    FillConsoleOutputCharacter(console, ' ', csbi.dwSize.X, coord, &written);
    SetConsoleCursorPosition(console, coord);
}


