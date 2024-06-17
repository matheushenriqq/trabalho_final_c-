#include "./include/info.hpp"
#include "./include/navigation.hpp"
#include <fstream>
#include <iostream>

// Clear the contents of a file
void Info::clear_file(const std::string &filepath) {
    std::ofstream file(filepath, std::ios::trunc);
    if (!file) {
        std::cerr << "Error opening file for writing.\n";
    } else {
        std::cout << "File " << filepath << " cleared.\n";
    }
}

// Log positions where charging is impossible
void Info::charge_impossible(int actual[2]) {
    tMap map = read_map_from_file();
    int y = actual[1];
    int x = actual[0];

    std::ofstream file("./data/charge_impossible.txt", std::ios::app);
    if (!file) {
        std::cerr << "Error opening file for writing!\n";
        return;
    }

    // Directions to check around the current position
    int directions[5][2] = {
        {0, 1}, {1, 1}, {-1, 1},
        {1, 0}, {-1, 0}
    };

    for (int i = 0; i < 5; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        // Check if the new position is within map bounds
        if (new_x >= 0 && new_x < map.sz_x && new_y >= 0 && new_y < map.sz_y) {
            int color = map.map_data[8 - new_y][new_x];
            if (color == 1) {
                std::cout << "Checking sun at position (" << new_x << ", " << new_y << "): " << color << "\n";
                file << "impossibility of loading found at position (" << new_x << ", " << new_y << ")\nImpossible to charge\n";
                std::cout << "impossibility of loading found at position (" << new_x << ", " << new_y << ") and written to file.\n";
            }
        }
    }
}

// List elements encountered during navigation
void Info::list_way(tList &list, int actual[2]) {
    tMap map = read_map_from_file();
    int y = actual[1];
    int x = actual[0];

    int color = map.map_data[8 - y][x];
    switch (color) {
        case 255: insert_list(list, "free_2_go"); break;
        case 191: insert_list(list, "gold"); break;
        case 127: insert_list(list, "silver"); break;
        case 63:  insert_list(list, "bronze"); break;
        case 1:   insert_list(list, "charge_impossible"); break;  
    }

    tNode* current = list.first_elem;
    std::ofstream file("./data/list_way.txt", std::ios::out);
    if (!file) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    file << "List elements:\n";
    while (current != nullptr) {
        file << current->data << "\n";
        current = current->next;
    }
}

// Log positions where gold is found
int Info::gold(int actual[2]) {
    tMap map = read_map_from_file();
    int y = actual[1];
    int x = actual[0];

    int count = 0;

    if (map.map_data[8 - y][x] == 191) {
        std::ofstream file("./data/gold.txt", std::ios::app);
        if (!file) {
            std::cerr << "Error opening file for writing!\n";
            return 0;
        }

        file << "Gold found at position (" << x << ", " << y << ")\ngold\n";
        std::cout << "Gold found at position (" << x << ", " << y << ") and written to file.\n";
        count++;
    }

    return count;
}

// Log positions where silver is found
int Info::silver(int actual[2]) {
    tMap map = read_map_from_file();
    int x = actual[0];
    int y = actual[1];

    int count = 0;

    if (map.map_data[8 - y][x] == 127) {
        std::ofstream file("./data/silver.txt", std::ios::app);
        if (!file) {
            std::cerr << "Error opening file for writing!\n";
            return 0;
        }

        file << "Silver found at position (" << x << ", " << y << ")\nsilver\n";
        std::cout << "Silver found at position (" << x << ", " << y << ") and written to file.\n";
        count++;
    }

    return count;
}

// Log positions where bronze is found
int Info::bronze(int actual[2]) {
    tMap map = read_map_from_file();
    int x = actual[0];
    int y = actual[1];

    int count = 0;

    if (map.map_data[8 - y][x] == 63) {
        std::ofstream file("./data/bronze.txt", std::ios::app);
        if (!file) {
            std::cerr << "Error opening file for writing!\n";
            return 0;
        }

        file << "Bronze found at position (" << x << ", " << y << ")\nbronze\n";
        std::cout << "Bronze found at position (" << x << ", " << y << ") and written to file.\n";
        count++;
    }

    return count;
}

// Check if a position exists in a vector of Positions
bool Info::position_exists(const std::vector<Position> &positions, int x, int y) {
    for (const auto &pos : positions) {
        if (pos.x == x && pos.y == y) {
            return true;
        }
    }
    return false;
}

// Log positions of obstacles
int Info::obstacles(int actual[2], std::vector<Position> &registered_positions) {
    tMap map = read_map_from_file();
    int y = actual[1];
    int x = actual[0];

    std::ofstream file("./data/obstacles.txt", std::ios::app);
    if (!file) {
        std::cerr << "Error opening file for writing!\n";
        return 0;
    }

    int count = 0;

    // Directions to check around the current position
    int directions[8][2] = {
        {0, 1},  {0, -1}, {1, 0},  {-1, 0},
        {1, 1},  {-1, -1}, {1, -1}, {-1, 1}
    };

    for (int i = 0; i < 8; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        // Check if the new position is within map bounds
        if (new_x >= 0 && new_x < map.sz_x && new_y >= 0 && new_y < map.sz_y) {
            int color = map.map_data[8 - new_y][new_x];
            // If the position is an obstacle (color 0) and hasn't been registered yet
            if (color == 0 && !position_exists(registered_positions, new_x, new_y)) {
                registered_positions.push_back({new_x, new_y});
                count++;
                std::cout << "obstacle_found (" << new_x << ", " << new_y << ")\n";
                file << "Obstacle (color 0) found at position (" << new_x << ", " << new_y << ")\n";
            }
        }
    }

    return count;
}
