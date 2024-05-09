#include <thread>
#include <chrono>
#include <ncurses.h>
#include "common.hpp"

void initNcurses () {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);
    start_color();
}

/**
 * Sleep until target frame duration is reached
*/
void capFrames (std::chrono::milliseconds targetFrameDuration, std::chrono::_V2::steady_clock::time_point frameStart) {
    auto elapsedTime = std::chrono::steady_clock::now() - frameStart;
    auto sleepDuration = targetFrameDuration - elapsedTime;

    if (sleepDuration > std::chrono::milliseconds(0)) {
        std::this_thread::sleep_for(sleepDuration);
    }
}
