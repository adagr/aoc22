#include "day.hpp"
#include <queue>

class Day18 : public Day {

public:
    Day18() : Day{"input/day18.txt"} {}
    ~Day18() override = default;

    struct Point {
        int x, y, z;
        bool operator==(const Point& p) const {
            return x == p.x && y == p.y && z == p.z;
        }
    };    

    void run() override {
        // Part 1
        std::vector<Point> cubes{};
        int sum{};
        int xMin{}, xMax{}, yMin{}, yMax{}, zMin{}, zMax{};
        for (const auto& line : lines) {
            sum += 6;
            auto coord = getNumbersInLine(line, ',');
            auto cube = Point{coord[0], coord[1], coord[2]};
            xMin = std::min(xMin, cube.x);
            xMax = std::max(xMax, cube.x);
            yMin = std::min(yMin, cube.y);
            yMax = std::max(yMax, cube.y);
            zMin = std::min(zMin, cube.z);
            zMax = std::max(zMax, cube.z);
            if (std::find(cubes.begin(), cubes.end(), Point{cube.x - 1, cube.y, cube.z}) != cubes.end())
                sum -= 2;
            if (std::find(cubes.begin(), cubes.end(), Point{cube.x + 1, cube.y, cube.z}) != cubes.end())
                sum -= 2;
            if (std::find(cubes.begin(), cubes.end(), Point{cube.x, cube.y - 1, cube.z}) != cubes.end())
                sum -= 2;
            if (std::find(cubes.begin(), cubes.end(), Point{cube.x, cube.y + 1, cube.z}) != cubes.end())
                sum -= 2;
            if (std::find(cubes.begin(), cubes.end(), Point{cube.x, cube.y, cube.z - 1}) != cubes.end())
                sum -= 2;
            if (std::find(cubes.begin(), cubes.end(), Point{cube.x, cube.y, cube.z + 1}) != cubes.end())
                sum -= 2;

            cubes.emplace_back(cube);
        }

        std::cout << sum << std::endl;

        // Part 2
        std::deque<Point> q;
        q.emplace_back(Point{0,0,0});
        std::vector<Point> exposedPoints{};
        while(!q.empty()) {
            auto point = q.front();
            q.pop_front();
            exposedPoints.push_back(point);
            if (point.x > xMin) {
                auto p = Point{point.x - 1, point.y, point.z};
                addNeighbour(exposedPoints, cubes, p, q);
            }
            if (point.x < xMax) {
                auto p = Point{point.x + 1, point.y, point.z};
                addNeighbour(exposedPoints, cubes, p, q);
            }
            if (point.y > yMin) {
                auto p = Point{point.x, point.y - 1, point.z};
                addNeighbour(exposedPoints, cubes, p, q);
            }
            if (point.y < yMax) {
                auto p = Point{point.x, point.y + 1, point.z};
                addNeighbour(exposedPoints, cubes, p, q);
            }
            if (point.z > zMin) {
                auto p = Point{point.x, point.y, point.z - 1};
                addNeighbour(exposedPoints, cubes, p, q);
            }
            if (point.z < zMax) {
                auto p = Point{point.x, point.y, point.z + 1};
                addNeighbour(exposedPoints, cubes, p, q);
            }
        }

        for (int x = xMin + 1; x < xMax; ++x) {
            for (int y = yMin + 1; y < yMax; ++y) {
                for (int z = zMin + 1; z < zMax; ++z) {
                    if (std::find(cubes.begin(), cubes.end(), Point{x, y, z}) == cubes.end() &&
                        std::find(exposedPoints.begin(), exposedPoints.end(), Point{x, y, z}) == exposedPoints.end()) {
                        int exposed = 6;
                        int nextTo = 6;
                        for (int i = x - 1; i >= xMin; --i) {
                            if (std::find(cubes.begin(), cubes.end(), Point{i, y, z}) != cubes.end()) {
                                --exposed;
                                break;
                            }
                            if (i == x - 1)
                                --nextTo;
                        }
                        for (int i = x + 1; i <= xMax; ++i) {
                            if (std::find(cubes.begin(), cubes.end(), Point{i, y, z}) != cubes.end()) {
                                --exposed;
                                break;
                            }
                            if (i == x + 1)
                                --nextTo;
                        }
                        for (int i = y - 1; i >= yMin; --i) {
                            if (std::find(cubes.begin(), cubes.end(), Point{x, i, z}) != cubes.end()) {
                                --exposed;
                                break;
                            }
                            if (i == y - 1)
                                --nextTo;
                        }
                        for (int i = y + 1; i <= yMax; ++i) {
                            if (std::find(cubes.begin(), cubes.end(), Point{x, i, z}) != cubes.end()) {
                                --exposed;
                                break;
                            }
                            if (i == y + 1)
                                --nextTo;
                        }
                        for (int i = z - 1; i >= zMin; --i) {
                            if (std::find(cubes.begin(), cubes.end(), Point{x, y, i}) != cubes.end()) {
                                --exposed;
                                break;
                            }
                            if (i == z - 1)
                                --nextTo;
                        }
                        for (int i = z + 1; i <= zMax; ++i) {
                            if (std::find(cubes.begin(), cubes.end(), Point{x, y, i}) != cubes.end()) {
                                --exposed;
                                break;
                            }
                            if (i == z + 1)
                                --nextTo;
                        }

                        if (exposed == 0)
                            sum -= nextTo;
                    }
                }
            }
        }

        std::cout << sum;
    }

    void addNeighbour(const std::vector<Point>& exposedPoints, const std::vector<Point>& cubes, const Point& p, std::deque<Point>& q) {
        if (std::find(exposedPoints.begin(), exposedPoints.end(), p) == exposedPoints.end() &&
            std::find(cubes.begin(), cubes.end(), p) == cubes.end()) {
            q.push_front(p);
        }
    }

};
