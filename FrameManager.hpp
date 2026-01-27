#pragma once

#include <iostream>

#include <chrono>
using namespace std::chrono;

class FrameManager {
    public:
        void start() {
            startTimePoint = system_clock::now();
            previousTimePoint = system_clock::now();
            startTime = duration_cast<milliseconds>(startTimePoint.time_since_epoch());
        }

        void printStartTime() {
            time_t time = system_clock::to_time_t(startTimePoint);
            std::cout << std::ctime(&time) << '\n';
        }

        void printCurrentTime() {
            time_t time = system_clock::to_time_t(system_clock::now());
            std::cout << "Time: " << std::ctime(&time);
            std::cout << "Milliseconds: " << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << '\n';
        }

        int64_t getMillisecondsFromStart() {
            milliseconds millisecondsNow = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
            return (millisecondsNow - startTime).count();
        }

        int64_t getMillisecondsFromPrevious() {
            milliseconds millisecondsNow = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
            milliseconds difference = millisecondsNow - duration_cast<milliseconds>(previousTimePoint.time_since_epoch());
            previousTimePoint = system_clock::now();
            return difference.count();
        }

    private:
        system_clock::time_point startTimePoint;
        system_clock::time_point previousTimePoint;
        milliseconds startTime;
};