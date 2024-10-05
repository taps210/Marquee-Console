#include <windows.h>

class ConsoleManager {
public:
    static void setCursorPosition(int x, int y);
    static COORD getConsoleSize();
    static bool isInBounds(int x, int y);
    static void clearLine(int y);
};



