#include "timer.hpp"
#include <chrono>
#include <string>

Timer::Timer() {
    isStopped = true; // timer starts off stopped
    elapsedTime = (std::chrono::nanoseconds) 0;
}

void Timer::Start() {
    if (!isStopped) {
        return;
    }
    isStopped = false;
    timeStart = std::chrono::steady_clock::now();
}

void Timer::Stop() {
    if (isStopped) {
        return;
    }
    isStopped = true;
    timeEnd = std::chrono::steady_clock::now();

    auto sessionTime = timeEnd - timeStart;
    elapsedTime += sessionTime;
}

template <typename DurationType>
int Timer::GetTime() const {
    if (isStopped) {
        return std::chrono::duration_cast<DurationType>(elapsedTime).count();
    }

    return std::chrono::duration_cast<DurationType>(elapsedTime).count() + std::chrono::duration_cast<DurationType>(std::chrono::steady_clock::now() - timeStart).count();
}

int Timer::GetMilliseconds() const {
    return GetTime<std::chrono::milliseconds>();
}

int Timer::GetSeconds() const {
    return GetTime<std::chrono::seconds>();
}

int Timer::GetMinutes() const {
    return GetTime<std::chrono::minutes>();
}

int Timer::GetHours() const {
    return GetTime<std::chrono::hours>();
}

bool Timer::IsStopped() const {
    return isStopped;
}

void Timer::Toggle() {
    if (isStopped) {
        Start();
    } else {
        Stop();
    }
}