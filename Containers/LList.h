#ifndef LLIST_H_INCLUDED
#define LLIST_H_INCLUDED

#include <cassert>
#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node<T>* next;

    Node(const T& d):data(d), next(NULL) {}
};

template <typename T>
class LList
{
    Node<T>* start;
    Node<T>* end;
public:
    LList():start(NULL), end(NULL){}
    LList(const LList& other)
    {
        copy(other);
    }
    ~LList()
    {
        destroy();
    }
    LList<T>& operator =(const LList& other);

    bool empty() const
    {
        return start == NULL;
    }

    void toEnd(const T& element);
    void toStart(const T& element);
    void insertAt(const T& element, unsigned index);
    void insertAfter(const T& element, unsigned index);

    void deleteAt(T& element, unsigned index);

    std::ostream& print(std::ostream& out) const;
    size_t size() const;
private:
    void copy(const LList& other);
    void destroy();
};

template <typename T>
void LList<T>::copy(const LList& other)
{
    if (other.start != NULL)
    {
        start = new Node<T>(other.start->data);
        Node<T>* p = other.start->next;
        Node<T>* q = start;
        while (p != NULL)
        {
            Node<T>* newBox = new Node<T>(p->data);
            p = p->next;
            q->next = newBox;
            q = newBox;
        }
        end = q;
        q = NULL;
    }
    else
    {
        start = end = NULL;
    }
}

template <typename T>
void LList<T>::destroy()
{
    if (!empty())
    {
        Node<T>* p;
        while (start != NULL)
        {
            p = start;
            start = start->next;
            delete p;
        }
        end = NULL;
    }
}

template <typename T>
LList<T>& LList<T>::operator =(const LList& other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

template <typename T>
void LList<T>::toEnd(const T& element)
{
    if (empty())
    {
        start = new Node<T>(element);
        end = start;
        return;
    }
    Node<T>* p = end;
    end = new Node<T>(element);
    p->next = end;
    p = NULL;
}

template <typename T>
void LList<T>::toStart(const T& element)
{
    Node<T>* p = new Node<T>(element);
    p->next = start;
    start = p;
    if (start->next == NULL)
    {
        end = start;
    }
    p = NULL;
}

template <typename T>
void LList<T>::insertAt(const T& element, unsigned index)
{
    if (index == 0)
    {
        toStart(element);
        return;
    }
    insertAfter(element, index - 1);
}

template <typename T>
void LList<T>::insertAfter(const T& element, unsigned index)
{
    if (!empty())
    {
        if (index >= size())
        {
            toEnd(element);
            return;
        }
        Node<T>* p = start;
        for (int i = 1; i <= index; i++)
        {
            p = p->next;
        }

        Node<T>* q = new Node<T>(element);
        if(p->next != NULL)
        {
            q->next = p->next;
        }
        else
        {
            end = q;
        }
        p->next = q;
        p = q = NULL;
    }
}

template <typename T>
void LList<T>::deleteAt(T& element, unsigned index)
{
    assert(index < size());
    if (!empty())
    {
        Node<T>* p;
        if (index == 0)
        {
            element = start->data;
            p = start;
            start = start->next;
            delete p;
            return;
        }
        size_t sizeOfList = size();
        if (index == sizeOfList - 1)
        {
            element = end->data;
            p = end;
            end = start;
            for (int i = 1; i < sizeOfList - 1; i++)
            {
                end = end->next;
            }
            end->next = NULL;
            delete p;
            return;
        }
        p = start;
        for (int i = 1; i < index; i++)
        {
            p = p->next;
        }
        Node<T>* q = p->next;
        element = q->data;
        p->next = q->next;
        delete q;
    }
}

template <typename T>
std::ostream& LList<T>::print(std::ostream& out) const
{
    if (empty())
    {
        out << "The list is empty!";
        return out;
    }
    Node<T>* p = start;
    while (p != NULL)
    {
        out << p->data << " ";
        p = p->next;
    }
    return out;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const LList<T>& list)
{
    return list.print(out);
}

template <typename T>
size_t LList<T>::size() const
{
    if (empty())
    {
        return 0;
    }
    size_t count = 0;
    Node<T>* p = start;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

#endif // LLIST_H_INCLUDED
