#include "day.hpp"
#include <unordered_set>

class Day3 : public Day {

public:
    Day3() : Day{"input/day3.txt"} {}
    ~Day3() override = default;

    void run() override {
        // Part 1
        int sum{};
        for (const auto& line : lines) {
            auto compLeft = line.substr(0, line.size()/2);
            auto compRight = line.substr(line.size()/2, line.size()/2);
            for (const auto& left : compLeft) {
                if (compRight.find(left) != std::string::npos) {
                    sum += getValue(left);
                    break;
                }
            }
        }

        std::cout << sum << std::endl;

        // Part 2
        sum = 0;
        int i{};
        std::unordered_map<char, int> items{};
        std::unordered_set<char> uniqueItems{};
        for (const auto& line : lines) {
            for (const auto& c : line)
                uniqueItems.emplace(c);

            for (const auto& c : uniqueItems)
                ++items[c];

            uniqueItems.clear();
            ++i;
            if (i == 3) {
                auto it = std::find_if(items.begin(), items.end(), [](const std::pair<char, int>& item){
                    return item.second == 3;
                });
                sum += getValue((*it).first);
                i = 0;
                items.clear();
            }
        }

        std::cout << sum;
    }

    int getValue(char c) {
        if (std::isupper(c))
            return c - 'A' + 27;

        return c - 'a' + 1;
    }

};
