#include "MarqueeConsole.h"
#include "ConsoleManager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>

using namespace std;

MarqueeConsole::MarqueeConsole(const string& text)
    : marqueeThread(text, 0, 3, 1) {
    printHeader();
    inputLoop();
}

void MarqueeConsole::printHeader() {
    ConsoleManager::setCursorPosition(0, 0);
    cout << "*****************************************" << endl;
    cout << "* Displaying a Marquee Console! *" << endl;
    cout << "*****************************************" << endl;
}

void MarqueeConsole::inputLoop() {
    char ch;
    string input;
    int inputLine = 26;
    int curTextPos = 37;

    ConsoleManager::clearLine(inputLine);
    ConsoleManager::setCursorPosition(0, inputLine);
    cout << " Enter a command for MARQUEE_CONSOLE: ";
    ConsoleManager::setCursorPosition(curTextPos, inputLine);

    while (true) {
        // Non-blocking keyboard polling
        if (_kbhit()) {
            ch = _getch();  // Get the character pressed
            if (ch == '\r') {  // If the Enter key is pressed
                if (input == "exit") {
                    break;  // Exit the loop if the input is "exit"
                }
                ConsoleManager::clearLine(inputLine);
                ConsoleManager::setCursorPosition(0, inputLine);
                cout << " Enter a command for MARQUEE_CONSOLE: ";
                ConsoleManager::clearLine(inputLine + 1);
                ConsoleManager::setCursorPosition(0, inputLine + 1);
                cout << " Command processed in MARQUEE_CONSOLE: ";
                ConsoleManager::setCursorPosition(curTextPos + 1, inputLine + 1);
                cout << input;
                input.clear();
            }
            else if (ch == '\b') {  // If Backspace is pressed
                if (!input.empty()) {
                    input.pop_back();  // Remove the last character
                    ConsoleManager::clearLine(inputLine);
                    ConsoleManager::setCursorPosition(0, inputLine);
                    cout << " Enter a command for MARQUEE_CONSOLE: ";
                    ConsoleManager::setCursorPosition(curTextPos, inputLine);
                    cout << input;
                }
            }
            else {
                input += ch;  // Append the character to the input
                ConsoleManager::setCursorPosition(curTextPos, inputLine);
                cout << input;
            }
        }
        
        // Add a small delay to avoid excessive CPU usage
        this_thread::sleep_for(chrono::milliseconds(50));
        
    }
}


