#include <stdio.h>
#include "day1.hpp"

int main(int argc, char const *argv[]) {
    Day* day = new Day1{};
    day->run();
    delete day;
    return 0;
}
