#include "day.hpp"

class Day10 : public Day {

public:
    Day10() : Day{"input/day10.txt"} {}
    ~Day10() override = default;

    void run() override {
        int x = 1;
        int cycle{};
        int signalStrength{};
        std::cout << "#";
        int pixel{};
        for (const auto& line : lines) {
            auto inst = line.substr(0, 4);
            ++cycle;
            signalStrength += getSignalStrength(cycle, x);
            drawPixel(pixel, x);
            if (inst == "addx") {
                ++cycle;
                signalStrength += getSignalStrength(cycle, x);
                x += std::stoi(line.substr(4, line.size() - 4));
                drawPixel(pixel, x);
            }
        }

        std::cout << signalStrength << " " << cycle << std::endl;
    }

    void drawPixel(int& pixel, int x) {
        ++pixel;
        if (pixel == 40) {
            pixel = 0;
            std::cout << std::endl;
        }

        if (std::abs(x - pixel) <= 1)
            std::cout << "#";
        else
            std::cout << ".";
    }

    int getSignalStrength(int cycle, int x) {
        if (cycle == 20 || (cycle - 20) % 40 == 0)
            return cycle * x;

        return 0;
    }

};
