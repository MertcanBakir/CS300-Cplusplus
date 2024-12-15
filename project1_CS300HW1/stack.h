#ifndef CS300HW1_STACK_H
#define CS300HW1_STACK_H

#include <vector>
using namespace std;

template <class type>
class Stack
{
public:
    Stack(type n); // constructor

    bool isFull() const;  // Checks that if the stack is full or not

    void push(const type& x); // Adds a new element on top of the stack

    type topAndPop(); // Returns and removes the top element from the stack

private:
    vector<type> theArray; // Vector to store elements

    int topOfStack; // Index of the current top of the stack
};


// ı have problem with linking my templated stack class so ı did implementations in header file

template <class type>
Stack<type>::Stack(type n) { // initialize the stack with the size of n
    theArray.resize(n);
    topOfStack = -1;
}

template <class type>
bool Stack<type>::isFull() const { // checks that stack is full or not
    return topOfStack == theArray.size() - 1;
}

template <class type>
void Stack<type>::push(const type& x) { // add a new element to the stack
    if (!isFull()) { // before the push it checks if it is full or not
        theArray[++topOfStack] = x;
    }
}

template <class type>
type Stack<type>::topAndPop() { // returns the last element and pop from the stack
    return theArray[topOfStack--];
}

#endif //CS300HW1_STACK_H