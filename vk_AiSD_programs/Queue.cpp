#include "Queue.h"

int Queue::pop_front()
{
    if (isEmpty())
    {
        return -1;
    }
    if (stack2.isEmpty())
    {
        while (!stack1.isEmpty())
        {
            stack2.push(stack1.pop());
        }
    }
    return stack2.pop();
}

void Queue::push_back(int value)
{
    stack1.push(value);
}

bool Queue::isEmpty()
{
    return (stack1.isEmpty()&&stack2.isEmpty());
}
