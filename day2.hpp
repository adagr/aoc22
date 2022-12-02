#include "day.hpp"

class Day2 : public Day {

public:
    Day2() : Day{"input/day2.txt"} {}
    ~Day2() override = default;

    void run() override {
        // Part 1
        std::map<char, int> scores = {{'X', 1}, {'Y', 2}, {'Z', 3}, {'A', 1}, {'B', 2}, {'C', 3}};
        int sum{};
        for (const auto& line : lines)
            sum += beats(line[2], line[0]) + scores[line[2]];

        std::cout << sum << std::endl;

        // Part 2
        sum = 0;
        std::map<char, char> loses = {{'A', 'Z'}, {'B', 'X'}, {'C', 'Y'}};
        std::map<char, char> wins = {{'A', 'Y'}, {'B', 'Z'}, {'C', 'X'}};
        for (const auto& line : lines) {
            switch (line[2]) {
            case 'X':
                sum += scores[loses[line[0]]];
                break;
            case 'Y':
                sum += scores[line[0]] + 3;
                break;
            case 'Z':
                sum += scores[wins[line[0]]] + 6;
                break;
            default:
                break;
            }
        }

        std::cout << sum;
    }

    int beats(char player1, char player2) {
        switch (player1) {
        case 'X':
            switch (player2) {
            case 'A':
                return 3;
            case 'B':
                return 0;
            case 'C':
                return 6;
            default:
                break;
            }
            break;
        case 'Y':
            switch (player2) {
            case 'A':
                return 6;
            case 'B':
                return 3;
            case 'C':
                return 0;
            default:
                break;
            }
            break;
        case 'Z':
            switch (player2) {
            case 'A':
                return 0;
            case 'B':
                return 6;
            case 'C':
                return 3;
            default:
                break;
            }
            break;
        default:
            break;
        }

        return 0;
    }

};
