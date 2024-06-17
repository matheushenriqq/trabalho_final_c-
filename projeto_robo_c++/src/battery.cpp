#include "./include/battery.hpp"
#include "./include/navigation.hpp"
#include <fstream>

// Constructor to initialize the battery with maximum capacity
Battery::Battery() : top(-1) {
    stack.resize(MAX_BATTERY, 1);
    top = MAX_BATTERY - 1;
}

// Check if the battery is empty
bool Battery::is_empty() const {
    return top == -1;
}

// Check if the battery is full
bool Battery::is_full() const {
    return top == MAX_BATTERY - 1;
}

// Push (recharge) a unit of battery
void Battery::push(int value) {
    if (!is_full()) {
        stack[++top] = value;
    }
}

// Pop (consume) a unit of battery
int Battery::pop() {
    if (!is_empty()) {
        return stack[top--];
    }
    return -1; // Indicates that the battery is empty
}

// Get the current battery level
int Battery::battery_level() const {
    return top + 1;
}

// Simulate battery recharging
void Battery::recharge_battery() {
    std::cout << "Recharging battery...\n";
    std::this_thread::sleep_for(std::chrono::seconds(RECHARGE_TIME));
    while (!is_full()) {
        push(1);
    }
    std::cout << "Battery fully recharged. Battery level: " << battery_level() << "\n";
}

// Manage battery while moving the robot
int Battery::manage_battery_on_move(int* actual, int* next_pos) {
    tMap mapa = read_map_from_file();
    if (mapa.map_data.empty()) {
        std::cerr << "Failed to read map data\n";
        return -1; // Indicating error
    }

    int time = 0;
    int y_bat = next_pos[1];
    int x_bat = next_pos[0];

    if (y_bat < 0 || y_bat >= mapa.sz_y || x_bat < 0 || x_bat >= mapa.sz_x) {
        std::cerr << "Next position out of map bounds\n";
        return -1; // Indicating error
    }

    int cell = mapa.map_data[8 - y_bat][x_bat];
    int level = battery_level();

    if (cell == 255 || cell == 191 || cell == 127 || cell == 63) { // Navigable areas
        if (level > 1) {
            pop();
            actual[0] = x_bat;
            actual[1] = y_bat;
            time += MOVE_TIME;
            std::cout << "2 seconds for move\n";
            std::this_thread::sleep_for(std::chrono::seconds(MOVE_TIME));
            std::cout << "Moved to (" << actual[0] << ", " << actual[1] << "), Battery: " << battery_level() << "\n";

            // Check if the battery is at 25% or less
            if (level - 1 < 2) {
                std::cout << "Battery low. Charging at (" << actual[0] << ", " << actual[1] << ")\n";
                recharge_battery();

                std::ofstream file("./data/charging.txt", std::ios::app);
                if (file) {
                    file << "Charge at (" << x_bat << ", " << y_bat << ")\n";
                } else {
                    std::cerr << "Failed to open charging log file\n";
                }
                time += RECHARGE_TIME;
            }
        } else {
            std::cout << "Not enough battery to move\n";
        }
    } else if (cell == 1) { // Area with impossibility of charging
        if (level > 2) {
            pop();
            actual[0] = x_bat;
            actual[1] = y_bat;
            time += MOVE_TIME;
            std::cout << "2 seconds for move\n";
            std::this_thread::sleep_for(std::chrono::seconds(MOVE_TIME));
            std::cout << "Moved to (" << actual[0] << ", " << actual[1] << "), Battery: " << battery_level() << "\n";
        } else {
            std::cout << "Battery too low to move to an area with impossibility of charge\n";
            // Recharge the battery before moving
            std::cout << "Battery low. Charging at (" << actual[0] << ", " << actual[1] << ")\n";
            recharge_battery();


            std::ofstream file("./data/charging.txt", std::ios::app);
            if (file) {
                file << "Charge at (" << actual[0] << ", " << actual[1] << ")\n";
            } else {
                std::cerr << "Failed to open charging log file\n";
            }
            time += RECHARGE_TIME;            
            pop();
            actual[0] = x_bat;
            actual[1] = y_bat;
            time += MOVE_TIME;
            std::cout << "2 seconds for move\n";
            std::this_thread::sleep_for(std::chrono::seconds(MOVE_TIME));
            std::cout << "Moved to (" << actual[0] << ", " << actual[1] << "), Battery: " << battery_level() << "\n";
        }
    }

    return time;
}
