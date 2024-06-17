#ifndef INFO_H
#define INFO_H

#include "navigation.hpp"
#include "list.hpp"
#include <vector>
#include <string>

class Info {
public:
    // Clears the contents of a file at the specified filepath
    static void clear_file(const std::string &filepath);

    // Checks and logs positions where charging is impossible based on current position
    static void charge_impossible(int actual[2]);

    // Lists elements encountered during navigation and writes to a file
    static void list_way(tList &list, int actual[2]);

    // Logs positions where gold is found and returns the count
    static int gold(int actual[2]);

    // Logs positions where silver is found and returns the count
    static int silver(int actual[2]);

    // Logs positions where bronze is found and returns the count
    static int bronze(int actual[2]);

    // Identifies obstacles around the current position and logs them
    static int obstacles(int actual[2], std::vector<Position> &registered_positions);

    // Checks if a position exists in a vector of positions
    static bool position_exists(const std::vector<Position> &positions, int x, int y);
};

#endif // INFO_H
