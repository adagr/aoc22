#include "day.hpp"

class Day4 : public Day {

public:
    Day4() : Day{"input/day4.txt"} {}
    ~Day4() override = default;

    auto split(const std::string& line, char delim) {
        auto d = line.find(delim);
        auto left = line.substr(0, d);
        auto right = line.substr(d + 1, line.size() - d);
        return std::make_pair(left, right);
    }

    auto splitInt(const std::string& line, char delim) {
        auto s = split(line, delim);
        return std::make_pair(std::stoi(s.first), std::stoi(s.second));
    }

    void run() override {
        int sum{}, sumPart2{};
        for (const auto& line : lines) {
            auto [left, right] = split(line, ',');
            auto [a, b] = splitInt(left, '-');
            auto [c, d] = splitInt(right, '-');
            if ((c <= a && b <= d) || (a <= c && d <= b))
                ++sum;

            if (c - b <= 0 && a - d <= 0)
                ++sumPart2;
        }

        std::cout << sum << std::endl;
        std::cout << sumPart2;
    }

};
