#include <ncurses.h>
#include <chrono>
#include <tuple>
#include <functional>
#include "src/timer.hpp"
#include "src/common.hpp"
#include "src/digitalclock.hpp"

int main(int argc, char ** argv) {
    initNcurses();

    int screenW, screenH;
    getmaxyx(stdscr, screenH, screenW);

    auto getCenterOnScreen = [&screenW, &screenH] (int width, int height) -> std::tuple<int, int> {
        return {(screenW / 2) - (width / 2), (screenH / 2) - (height / 2)} ;
    };

    auto getClockCenterOnScreen = [getCenterOnScreen] () -> std::tuple<int, int> {
        return getCenterOnScreen (DigitalClock::WIDTH, DigitalClock::HEIGHT);
    };

    constexpr auto FRAME_DURATION = std::chrono::milliseconds(16); // Target framerate ~60 fps

    Timer mainTimer;
    DigitalClock clock = std::make_from_tuple<DigitalClock>(getClockCenterOnScreen());

    while(true) {
        auto frameStart = std::chrono::steady_clock::now();
        clear();

        // Handle user input
        if (getch() == ' ') {
            mainTimer.Toggle();
        }

        // Handle screen resize
        int newScreenW, newScreenH;
        getmaxyx(stdscr, newScreenH, newScreenW);
        if (screenW != newScreenW || screenH != newScreenH) {
            screenW = newScreenW;
            screenH = newScreenH;
            clock.SetXY(getClockCenterOnScreen());
        }

        // Draw
        clock.Draw(mainTimer.GetMilliseconds(), mainTimer.IsStopped());
        if (mainTimer.IsStopped()) {
            attron(A_DIM);
        }
        box(stdscr, 0, 0);
        attroff(A_DIM);

        refresh();
        capFrames(FRAME_DURATION, frameStart);
    }

    endwin();
    return 0;
}