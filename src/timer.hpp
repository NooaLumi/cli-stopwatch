#include <chrono>
#include <string>

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

enum TimeFormat {
    milliseconds,
    seconds,
    minutes,
    hours
};

class Timer {
private:
    std::chrono::_V2::steady_clock::time_point timeStart;
    std::chrono::_V2::steady_clock::time_point timeEnd;
    std::chrono::nanoseconds elapsedTime;
    bool isStopped;

    template <typename DurationType>
    int GetTime() const;

public:
    Timer();

    void Start();
    void Stop();
    void Toggle();

    int GetMilliseconds() const;
    int GetSeconds() const;
    int GetMinutes () const;
    int GetHours() const;

    bool IsStopped() const;
};

#endif // TIMER_TIMER_H_