#ifndef STACKQUEUE_H_INCLUDED
#define STACKQUEUE_H_INCLUDED

#include <iostream>
#include "Stack.h"

template <typename T>
class StackQueue
{
    Stack<T> inStack;
    Stack<T> outStack;
public:
    StackQueue(): inStack(), outStack() {}

    bool isEmpty() const
    {
        return inStack.empty() && outStack.empty();
    }

    void push(const T& element)
    {
        inStack.push(element);
    }

    void pop(T& element);
    T& getFront();
    size_t size() const
    {
        return inStack.getSize() + outStack.getSize();
    }

    std::ostream& print(std::ostream& out) const;

    bool operator < (const StackQueue<T>& other)
    {
        return size() < other.size();
    }
private:
    void transfer();
};

template <typename T>
void StackQueue<T>::transfer()
{
    while (!inStack.empty())
    {
        T temp;
        inStack.pop(temp);
        outStack.push(temp);
    }
}

template <typename T>
void StackQueue<T>::pop(T& element)
{
    if (outStack.empty())
    {
        transfer();
    }
    outStack.pop(element);
}

template <typename T>
T& StackQueue<T>::getFront()
{
    if (outStack.empty())
    {
        transfer();
    }
    return outStack.getTop();
}

template <typename T>
std::ostream& StackQueue<T>::print(std::ostream& out) const
{
    if (isEmpty())
    {
        out << "The queue is empty!\n";
        return out;
    }
    if (!outStack.empty())
    {
        outStack.print(out);
    }
    if (!inStack.empty())
    {
        Stack<T> helper = inStack;
        Stack<T> reversedHelper;
        while (!helper.empty())
        {
            T temp;
            helper.pop(temp);
            reversedHelper.push(temp);
        }
        reversedHelper.print(out);
    }
    return out;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const StackQueue<T>& sq)
{
    return sq.print(out);
}

#endif // STACKQUEUE_H_INCLUDED
