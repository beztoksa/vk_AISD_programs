#include "Stack.h"
#include <iostream>
#include <cassert>
bool Stack::isEmpty()
{
    return DynamicArray::isEmpty();
}

void Stack::push(int value)
{
    push_back(value);
}

int Stack::pop()
{
    return pop_back();
}

int Stack::peek()
{
    return (*this)[-1];
}

void Stack::printStack()
{
    print_all();
}
