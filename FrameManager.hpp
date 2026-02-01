#pragma once

#include <iostream>

#include <chrono>
using namespace std::chrono;

class FrameManager {
    public:
        void start() {
            startTimePoint = system_clock::now();
        }

        void printCurrentTime() {
            time_t time = system_clock::to_time_t(system_clock::now());
            std::cout << std::ctime(&time);
        }

        void printStartTime() {
            time_t time = system_clock::to_time_t(startTimePoint);
            std::cout << std::ctime(&time) << '\n';
        }

        int64_t getFramesFromStart() {
            seconds startSeconds = duration_cast<seconds>(startTimePoint.time_since_epoch());
            system_clock::time_point currentTimePoint = system_clock::now();
            seconds currentSeconds = duration_cast<seconds>(currentTimePoint.time_since_epoch());
            int64_t secondsFrames = (currentSeconds - startSeconds).count() * 60;
            milliseconds currentMiliseconds = duration_cast<milliseconds>(currentTimePoint.time_since_epoch());
            int64_t milliFrames = (currentMiliseconds.count() - currentSeconds.count() * 1000) / (1000 / 60);
            return secondsFrames + milliFrames;
        }

    private:
        system_clock::time_point startTimePoint;
};