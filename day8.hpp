#include "day.hpp"

class Day8 : public Day {

public:
    Day8() : Day{"input/day8.txt"} {}
    ~Day8() override = default;

    void run() override {
        std::vector<std::vector<int>> trees{};
        for (const auto& line : lines) {
            std::vector<int> row{};
            for (const auto& c : line)
                row.emplace_back(c - '0');

            trees.push_back(row);
        }

        int visable{};
        int highscore{0};
        for (int i{1}; i < trees.size() - 1; ++i) {
            for (int j{1}; j < trees[i].size() - 1; ++j) {
                int vis{4};
                int score{1};
                int distance{};
                while(j - distance > 0) {
                    ++distance;
                    if (trees[i][j] <= trees[i][j - distance]) {
                        --vis;
                        break;
                    }
                }

                score *= distance;
                distance = 0;
                while(j + distance < trees[i].size() - 1) {
                    ++distance;
                    if (trees[i][j] <= trees[i][j + distance]) {
                        --vis;
                        break;
                    }
                }

                score *= distance;
                distance = 0;
                while(i - distance > 0) {
                    ++distance;
                    if (trees[i][j] <= trees[i - distance][j]) {
                        --vis;
                        break;
                    }
                }

                score *= distance;
                distance = 0;
                while(i + distance < trees.size() - 1) {
                    ++distance;
                    if (trees[i][j] <= trees[i + distance][j]) {
                        --vis;
                        break;
                    }
                }

                score *= distance;
                highscore = std::max(highscore, score);
                if (vis > 0)
                    ++visable;
            }
        }

        auto sum = visable + trees.size() * 2 + trees[0].size() * 2 - 4;
        std::cout << sum << std::endl;
        std::cout << highscore;
    }

};
