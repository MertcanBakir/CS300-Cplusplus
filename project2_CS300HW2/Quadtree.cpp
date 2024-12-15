//
// Created by Mertcan Bakır on 6.11.2024.
//
#include <iostream>
#include "Quadtree.h"
#include <vector>
#include <string>


node* Quadtree::insertNodes(node* current, string city, int x, int y) {
    if (current == nullptr) { // checks that position is null or not
        return new node(city, x, y);
    }

    if (x >= current->x_axis && y < current->y_axis) {  // set node to the Southeast (SE) child
        current->SE = insertNodes(current->SE, city, x, y);
    }
    else if (x < current->x_axis && y < current->y_axis) {  // set node to the Southwest (SW) child
        current->SW = insertNodes(current->SW, city, x, y);
    }
    else if (x >= current->x_axis && y >= current->y_axis) {  // set node to the Northeast (NE) child
        current->NE = insertNodes(current->NE, city, x, y);
    }
    else if (x < current->x_axis && y >= current->y_axis) {  // set node to the Northwest (NW) child
        current->NW = insertNodes(current->NW, city, x, y);
    }

    return current;
}

void Quadtree::insertion(string city, int x, int y) {

    head = insertNodes(head, city, x, y); // Start the insertion process at the root node
}


void Quadtree::printTree(node* current) {
    if (current == nullptr) {   //Stopping condition for the recursion
        return;
    }

    // Print the city name stored in the current node.
    cout << current->city_name << endl;

    // Recursively traverse the Southeast (SE) quadrant of the quadtree.
    printTree(current->SE);

    // Recursively traverse the Southwest (SW) quadrant of the quadtree.
    printTree(current->SW);

    // Recursively traverse the Northeast (NE) quadrant of the quadtree.
    printTree(current->NE);

    // Recursively traverse the Northwest (NW) quadrant of the quadtree.
    printTree(current->NW);
}

void Quadtree::printAllNodes() {
    printTree(head); // set the starting point as root
}


bool Quadtree::isfound(node* current, int x, int y, int r){ // checks that node is in the circle or not
    if ((current->x_axis - x) * (current->x_axis - x) + (current->y_axis - y) * (current->y_axis - y) < r * r) {
        return true; // means in the circle

    }
    return false; // means not in the circle
}



node* Quadtree::SearchNodes(node* current, int x, int y, int r, vector<string>& found, vector<string>& search) {
    if (current == nullptr)return nullptr;

    search.push_back(current->city_name); // push to searched vector that list of searched nodes


    if (isfound(current, x, y, r)) { // checks that node is in the circle
        found.push_back(current->city_name); // if it is, push to founded vector that list of founded nodes
    }

    if (current->x_axis <= x - r && current->y_axis <= y - r) { // Checks that do we need to look Only NE
        current->NE = SearchNodes(current->NE, x, y, r, found, search);
    }
    else if (current->x_axis > x + r && current->y_axis <= y - r) { // Checks that do we need to look Only NW
        current->NW = SearchNodes(current->NW, x, y, r, found, search);
    }
    else if (current->x_axis <= x - r && current->y_axis > y + r) { // Checks that we do need to look Only SE
        current->SE = SearchNodes(current->SE, x, y, r, found, search);
    }
    else if (current->x_axis > x + r && current->y_axis > y + r) { //Checks that we do need to look Only SW
        current->SW = SearchNodes(current->SW, x, y, r, found, search);
    }
    else if (current->y_axis <= y - r) { //Checks that we do need to look Both NE and NW
        current->NE = SearchNodes(current->NE, x, y, r, found, search);
        current->NW = SearchNodes(current->NW, x, y, r, found, search);
    }
    else if (current->x_axis <= x - r) { //Checks that we do need to look Both SE and NE
        current->SE = SearchNodes(current->SE, x, y, r, found, search);
        current->NE = SearchNodes(current->NE, x, y, r, found, search);
    }
    else if (current->x_axis > x + r) { //Checks that we do need to look Both SW and NW
        current->SW = SearchNodes(current->SW, x, y, r, found, search);
        current->NW = SearchNodes(current->NW, x, y, r, found, search);
    }
    else if (current->y_axis > y + r) { //Checks that we do need to look Both SE and SW
        current->SE = SearchNodes(current->SE, x, y, r, found, search);
        current->SW = SearchNodes(current->SW, x, y, r, found, search);

    }else if (x < current->x_axis && current->x_axis <= x + r && current->y_axis >= y - r && y > current->y_axis && !(isfound(current, x, y, r))) { //Checks that we do need to look All but SE
        current->SW = SearchNodes(current->SW, x, y, r, found, search);
        current->NE = SearchNodes(current->NE, x, y, r, found, search);
        current->NW = SearchNodes(current->NW, x, y, r, found, search);
    }
    else if (x > current->x_axis && current->x_axis >= x - r && current->y_axis >= y - r && y > current->y_axis && !(isfound(current, x, y, r))) { //Checks that we do need to look All but SW
        current->SE = SearchNodes(current->SE, x, y, r, found, search);
        current->NE = SearchNodes(current->NE, x, y, r, found, search);
        current->NW = SearchNodes(current->NW, x, y, r, found, search);
    }
    else if (x < current->x_axis && current->x_axis <= x + r && current->y_axis <= y + r && y < current->y_axis && !(isfound(current, x, y, r))) { //Checks that we do need to look All but NE
        current->SE = SearchNodes(current->SE, x, y, r, found, search);
        current->SW = SearchNodes(current->SW, x, y, r, found, search);
        current->NW = SearchNodes(current->NW, x, y, r, found, search);
    }
    else if (x > current->x_axis && current->x_axis >= x - r && current->y_axis <= y + r && current->y_axis > y && !(isfound(current, x, y, r))) {//Checks that we do need to look All but NW
        current->SE = SearchNodes(current->SE, x, y, r, found, search);
        current->SW = SearchNodes(current->SW, x, y, r, found, search);
        current->NE = SearchNodes(current->NE, x, y, r, found, search);
    }
    else { //Checks All quadrants
        current->SE = SearchNodes(current->SE, x, y, r, found, search);
        current->SW = SearchNodes(current->SW, x, y, r, found, search);
        current->NE = SearchNodes(current->NE, x, y, r, found, search);
        current->NW = SearchNodes(current->NW, x, y, r, found, search);



    }
    return current;
}

void Quadtree::Searching(int x, int y, int r) {

    vector<string> founded; // Contains the names of cities that are found within circle
    vector<string> searched; //  Contains the names of all nodes that were visited during the search

    SearchNodes(head, x, y, r, founded, searched);  // Start the recursive search from the root


    if (founded.empty()) { // Check if any cities were found within the circle
        cout << "<None>";
    } else {

        for (int i = 0; i < founded.size(); ++i) {  // Look over the founded vector and print the names of the cities found
            cout << founded[i];
            if (i < founded.size() - 1) { // Add a comma and space between city names
                cout << ", ";
            }
        }
    }
    cout << endl;


    for (int i = 0; i < searched.size(); ++i) { // Look over the searched vector and print the names of all visited nodes
        cout << searched[i];

        if (i < searched.size() - 1) { // Add a comma and space between city names
            cout << ", ";
        }
    }
    cout << endl;
    cout << endl;
}