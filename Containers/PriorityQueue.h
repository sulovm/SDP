#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

#include <ostream>
#include "heap.h"

template <typename T>
class PriorityQueue
{
    BinaryHeap<T> heap;
public:
    PriorityQueue(): heap() {}

    int getSize() const
    {
        return heap.getSize();
    }
    void push(const T& element)
    {
        heap.push(element);
    }
    void pop()
    {
        heap.pop();
    }
    T top() const
    {
        return heap.peek();
    }
    bool isEmpty() const
    {
        return heap.isEmpty();
    }
    std::ostream& print(std::ostream& out) const;

    //за 2-ра зад. от 16.11.2015 г.
    bool operator < (const PriorityQueue<T>& other) const
    {
        return getSize() < other.getSize();
    }

};

template <typename T>
std::ostream& PriorityQueue<T>::print(std::ostream& out) const
{
    out << heap;
    return out;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const PriorityQueue<T>& prq)
{
    prq.print(out);
    return out;
}


#endif // PRIORITYQUEUE_H_INCLUDED
