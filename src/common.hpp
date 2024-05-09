#ifndef TIMER_COMMON_H_
#define TIMER_COMMON_H_

#include <chrono>

void initNcurses();
void capFrames (std::chrono::milliseconds targetFrameDuration, std::chrono::_V2::steady_clock::time_point frameStart);

#endif