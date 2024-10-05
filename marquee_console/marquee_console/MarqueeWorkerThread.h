#include <string>
#include <thread>
#include <mutex>

class MarqueeWorkerThread {
public:
    MarqueeWorkerThread(const std::string& text, int startX, int startY, int delayMs);
    ~MarqueeWorkerThread();
    void stop();
    void updateText(const std::string& newText); // Updates the marquee text

private:
    std::string marqueeText;
    int x, y, dx, dy;  // Added dx and dy for diagonal movement
    int delay;
    std::thread marqueeThread;
    bool threadRunning;
    std::mutex textMutex;

    void run();
};