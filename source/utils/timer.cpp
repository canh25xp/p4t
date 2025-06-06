#include "timer.h"

const std::chrono::high_resolution_clock Timer::s_Clock;

Timer::Timer()
    : m_StartTime(Now()) {
}
