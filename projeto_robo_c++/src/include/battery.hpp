#ifndef BATTERY_H
#define BATTERY_H

#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include "navigation.hpp"

#define MAX_BATTERY 4
#define RECHARGE_TIME 4
#define MOVE_TIME 2

class Battery {
public:
    // Constructor to initialize the battery with maximum capacity
    Battery();

    // Check if the battery is empty
    bool is_empty() const;

    // Check if the battery is full
    bool is_full() const;

    // Push (recharge) a unit of battery
    void push(int value);

    // Pop (consume) a unit of battery
    int pop();

    // Get the current battery level
    int battery_level() const;

    // Simulate battery recharging
    void recharge_battery();

    // Manage battery while moving the robot
    int manage_battery_on_move(int* actual, int* next_pos);

private:
    std::vector<int> stack; // Stack to represent battery units
    int top; // Index to track the top of the stack
};

#endif // BATTERY_H
