#include "./include/navigation.hpp"
#include <iostream>
#include <fstream>

// Function to read coordinates from a file and return them as a path
tPath read_coordinates(void) {
    tPath path;
    FILE *file = fopen("./data/path.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!");
        exit(1);
    }

    // Read the number of coordinates from the first line
    fscanf(file, "%d", &path.num_coords);

    // Read each coordinate and store it in the array
    for (int i = 0; i < path.num_coords; i++) {
        fscanf(file, "%d, %d", &path.path[i].x, &path.path[i].y);
    }

    fclose(file);
    return path;
}
// Function to read the map from a file and return it
tMap read_map_from_file() {
    tMap map;
    std::ifstream file("./data/map.txt");
    if (!file) {
        std::cerr << "Error opening file!";
        exit(1);
    }

    // Read the number of rows and columns
    file >> map.sz_x >> map.sz_y;

    // Resize the map data to fit the dimensions
    map.map_data.resize(map.sz_x, std::vector<int>(map.sz_y));

    // Read the map data
    for (int i = 0; i < map.sz_x; i++) {
        for (int j = 0; j < map.sz_y; j++) {
            file >> map.map_data[i][j];
        }
    }

    return map;
}

// Function to get the map data as a 2D vector
std::vector<std::vector<int>> get_map() {
    tMap map = read_map_from_file();
    return map.map_data;
}

// Function to get the next position based on the current position and map data
int get_next_pos(const std::vector<std::vector<int>> &map_data, int *actual, int *next_pos) {
    tPath path = read_coordinates();

    for (int i = 0; i < path.num_coords - 1; i++) {
        if (path.path[i].x == actual[0] && path.path[i].y == actual[1]) {
            next_pos[0] = path.path[i + 1].x;
            next_pos[1] = path.path[i + 1].y;
            return 0;
        }
    }

    std::cerr << "Error! Unable to find next position!\n";
    next_pos[0] = -1;
    next_pos[1] = -1;
    return 0;
}

// Function to print the map
void print_map() {
    tMap map = read_map_from_file();
    std::cout << "Size X: " << map.sz_x << "\n";
    std::cout << "Size Y: " << map.sz_y << "\n";
    std::cout << "Map Data:\n";
    for (int i = 0; i < map.sz_x; i++) {
        for (int j = 0; j < map.sz_y; j++) {
            std::cout << map.map_data[i][j] << " ";
        }
        std::cout << "\n";
    }
}
