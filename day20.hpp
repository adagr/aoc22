#include "day.hpp"
#include <list>

class Day20 : public Day {

public:
    Day20() : Day{"input/day20.txt"} {}
    ~Day20() override = default;

    void run() override {
        // Part 1
        std::list<int64_t> numbers{};
        std::vector<std::list<int64_t>::iterator> order{};
        for (const auto& line : getLinesInt()) {
            //Part 1
            //auto value = line;
            //Part 2
            auto value = line * 811589153ll;
            auto pos = numbers.insert(numbers.end(), value);
            order.push_back(pos);
        }

        for (int mix{}; mix < 10; ++mix) {
            for (auto& number : order) {
                auto value = *number;
                auto it = numbers.erase(number);
                auto distance = std::distance(it, numbers.end());
                auto steps = value % static_cast<int64_t>(numbers.size());
                std::advance(it, steps);
                if (value >= 0) {
                    if (steps >= distance)
                        ++it;
                } else {
                    if (steps <= distance - static_cast<int64_t>(numbers.size()))
                        --it;
                }

                number = numbers.insert(it, value);
            }
        }

        auto res1 = std::find(numbers.begin(), numbers.end(), 0);
        if (1000 >= std::distance(res1, numbers.end()))
            ++res1;
        std::advance(res1, 1000 % numbers.size());
        auto res2 = res1;
        if (1000 >= std::distance(res2, numbers.end()))
            ++res2;
        std::advance(res2, 1000 % numbers.size());
        auto res3 = res2;
        if (1000 >= std::distance(res3, numbers.end()))
            ++res3;
        std::advance(res3, 1000 % numbers.size());
        std::cout << *res1 + *res2 + *res3;
    }

};
