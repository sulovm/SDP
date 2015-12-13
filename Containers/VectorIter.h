#ifndef LLISTITER_H_INCLUDED
#define LLISTITER_H_INCLUDED

#include <cassert>
#include <iostream>

template <typename T>
struct NodeL
{
    T data;
    NodeL<T>* next;

    NodeL(const T& d):data(d), next(NULL) {}
};

template <typename T>
class LListIter
{
    NodeL<T>* start;
    NodeL<T>* last;

public:
    class Iterator
    {
        NodeL<T>* ptr;
    public:
        Iterator(): ptr(NULL) {}

        Iterator(NodeL<T>* p) : ptr(p) {}

        Iterator(const Iterator& other) : ptr(other.ptr) {}

        Iterator operator++()
        {
            ptr = ptr->next;
            return *this;
        }
        Iterator operator++(int junk)
        {
            Iterator result (ptr);
            ptr = ptr->next;
            return result;
        }
        T operator*()
        {
            return ptr->data;
        }
        NodeL<T>* operator->()
        {
            return ptr;
        }

        NodeL<T>* getPtr()
        {
            return ptr;
        }

        Iterator& operator +(unsigned offset)
        {
            NodeL<T>* p = ptr;
            for (int i = 1; i <= offset; i++)
            {
                p = p->next;
            }
            Iterator iterator(p);
            return iterator;
        }

        bool operator==(const Iterator& other) const
        {
            return ptr == other.ptr;
        }
        bool operator!=(const Iterator& other) const
        {
            return ptr != other.ptr;
        }
    };

    LListIter():start(NULL), last(NULL){}
    LListIter(const LListIter& other)
    {
        copy(other);
    }
    ~LListIter()
    {
        destroy();
    }
    LListIter<T>& operator =(const LListIter& other);

    bool empty() const
    {
        return start == NULL;
    }

    void toEnd(const T& element);
    void toStart(const T& element);
    void insertAt(const T& element, unsigned index);
    void insertAfter(const T& element, unsigned index);
    void insertAfterPointed(Iterator it, const T& element);
    void insertAtPointed(Iterator it, const T& element);

    void deleteAt(T& element, unsigned index);

    Iterator begin() const
    {
        return Iterator(start);
    }
    Iterator end() const
    {
        return Iterator(last);
    }

    std::ostream& print(std::ostream& out) const;
    size_t size() const;

    void reverse();
    void sort();
private:
    void copy(const LListIter& other);
    void destroy();
};

template <typename T>
void LListIter<T>::copy(const LListIter& other)
{
    if (other.start != NULL)
    {
        start = new NodeL<T>(other.start->data);
        NodeL<T>* p = other.start->next;
        NodeL<T>* q = start;
        while (p != NULL)
        {
            NodeL<T>* newBox = new NodeL<T>(p->data);
            p = p->next;
            q->next = newBox;
            q = newBox;
        }
        last = q;
        q = NULL;
    }
    else
    {
        start = last = NULL;
    }
}

template <typename T>
void LListIter<T>::destroy()
{
    if (!empty())
    {
        NodeL<T>* p;
        while (start != NULL)
        {
            p = start;
            start = start->next;
            delete p;
        }
        last = NULL;
    }
}

template <typename T>
LListIter<T>& LListIter<T>::operator =(const LListIter& other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

template <typename T>
void LListIter<T>::toEnd(const T& element)
{
    if (empty())
    {
        start = new NodeL<T>(element);
        last = start;
        return;
    }
    NodeL<T>* p = last;
    last = new NodeL<T>(element);
    p->next = last;
    p = NULL;
}

template <typename T>
void LListIter<T>::toStart(const T& element)
{
    NodeL<T>* p = new NodeL<T>(element);
    p->next = start;
    start = p;
    if (start->next == NULL)
    {
        last = start;
    }
    p = NULL;
}

template <typename T>
void LListIter<T>::insertAt(const T& element, unsigned index)
{
    if (index == 0)
    {
        toStart(element);
        return;
    }
    insertAfter(element, index - 1);
}

template <typename T>
void LListIter<T>::insertAfter(const T& element, unsigned index)
{
    if (!empty())
    {
        if (index >= size())
        {
            toEnd(element);
            return;
        }
        NodeL<T>* p = start;
        for (int i = 1; i <= index; i++)
        {
            p = p->next;
        }
        insertAfterPointed(p, element);
        p = NULL;
    }
}

template <typename T>
void LListIter<T>::insertAfterPointed(Iterator it, const T& element)
{
    if (it == end())
    {
        toEnd(element);
        return;
    }
    NodeL<T>* q = new NodeL<T>(element);
    q->next = it->next;
    it->next = q;
    q = NULL;
}

template <typename T>
void LListIter<T>::insertAtPointed(Iterator it, const T& element)
{
    if (it == begin())
    {
        toStart(element);
        return;
    }
    Iterator p = begin();
    while (p->next != it.getPtr())
    {
        p++;
    }
    NodeL<T>* q = new NodeL<T>(element);
    q->next = it->next;
    p->next = q;
    q = NULL;
}

template <typename T>
void LListIter<T>::deleteAt(T& element, unsigned index)
{
    assert(index < size());
    if (!empty())
    {
        NodeL<T>* p;
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
            element = last->data;
            p = last;
            last = start;
            for (int i = 1; i < sizeOfList - 1; i++)
            {
                last = last->next;
            }
            last->next = NULL;
            delete p;
            return;
        }
        p = start;
        for (int i = 1; i < index; i++)
        {
            p = p->next;
        }
        NodeL<T>* q = p->next;
        element = q->data;
        p->next = q->next;
        delete q;
    }
}

template <typename T>
std::ostream& LListIter<T>::print(std::ostream& out) const
{
    if (empty())
    {
        out << "The list is empty!";
        return out;
    }
    NodeL<T>* p = start;
    while (p != NULL)
    {
        out << p->data << " ";
        p = p->next;
    }
    return out;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const LListIter<T>& list)
{
    return list.print(out);
}

template <typename T>
size_t LListIter<T>::size() const
{
    if (empty())
    {
        return 0;
    }
    size_t count = 0;
    NodeL<T>* p = start;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}
template <typename T>
void LListIter<T>::reverse()
{
    LListIter<T> rev;
    Iterator iter = begin();
    while (iter != end())
    {
        rev.toStart(*iter);
        iter++;
    }
    rev.toStart(*iter);
    *this = rev;
}

template <typename T>
void LListIter<T>::sort()
{
    size_t listSize = size();
    for (unsigned i = 0; i < listSize - 1; i++)
    {
        Iterator current = begin() + i;
        Iterator iter = current + 1;
        T min = *current;
        while (iter != end())
        {
            if (*iter < min)
            {
                min = *iter;
                T temp = *current;
                current->data = iter->data;
                iter->data = temp;
            }
            iter++;
        }
        if (*iter < min)
        {
            min = *iter;
            T temp = *current;
            current->data = iter->data;
            iter->data = temp;
        }
    }
}

#endif // LLISTITER_H_INCLUDED
