#include "day.hpp"

class Day11 : public Day {

public:
    Day11() : Day{"input/day11.txt"} {}
    ~Day11() override = default;

    struct Monkey {
        std::vector<uint64_t> items{};
        uint64_t test{};
        uint64_t t{};
        uint64_t f{};
        bool add{};
        std::string op;
        uint64_t inspections{};
    };

    void run() override {
        std::vector<Monkey> monkeys{};
        int line = 1;
        while (line < lines.size()) {
            monkeys.emplace_back(readMonkey(line));
            line += 7;
        }

        uint64_t mgn{1};
        for (const auto& monkey : monkeys)
            mgn *= monkey.test;

        for (int round{}; round < 10000; ++round) {
            for (auto& monkey : monkeys) {
                monkey.inspections += monkey.items.size();
                for (auto& item : monkey.items) {
                    if (monkey.add)
                        item += monkey.op == "old" ? item : std::stoi(monkey.op);
                    else
                        item *= monkey.op == "old" ? item : std::stoi(monkey.op);

                    // Part 1
                    //item /= 3;
                    // Part 2
                    item %= mgn;

                    int target{};
                    if (item % monkey.test == 0)
                        target = monkey.t; 
                    else
                        target = monkey.f;

                    monkeys[target].items.push_back(item);
                }

                monkey.items.clear();
            }
        }

        std::sort(monkeys.rbegin(), monkeys.rend(), [](const Monkey& lh, const Monkey& rh) {
            return lh.inspections < rh.inspections;
        });
        std::cout << monkeys[0].inspections * monkeys[1].inspections << std::endl;
    }

    Monkey readMonkey(int line) {
        auto monkey = Monkey{};
        auto list = lines[line].substr(lines[line].find(':') + 1, 50);
        auto items = getFromLine(list, ", ");
        for (const auto& item : items)
            monkey.items.push_back(std::stoi(item));

        ++line;
        auto delim = lines[line].find('+');
        if (delim != std::string::npos)
            monkey.add = true;
        else
            delim  = lines[line].find('*');
        
        monkey.op = lines[line].substr(delim + 2, lines[line].size() - delim - 1);
        ++line;
        monkey.test = std::stoi(lines[line].substr(lines[line].find("by ") + 3, 10));
        ++line;
        monkey.t = std::stoi(lines[line].substr(lines[line].find("monkey ") + 7, 10));
        ++line;
        monkey.f = std::stoi(lines[line].substr(lines[line].find("monkey ") + 7, 10));
        return monkey;
    }

};
