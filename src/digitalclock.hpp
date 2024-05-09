#ifndef TIMER_DIGITALCLOCK_H_
#define TIMER_DIGITALCLOCK_H_

#include <string>
#include <array>
#include <tuple>

using AsciiArt = std::array<std::string, 4>;

class DigitalClock {
private:
    int x, y;

    static void DrawAsciiArt(AsciiArt rows, int x, int y, bool dim);
    static AsciiArt colon, zero, one, two, three, four, five, six, seven, eight, nine;
    static AsciiArt GetAsciiArt(int digit);
    static AsciiArt GetAsciiArt(char character);

    static constexpr int DIGIT_WIDTH = 6;
    static constexpr int COL_WIDTH = 3;
    static constexpr int DIM_DURATION = 30; // ms

public:
    static constexpr int WIDTH = 5 * DIGIT_WIDTH + 2 * COL_WIDTH;
    static constexpr int HEIGHT = 4;

    DigitalClock(int x, int y);
    void Draw(int timerElapsedMs, bool timerIsStopped) const;

    void SetXY(std::tuple<int, int> pos);
};

#endif