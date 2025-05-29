#include "DynamicArray.h"
#include <iostream>
#include <cassert>

DynamicArray::DynamicArray() :size(0), capacity(0), array(nullptr)
{}
DynamicArray::~DynamicArray()
{
    delete[] array;
}
int& DynamicArray::operator[](int index)
{
    if (isEmpty())
    {
        assert(isEmpty() == 0);
    }
    if (index >=0)
    {
        assert(index < size);
        return array[index];
    }
    else
    {
        assert(index >= -size);
        return *(array + size + index);
    }
}
bool DynamicArray::isEmpty()
{
    return size == 0;
}
void DynamicArray::push_back(int value)
{
    if (isEmpty())
    {
        resize(1);
    }
    else
    {
        if (capacity == size)
        {
            resize(capacity * 2);
        }
    }
    
    
    size++;
    array[size - 1] = value;
}
int DynamicArray::pop_back()
{
    if (isEmpty())
    {
        return -1;
    }
    int temp = array[size - 1];
    array[size - 1] = -1;
    size--;
    if (size == capacity / 4 && capacity>1)
    {
       resize(capacity / 2);
    }
    return temp;
}
void DynamicArray::resize(int NewCapacity)
{
    capacity = NewCapacity;
    int* temp_array = new int[capacity];
    for (int i = 0; i < size; i++)
    {
        temp_array[i] = array[i];
         
    }
    delete[] array;
    array = temp_array;

}
int DynamicArray::getSize()
{
    return size;
}
int DynamicArray::getCapacity()
{
    return capacity;
}
int* DynamicArray::getArray()
{
    return array;
}
void DynamicArray::print_all()
{
    std::cout << size<<std::endl;
    std::cout << capacity <<std::endl;
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] <<' ';
    }
    std::cout << std::endl;
}
