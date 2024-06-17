#ifndef LIST_H
#define LIST_H

#include <string>

// Structure to represent a node in the list
struct tNode {
    std::string data;
    tNode* next;
};

// Structure to represent the list
struct tList {
    tNode* first_elem;
};

// Function to list the way taken by the robot
void list_way(tList &list, int actual[2]);

// Function to insert a new element into the list
void insert_list(tList &list, const std::string &new_data);

// Function to remove an element from the list
void remove_list(tList &list, const std::string &del_data);

// Function to free the memory allocated for the list
void free_list(tList &list);

// Function to print all elements in the list
void print_list(const tList &list);

// Function to create and initialize a new list
tList create_list();

#endif // LIST_H
