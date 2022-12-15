#include "day.hpp"

class Day9 : public Day {

public:
    Day9() : Day{"input/day9.txt"} {}
    ~Day9() override = default;

    class Point {
    public:
        Point() : x{}, y{} {}
        void right() { x += 1; }
        void left() { x -= 1; }
        void up() { y += 1; }
        void down() { y -= 1; }
        void follow(const Point& p) {
            if (std::abs(x - p.x) >= 2) {
                x - p.x >= 2 ? left() : right();
                if (y != p.y)
                    y - p.y > 0 ? down() : up();
            } else if (std::abs(y - p.y) >= 2) {
                y - p.y >= 2 ? down() : up();
                if (x != p.x)
                    x - p.x > 0 ? left() : right();
            }
        }

        int x, y;
    };

    void run() override {
        // Part 1
        moveRope(2);
        // Part 2
        moveRope(10);
    }

    void moveRope(int knots) {
        std::vector<Point> points{};
        for (int i{}; i < knots - 1; ++i)
            points.push_back(Point{});

        auto head = Point{};
        std::set<std::pair<int, int>> visited{};
        visited.emplace(std::make_pair(0, 0));
        for (const auto& line : lines) {
            auto size = std::stoi(line.substr(2, line.size() - 2));
            for (int i{}; i < size; ++i) {
                movePoint(head, line[0]);
                auto target = head;
                for (auto& p : points) {
                    p.follow(target);
                    target = p;
                }

                visited.emplace(std::make_pair(points.back().x, points.back().y));
            }
        }

        std::cout << visited.size() << std::endl;
    }

    void movePoint(Point& p, char dir) {
        switch (dir) {
        case 'R':
            p.right();
            break;
        case 'L':
            p.left();
            break;
        case 'U':
            p.up();
            break;
        case 'D':
            p.down();
            break;
        default:
            break;
        }
    }

};
