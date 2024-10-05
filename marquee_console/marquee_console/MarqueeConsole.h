#include <string>
#include "MarqueeWorkerThread.h"

class MarqueeConsole {
public:
    MarqueeConsole(const std::string& text);

private:
    MarqueeWorkerThread marqueeThread;
    void inputLoop();
    void printHeader();
    int inputFieldY;  // Added inputFieldY as a member variable
};