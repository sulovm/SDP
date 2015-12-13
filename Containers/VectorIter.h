#ifndef VECTORITER_H_INCLUDED
#define VECTORITER_H_INCLUDED

#include <iostream>
#include <cassert>

const int CAPACITY = 10;

template <typename T>
class VectorIter
{
    T* arr;
    size_t size;
    size_t capacity;
public:
    class Iterator
    {
        T* ptr;
    public:
        Iterator(): ptr(NULL) {}

        Iterator(T* p) : ptr(p) {}

        Iterator operator++()
        {
            ptr++;
            return *this;
        }
        Iterator operator++(int junk)
        {
            Iterator result (ptr);
            ptr++;
            return result;
        }
        T& operator*()
        {
            return *ptr;
        }
        T* operator->()
        {
            return ptr;
        }

        Iterator& operator +(unsigned offset)
        {
            T* p = ptr;
            for (int i = 1; i <= offset; i++)
            {
                p++;
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

    VectorIter(): arr(NULL), size(0), capacity(CAPACITY)
    {
        arr = new T[capacity];
    }
    VectorIter(const VectorIter<T>& other): arr(NULL)
    {
        copy(other);
    }
    ~VectorIter()
    {
        destroy();
    }
    VectorIter& operator =(const VectorIter<T>& other);

    size_t getSize() const
    {
        return size;
    }
    size_t getCapacity() const
    {
        return capacity;
    }
    bool empty() const
    {
        return size == 0;
    }
    T& operator [](unsigned index)
    {
        return arr[index];
    }
    T operator [](unsigned index) const
    {
        return arr[index];
    }

    void pushBack(const T& element);
    void popBack(T& element);
    void insertAt(const T& element, unsigned index);
    void removeFrom(T& element, unsigned index);
    void clear();

    Iterator begin() const
    {
        return Iterator(arr);
    }
    Iterator end() const
    {
        return Iterator(arr + size - 1);
    }

    std::ostream& print(std::ostream& out) const;

    void reverse();
    void sort();
private:
    void copy(const VectorIter<T>& other);
    void destroy();
    void doubleCapacity();
    void reduceCapacity();
};

template <typename T>
void VectorIter<T>::copy(const VectorIter<T>& other)
{
    size = other.size;
    capacity = other.capacity;
    assert (size <= capacity);
    arr = new T[capacity];
    assert (arr != NULL);
    for (unsigned i = 0; i < size; i++)
    {
        arr[i] = other.arr[i];
    }
}

template <typename T>
void VectorIter<T>::destroy()
{
    if (arr != NULL)
    {
        delete [] arr;
        arr = NULL;
    }
}

template <typename T>
VectorIter<T>& VectorIter<T>::operator =(const VectorIter<T>& other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

template <typename T>
void VectorIter<T>::doubleCapacity()
{
    capacity *= 2;
    T* newArr = new T[capacity];
    assert (newArr != NULL);
    for (unsigned i = 0; i < size; i++)
    {
        newArr[i] = arr[i];
    }
    delete [] arr;
    arr = newArr;
    newArr = NULL;
}

template <typename T>
void VectorIter<T>::pushBack(const T& element)
{
    if (size == capacity)
    {
        doubleCapacity();
    }
    arr[size] = element;
    size++;
}

template <typename T>
void VectorIter<T>::reduceCapacity()
{
    assert (size <= capacity/4);
    capacity /= 2;
    T* newArr = new T[capacity];
    assert (newArr != NULL);
    for (unsigned i = 0; i < size; i++)
    {
        newArr[i] = arr[i];
    }
    delete [] arr;
    arr = newArr;
    newArr = NULL;
}

template <typename T>
void VectorIter<T>::popBack(T& element)
{
    element = arr[size - 1];
    size--;
    if (size <= capacity/4)
    {
        reduceCapacity();
    }
}

template <typename T>
void VectorIter<T>::insertAt(const T& element, unsigned index)
{
    assert (index <= size);
    if (size == capacity)
    {
        doubleCapacity();
    }
    if (index == size)
    {
        pushBack(element);
        return;
    }
    for (unsigned i = size; i > index; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[index] = element;
    size++;
}

template <typename T>
void VectorIter<T>::removeFrom(T& element, unsigned index)
{
    assert (index <= size);
    if (index == size)
    {
        popBack(element);
        return;
    }
    element = arr[index];
    for (unsigned i = index; i < size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    size--;
    if (size <= capacity/4)
    {
        reduceCapacity();
    }
}

template <typename T>
void VectorIter<T>::clear()
{
    destroy();
    size = 0;
    capacity = CAPACITY;
    arr = new T[capacity];
}

template <typename T>
std::ostream& VectorIter<T>::print(std::ostream& out) const
{
    if (empty())
    {
        std::cout << "[]";
        return out;
    }
    std::cout << "[";
    for (unsigned i = 0; i < size - 1; i++)
    {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[size - 1] << "]";
    return out;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const VectorIter<T> v)
{
    return v.print(out);
}

template <typename T>
void VectorIter<T>::reverse()
{
    VectorIter<T> rev;
    Iterator iter = begin();
    while (iter != end())
    {
        rev.insertAt(*iter, 0);
        iter++;
    }
    rev.insertAt(*iter, 0);
    *this = rev;
}

template <typename T>
void VectorIter<T>::sort()
{
    for (unsigned i = 0; i < size - 1; i++)
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
                *current = *iter;
                *iter = temp;
            }
            iter++;
        }
        if (*iter < min)
        {
            min = *iter;
            T temp = *current;
            *current = *iter;
            *iter = temp;
        }
    }
}



#endif // VECTORITER_H_INCLUDED
