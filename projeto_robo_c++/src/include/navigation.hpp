#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <vector>

#define MAX_COORDS 1000 // Maximum number of coordinates

// Structure to store the map
struct tMap {
    int sz_x; // Map size in x direction
    int sz_y; // Map size in y direction
    std::vector<std::vector<int>> map_data; // Map data matrix
};

// Structure to store a position
struct Position {
    int x; // x coordinate
    int y; // y coordinate
};

// Structure to store a path consisting of multiple positions
struct tPath {
    int num_coords; // Number of coordinates in the path
    Position path[MAX_COORDS]; // Array of positions
};

// Function to read coordinates from a file and return them as a path
tPath read_coordinates();

// Function to read the map from a file and return it
tMap read_map_from_file();

// Function to get the map data as a 2D array
std::vector<std::vector<int>> get_map();

// Function to get the next position based on the current position and map data
int get_next_pos(const std::vector<std::vector<int>> &map_data, int *actual, int *next_pos);

#endif // NAVIGATION_H