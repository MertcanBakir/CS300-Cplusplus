#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Quadtree.h"
using namespace std;

int main() {
    Quadtree tree;
    string city, filename;
    int x, y, r;

    filename = "cities.txt"; // set the file name
    ifstream file(filename);

    file >> x >> y; // read the first line x and y axis of table

    while (file >> city >> x >> y) { // read the file line by line
        tree.insertion(city, x, y); // insert to nodes to the tree
    }
    file.close(); // close the file

    tree.printAllNodes(); // print the tree
    cout << endl;

    filename = "queries0.txt"; // set the file name
    ifstream file2(filename);

    string line;
    while (getline(file2, line)) { // read line by line
        istringstream ss(line);
        string value;


        getline(ss, value, ','); // separate the line from comma
        x = stoi(value); // take the x axis
        getline(ss, value, ','); // separate the line from comma
        y = stoi(value); // take the y axis
        getline(ss, value, ','); // separate the line from comma
        r = stoi(value); // take the radius
        tree.Searching(x, y, r); // search the nodes with that circle
    }

    file2.close(); // close the file

    return 0;
}