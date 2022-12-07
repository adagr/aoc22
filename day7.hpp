#include "day.hpp"

class Day7 : public Day {

public:
    Day7() : Day{"input/day7.txt"} {}
    ~Day7() override = default;

    std::map<std::string, std::vector<std::string>> dirs{};
    std::map<std::string, int> sizes{};

    void run() override {
        // Part 1
        std::string currentDir{};
        for (const auto& line : lines) {
            auto split = getFromLine(line, " ");
            if (split[0] == "$") {
                if (split[1] == "cd") {
                    if (split[2] == "..")
                        currentDir = currentDir.substr(0, currentDir.find_last_of('/'));
                    else 
                        currentDir += "/" + split[2];
                } else
                    continue;
            } else if (split[0] == "dir")
                dirs[currentDir].push_back(currentDir + "/" + split[1]);
            else
                sizes[currentDir] += std::stoi(split[0]);
        }

        std::map<std::string, int> sums{};
        for (const auto& [dir, v] : dirs) {
            sums[dir] = sizes[dir];
            sums[dir] += getSize(dir);
        }

        int sum{};
        for (const auto& [dir, s] : sums)
            if (s <= 100000)
                sum += s;

        std::cout << sum << std::endl;

        // Part 2
        auto diff = sums["//"] - 40000000;
        int smallest = 70000000;
        for (const auto& [dir, s] : sums)
            if (s >= diff)
                smallest = std::min(smallest, s);

        std::cout << smallest;
    }

    int getSize(std::string dir) {
        int sum{};
        for (const auto& d : dirs[dir]) {
            sum += sizes[d];
            sum += getSize(d);
        }

        return sum;
    }

};
