//
// Created by Mertcan Bakır on 6.11.2024.
//

#ifndef CS300HW2_QUADTREE_H
#define CS300HW2_QUADTREE_H
#include <string>
using namespace std;

struct node {
    string city_name; // Name of the city represented by this node
    int x_axis;       // x-coordinate of the city
    int y_axis;       // y-coordinate of the city

    node* SE; // Pointer to the Southeast quadrant child
    node* SW; // Pointer to the Southwest quadrant child
    node* NE; // Pointer to the Northeast quadrant child
    node* NW; // Pointer to the Northwest quadrant child

    // Constructor for initializing a node with city name and coordinates
    node(string city, int x, int y) : city_name(city), x_axis(x), y_axis(y), SE(nullptr), SW(nullptr), NE(nullptr), NW(nullptr) {}
};

class Quadtree {
public:


    node* insertNodes(node* current, string city, int x, int y); // Recursive helper for the insert operation


    void insertion(string city, int x, int y); //insert all the node to the quadtree


    void printAllNodes(); // Prints all nodes in the quadtree


    void printTree(node* current); // Recursive function to print nodes in the quadtree


    void Searching(int x, int y, int r); // Search the nodes that in the circle

    node* SearchNodes(node* current, int x, int y, int r, vector<string>& found, vector<string>& search);// Recursive helper for the search operation


    bool isfound(node* current, int x, int y, int r); // checks that node is in the circle or not

private:

    node* head = nullptr; // root of the quadtree
};

#endif //CS300HW2_QUADTREE_H
