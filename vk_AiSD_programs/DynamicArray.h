#pragma once

class DynamicArray
{
public:
    DynamicArray();
    ~DynamicArray();

    DynamicArray(const DynamicArray& other) = delete;
    DynamicArray& operator=(const DynamicArray& other) = delete;
    int& operator[](int index);

    bool isEmpty();
    void push_back(int value);
    int pop_back();

    int getSize();
    int getCapacity();
    int* getArray();
    void print_all();

private:
    int capacity;
    int size;
    int* array;

    void resize(int capacity);
};

