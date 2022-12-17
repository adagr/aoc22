#include "day.hpp"
#include <unordered_set>

class Day14 : public Day {

public:
    Day14() : Day{"input/day14.txt"} {}
    ~Day14() override = default;

    void run() override {
        std::set<std::pair<int, int>> rocks;
        int maxX{}, maxY{}, minX{10000};
        for (const auto& line : lines) {
            auto split = getFromLine(line, " -> ");
            for (int i{}; i < split.size() - 1; ++i) {
                auto delim = split[i].find(',');
                auto x1 = std::stoi(split[i].substr(0, delim));
                auto y1 = std::stoi(split[i].substr(delim + 1, split[i].size() - delim - 1));
                delim = split[i + 1].find(',');
                auto x2 = std::stoi(split[i + 1].substr(0, delim));
                auto y2 = std::stoi(split[i + 1].substr(delim + 1, split[i + 1].size() - delim - 1));
                for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) {
                    for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y) {
                        maxX = std::max(x, maxX);
                        maxY = std::max(y, maxY);
                        minX = std::min(x, minX);
                        rocks.emplace(std::make_pair(x, y));
                    }
                }
            }
        }

        //Part1
        //int max = maxY + 1;
        //bool part1{true};
        //Part2
        int max = maxY + 2;
        bool part1{};

        bool abyss{};
        int units{};
        while (!abyss) {
            auto x = 500;
            auto y = 0;
            bool cannotMove{};
            while (!cannotMove) {
                if (rocks.find(std::make_pair(x, y + 1)) == rocks.end() && y + 1 < max) {
                    y += 1;
                } else if (rocks.find(std::make_pair(x - 1, y + 1)) == rocks.end() && y + 1 < max) {
                    y += 1;
                    x -= 1;
                } else if (rocks.find(std::make_pair(x + 1, y + 1)) == rocks.end() && y + 1 < max) {
                    y += 1;
                    x += 1;
                } else {
                    cannotMove = true;
                    rocks.emplace(std::make_pair(x, y));
                    if ((y + 1 >= max && part1) || (!part1 && x == 500 && y == 0)) {
                        abyss = true;
                        if (!part1)
                            ++units;
                    } else
                        ++units;
                }
            }            
        }

        std::cout << units << std::endl;
    }

};
