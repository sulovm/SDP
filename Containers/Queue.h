#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node<T>* next;

    Node(const T& element):data(element), next(NULL) {}
};


template <typename T>
class Queue
{
    Node<T>* front;
    Node<T>* rear;
public:
    Queue(): front(NULL), rear(NULL) {}

    Queue(const Queue<T>& other): front(NULL), rear(NULL)
    {
        copyQueue(other);
    }

    ~Queue()
    {
        destroyQueue();
    }

    Queue<T>& operator =(const Queue<T>& other);

    void push(const T& element);
    void pop(T& element);

    bool empty() const
    {
        return front == NULL && rear == NULL;
    }
    T& getFront() const
    {
        return front->data;
    }
    size_t getSize() const;

    std::ostream& print(std::ostream& out);
private:
    void copyQueue(const Queue<T>& other);
    void destroyQueue();
};

template <typename T>
void Queue<T>::copyQueue(const Queue<T>& other)
{
    Node<T>* q = other.front;
    while(q != NULL)
    {
        push(q->data);
        q = q->next;
    }
}

template <typename T>
void Queue<T>::destroyQueue()
{
    while (!empty())
    {
        T x;
        pop(x);
    }
}

template <typename T>
Queue<T>& Queue<T>::operator =(const Queue<T>& other)
{
    if (this != &other)
    {
        destroyQueue();
        copyQueue(other);
    }
    return *this;
}

template <typename T>
void Queue<T>::push(const T& element)
{
    if (empty())
    {
        front = new Node<T>(element);
        rear = front;
        return;
    }
    Node<T>* p = new Node<T>(element);
    rear->next = p;
    rear = p;
}

template <typename T>
void Queue<T>::pop(T& element)
{
    if (empty())
    {
        return;
    }
    element = getFront();
    Node<T>* p = front;
    if(front == rear)
    {
        front = rear = NULL;
    }
    else
    {
        front = front->next;
    }
    delete p;
    p = NULL;
}

template <typename T>
size_t Queue<T>::getSize() const
{
    if (empty())
    {
        return 0;
    }
    Node<T>* p = front;
    unsigned counter = 0;
    while (p != NULL)
    {
        counter++;
        p = p->next;
    }
    return counter;
}

template <typename T>
std::ostream& Queue<T>::print(std::ostream& out)
{
    if (empty())
    {
        out << "[]\n";
        return out;
    }
    Node<T>* p = front;
    out << "[";
    while (p->next != NULL)
    {
        out << p->data << ", ";
        p = p->next;
    }
    out << p->data << "]\n";
    return out;
}


#endif // QUEUE_H_INCLUDED
