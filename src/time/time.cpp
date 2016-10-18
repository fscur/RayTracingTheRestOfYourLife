#include "time.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <algorithm>

double time::totalSeconds = 0;
double time::deltaSeconds = 0;
stopwatch time::_stopwatch = stopwatch();

void time::start()
{
    _stopwatch.start();
    totalSeconds = _stopwatch.getElapsedMilliseconds();
    deltaSeconds = 0;
}

void time::update()
{
    auto totalSecondsLastFrame = totalSeconds;
    totalSeconds = _stopwatch.getElapsedSeconds();
    deltaSeconds = totalSeconds - totalSecondsLastFrame;
}

std::string time::writeNow()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y_%m_%d_%X");
    auto a = ss.str();
    std::replace(a.begin(), a.end(), ':', '_');
    return a;
}
