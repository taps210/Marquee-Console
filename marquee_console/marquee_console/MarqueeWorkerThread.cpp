#include "MarqueeWorkerThread.h"
#include "ConsoleManager.h"
#include <iostream>
#include <thread>
#include <windows.h>

using namespace std;

MarqueeWorkerThread::MarqueeWorkerThread(const string& text, int startX, int startY, int delayMs)
    : marqueeText(text), x(startX), y(startY), delay(delayMs), dx(1), dy(1) {
    threadRunning = true;
    marqueeThread = thread(&MarqueeWorkerThread::run, this);
}

MarqueeWorkerThread::~MarqueeWorkerThread() {
    stop();
}

void MarqueeWorkerThread::stop() {
    threadRunning = false;
    if (marqueeThread.joinable()) {
        marqueeThread.join();
    }
}

void MarqueeWorkerThread::updateText(const std::string& newText) {
    // Lock to prevent concurrent text updates
    std::lock_guard<std::mutex> lock(textMutex); 
    marqueeText = newText;
}

void MarqueeWorkerThread::run() {
    COORD consoleSize = ConsoleManager::getConsoleSize();
    int inputFieldY = consoleSize.Y - 5; // Barrier is the input field
    int headerFieldY = 4;                // Adjust this value as needed
    COORD coordScreen = { 0, 0 };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    while (threadRunning) {
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
        DWORD cCharsWritten;
        COORD consoleSize = ConsoleManager::getConsoleSize();

        // Clear the output area before each frame
        for (int row = headerFieldY; row <= inputFieldY; ++row) {
            coordScreen = { static_cast<SHORT>(0), static_cast<SHORT>(row) };
            FillConsoleOutputCharacter(hConsole, ' ', consoleSize.X + 1, coordScreen, &cCharsWritten);
        }

        // Update position for diagonal movement
        x += dx;
        y += dy;

        // Horizontal bouncing logic (ensure it stays within the console width)
        if (x < 0) {
            x = 0;
            dx = -dx;  // Reverse horizontal direction
        }
        else if ((x + marqueeText.length()) >= consoleSize.X) {
            x = consoleSize.X - marqueeText.length();
            dx = -dx;  // Reverse horizontal direction
        }

        // Vertical bouncing logic (ensure it stays between header and input field)
        if (y <= headerFieldY) {
            y = headerFieldY;
            dy = -dy;  // Reverse vertical direction
        }
        else if (y >= inputFieldY) {
            y = inputFieldY - 1;  // Keep it above the input field
            dy = -dy;  // Reverse vertical direction
        }

        // Print the marquee text at the new position
        ConsoleManager::setCursorPosition(x, y);
        lock_guard<mutex> lock(textMutex); // Ensure thread-safe access to text
        WriteConsoleA(hConsole, marqueeText.c_str(), static_cast<DWORD>(marqueeText.length()), &cCharsWritten, NULL);

        // Wait for the delay between frames
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}



