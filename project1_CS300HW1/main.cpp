//
// Mertcan Bakır 30879
//
#include <iostream>
#include <fstream>
#include <vector>
#include "stack.h"
using namespace std;


bool SafeCheck(const int chess[], const int& row, const int& col) { // checks that there are another queens in the range
    for (int i = 0; i < row; ++i) {
        if (chess[i] == col) {// Check the same column
            return false;
        }

        if (i == row) {// Check the same column
            return false;
        }

        if ((i - row) == (col - chess[i])) { // Check lower left diagonal
            return false;
        }

        if ((i - row) == (chess[i] - col)) {// Check lower right diagonal
            return false;
        }
    }

    return true; // it is safe to put queen
}




int main() {
    ofstream file;
    int size;

    cout << "Enter the value of N for the N-Queens problem: " << endl; // takes input for board size
    cin >> size;


    while (size < 1) { // enter input until its bigger than 0
        cout << "Invalid input. Please enter a positive integer" << endl;
        cin >> size;
    }

    Stack<int> stck(size); // a stack to do backtracking

    vector<vector<int>> solutions; // vector to store all the possible solutions

    int chessboard[size]; // represent the board which each index is a row

    int row = 0;
    int column = 0;


    bool done = false; // bool for stopping the loop

    while (!done) { //until done is true it keeps in the loop
        if (row == size) { //checks that if we are in the last row or not
            vector<int> solution;
            for (int i = 0; i < size; ++i) { // add the queens places to the vector
                solution.push_back(chessboard[i]);
            }
            solutions.push_back(solution);  //pushed to solutions vector
            row--;
            column = stck.topAndPop() + 1; // do backtracking

        } else if (column >= size) { // looks that are we in the last column of the row
            row--;
            if (row < 0) { //checks row is smaller than zero, it means all possible solutions is checked so all backtracking is done
                done = true;  // make done true for finish the loop
            } else {
                column = stck.topAndPop() + 1;  // do backtracking
            }
        } else {
            if (SafeCheck(chessboard, row, column)) { // checks that is it safe to place the queen
                chessboard[row] = column; // update the board
                stck.push(column);  //pushes to column to the stack
                row++;
                column = 0;
            } else { // it is not safe to place the queen
                column++; // look to next column
            }
        }
    }


    file.open(to_string(size)+"queens_solutions.txt"); // opens the file as Nqueens_solutions
    file << "Total solutions for N=" << size << ": " << solutions.size() << endl; // writes total solution number
    file << endl;
    for (int i = 0; i < solutions.size(); ++i) { // writes the solutions in a loop from solutions vector
        file << "Solution " << i + 1 << ": [";
        for (int j = 0; j < size; ++j) {
            file << solutions[i][j];
            if (j < size - 1) file << ", ";
        }
        file << "]" << endl;
    }
    file.close(); // closes the file
    cout << "Solutions have been saved to ’" + to_string(size)+ "queens_solutions.txt’" << endl;

    return 0;
}