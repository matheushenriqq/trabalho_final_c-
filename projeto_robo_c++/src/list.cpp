#include "./include/list.hpp"
#include <iostream>

// Insert an element at the beginning of the list
void insert_list(tList &list, const std::string &new_data) {
    tNode* new_node = new tNode;
    if (new_node == nullptr) {
        std::cerr << "Error: No space left in memory.\n";
        return;
    }

    new_node->data = new_data;
    new_node->next = list.first_elem; // Set next of new node
    list.first_elem = new_node; // Update list external pointer to new node
}

// Remove an element with the specified value
void remove_list(tList &list, const std::string &del_data) {
    if (list.first_elem == nullptr) {
        std::cerr << "Cannot delete from an empty list.\n";
        return;
    }

    tNode* current = list.first_elem;
    tNode* prev = nullptr;

    while (current != nullptr && current->data != del_data) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (prev == nullptr) {
            list.first_elem = current->next;
        } else {
            prev->next = current->next;
        }

        delete current; // Free memory allocated for the node
    } else {
        std::cerr << "Node with data " << del_data << " not found in the list.\n";
    }
}

// Release allocated memory for the entire list
void free_list(tList &list) {
    tNode* current = list.first_elem;
    while (current != nullptr) {
        tNode* temp = current;
        current = current->next;
        delete temp; // Free memory allocated for the node
    }
    list.first_elem = nullptr; // Reset the list to empty
}

// Print all elements of the list
void print_list(const tList &list) {
    tNode* current = list.first_elem;
    std::cout << "List elements: ";
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}

// Create and initialize a new list
tList create_list() {
    tList list;
    list.first_elem = nullptr; // Initialize the list with nullptr
    return list;
}
