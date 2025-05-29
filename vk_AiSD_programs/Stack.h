#pragma once
#include "DynamicArray.h"
class Stack : private DynamicArray
{
public:
    bool isEmpty();
    void push(int value);
    int pop();
    int peek();
    void printStack();
};
