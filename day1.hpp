#include "day.hpp"

class Day1 : public Day {

public:
    Day1() : Day{"input/day1.txt"} {}
    ~Day1() override = default;

    void run() override {
        // Part 1
        std::vector<int> calories{};
        calories.push_back(0);
        for (const auto& line : lines) {
            if (line == "")
                calories.push_back(0);
            else
                calories[calories.size() - 1] += std::stoi(line);
        }

        std::sort(calories.rbegin(), calories.rend());
        std::cout << calories[0] << std::endl;

        // Part 2
        std::cout << std::accumulate(calories.begin(), calories.begin() + 3, 0);
    }

};
