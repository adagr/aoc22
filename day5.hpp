#include "day.hpp"

class Day5 : public Day {

public:
    Day5() : Day{"input/day5.txt"} {}
    ~Day5() override = default;

    void run() override {
        // Part 1
        std::map<int, std::deque<char>> crates{}, cratesPart2{};
        bool readInput{true};
        for (auto it = lines.begin(); it < lines.end(); ++it) {
            auto line = *it;
            if (readInput) {
                int index{1};
                int i{};
                while (index < line.size()) {
                    if (line[index] == '1') {
                        readInput = false;
                        ++it;
                        cratesPart2 = crates;
                        break;
                    }
                    if (line[index] != ' ')
                        crates[i].emplace_front(line[index]);

                    index += 4;
                    ++i;
                }
            } else {
                auto data = getFromLine(line, " ");
                auto size = std::stoi(data[1]);
                auto from = std::stoi(data[3]) - 1;
                auto to = std::stoi(data[5]) - 1;
                for (int i{}; i < size; ++i) {
                    auto crate = crates[from].back();
                    crates[from].pop_back();
                    crates[to].push_back(crate);
                }

                // Part 2
                cratesPart2[to].insert(cratesPart2[to].end(), cratesPart2[from].end() - size, cratesPart2[from].end());
                cratesPart2[from].erase(cratesPart2[from].end() - size, cratesPart2[from].end());
            }
        }

        for (const auto& [i, crate] : crates) {
            std::cout << crate.back();
        }

        // Part 2
        std::cout << std::endl;
        for (const auto& [i, crate] : cratesPart2) {
            std::cout << crate.back();
        }
    }

};
