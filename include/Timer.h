#pragma once
#include <chrono>
#include <iostream>
#include <string>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start;
    std::string label;

public:
    Timer(const std::string& label)
        : start(std::chrono::high_resolution_clock::now()), label(label) {}

    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();

        auto us = std::chrono::duration_cast<std::chrono::microseconds>(
            end - start
        );

        std::cout << "[" << label << "] "
                  << us.count() << " us" << std::endl;
    }
};