#include "day.hpp"

class Day6 : public Day {

public:
    Day6() : Day{"input/day6.txt"} {}
    ~Day6() override = default;

    void run() override {
        // Part 1
        //int size = 3;
        // Part 2
        int size = 13;
        int i{};
        auto line = lines[0];
        while (true) {
            bool success{true};
            for (int j{i}; j < i + size; ++j) {
                auto s = line.substr(j+1, i + size - j).find(line[j]);
                if (s != std::string::npos) {
                    success = false;
                    i += j - i;
                    break;
                }
            }

            if (success) {
                std::cout << i + size + 1 << std::endl;
                break;
            }
            
            ++i;
        }
    }

};
