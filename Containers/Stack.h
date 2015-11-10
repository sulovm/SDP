#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node<T>* next;

    Node(const T& element):data(element), next(NULL) {}
};


template <typename T>
class Stack
{
    Node<T>* top;
public:
    Stack():top(NULL) {}

    Stack(const Stack<T>& other):top(NULL)
    {
        copyStack(other);
    }

    ~Stack()
    {
        destroyStack();
    }

    Stack<T>& operator =(const Stack<T>& other);

    void push(const T& element);
    void pop(T& element);

    bool empty() const
    {
        return top == NULL;
    }
    T& getTop() const
    {
        return top->data;
    }
    size_t getSize() const;

    std::ostream& print(std::ostream& out);
private:
    void copyStack(const Stack<T>& other);
    void destroyStack();
};

template <typename T>
void Stack<T>::copyStack(const Stack<T>& other)
{
    if (other.empty())
    {
        return;
    }
    top = new Node<T>(other.getTop());
    Node<T>* q = other.top->next;
    Node<T>* p = top;
    while (q != NULL)
    {
        Node<T>* node = new Node<T>(q->data);
        p->next = node;
        p = p->next;
        q = q->next;
    }
}

template <typename T>
void Stack<T>::destroyStack()
{
    while (!empty())
    {
        T x;
        pop(x);
    }
}

template <typename T>
Stack<T>& Stack<T>::operator =(const Stack<T>& other)
{
    if (this != &other)
    {
        destroyStack();
        copyStack(other);
    }
    return *this;
}

template <typename T>
void Stack<T>::push(const T& element)
{
    if (empty())
    {
        top = new Node<T>(element);
        return;
    }
    Node<T>* p = new Node<T>(element);
    p->next = top;
    top = p;
    p = NULL;
}

template <typename T>
void Stack<T>::pop(T& element)
{
    if (empty())
    {
        return;
    }
    element = getTop();
    if (top->next == NULL)
    {
        delete top;
        top = NULL;
        return;
    }
    Node<T>* p = top;
    top = top->next;
    delete p;
    p = NULL;
}

template <typename T>
size_t Stack<T>::getSize() const
{
    if (empty())
    {
        return 0;
    }
    Node<T>* p = top;
    unsigned counter = 0;
    while (p != NULL)
    {
        counter++;
        p = p->next;
    }
    return counter;
}

template <typename T>
std::ostream& Stack<T>::print(std::ostream& out)
{
    if (empty())
    {
        out << "[]\n";
        return out;
    }
    Node<T>* p = top;
    out << "[";
    while (p->next != NULL)
    {
        out << p->data << ", ";
        p = p->next;
    }
    out << p->data << "]\n";
    return out;
}


#endif // STACK_H_INCLUDED
