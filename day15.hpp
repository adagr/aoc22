#include "day.hpp"

class Day15 : public Day {

public:
    Day15() : Day{"input/day15.txt"} {}
    ~Day15() override = default;

    void run() override {
        std::map<std::pair<int, int>, std::pair<int, int>> sensors{};
        for (const auto& line : lines) {
            auto s = line.substr(line.find('=') + 1, line.size());
            auto xs = std::stoi(s.substr(0, s.find(',')));
            s = s.substr(s.find('=') + 1, s.size());
            auto ys = std::stoi(s.substr(0, s.find(':')));
            s = s.substr(s.find('=') + 1, s.size());
            auto xb = std::stoi(s.substr(0, s.find(',')));
            s = s.substr(s.find('=') + 1, s.size());
            auto yb = std::stoi(s.substr(0, s.size()));
            sensors[std::make_pair(xs, ys)] = std::make_pair(xb, yb);
        }

        int rows = 4000000;
        for (int row = 0; row <= rows; ++row) {
            std::vector<std::pair<int, int>> ranges{};
            for (const auto& [sensor, beacon] : sensors) {
                auto distance = std::abs(sensor.first - beacon.first) + std::abs(sensor.second - beacon.second);
                if (sensor.second <= row && sensor.second + distance >= row) {
                    auto min = sensor.first - sensor.second - distance + row;
                    auto max = sensor.first + sensor.second + distance - row;
                    min = std::max(min, 0);
                    max = std::min(max, rows);
                    if (addRange(ranges, min, max))
                        ranges.emplace_back(std::make_pair(min, max));
                } else if (sensor.second >= row && sensor.second - distance <= row) {
                    auto min = sensor.first + sensor.second - distance - row;
                    auto max = sensor.first - sensor.second + distance + row;
                    min = std::max(min, 0);
                    max = std::min(max, rows);
                    if (addRange(ranges, min, max))
                        ranges.emplace_back(std::make_pair(min, max));
                }
            }
            auto sum = std::accumulate(ranges.begin(), ranges.end(), 0, [](const int& sum, const std::pair<int, int>& range) {
                return sum + range.second - range.first + 1;
            });
            if (sum <= rows) {
                std::cout << (static_cast<unsigned long long>(ranges[0].second) + 1ull) * 4000000ull + static_cast<unsigned long long>(row);
                break;
            }
        }
    }

    bool addRange(std::vector<std::pair<int, int>>& ranges, int min, int max) {
        for (auto& [x1, x2] : ranges) {
            if (min >= x1 && min <= x2 && max > x2) {
                x2 = max;
                return false;
            } else if (max <= x2 && max >= x1 && min < x1) {
                x1 = min;
                return false;
            } else if (min >= x1 && max <= x2) {
                return false;
            } else if (min < x1 && max > x2) {
                x1 = min;
                x2 = max;
                return false;
            }
        }
        
        return !ranges.size(); // only one range should be enough
    }

};
