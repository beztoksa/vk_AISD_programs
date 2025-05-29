#pragma once
#include "Stack.h"
class Queue
{
public:
    int pop_front();
    void push_back(int value);
    bool isEmpty();
  

private:
    Stack stack1;
    Stack stack2;

};
