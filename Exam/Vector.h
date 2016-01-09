#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>
#include <cassert>

const int CAPACITY = 10;

template <typename T>
class Vector
{
    T* arr;
    size_t size;
    size_t capacity;
public:
    Vector(): arr(NULL), size(0), capacity(CAPACITY)
    {
        arr = new T[capacity];
    }
    Vector(const Vector<T>& other): arr(NULL)
    {
        copy(other);
    }
    ~Vector()
    {
        destroy();
    }
    Vector& operator =(const Vector<T>& other);

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

    std::ostream& print(std::ostream& out) const;
private:
    void copy(const Vector<T>& other);
    void destroy();
    void doubleCapacity();
    void reduceCapacity();
};

template <typename T>
void Vector<T>::copy(const Vector<T>& other)
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
void Vector<T>::destroy()
{
    if (arr != NULL)
    {
        delete [] arr;
        arr = NULL;
    }
}

template <typename T>
Vector<T>& Vector<T>::operator =(const Vector<T>& other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

template <typename T>
void Vector<T>::doubleCapacity()
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
void Vector<T>::pushBack(const T& element)
{
    if (size == capacity)
    {
        doubleCapacity();
    }
    arr[size] = element;
    size++;
}

template <typename T>
void Vector<T>::reduceCapacity()
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
void Vector<T>::popBack(T& element)
{
    element = arr[size - 1];
    size--;
    if (size <= capacity/4)
    {
        reduceCapacity();
    }
}

template <typename T>
void Vector<T>::insertAt(const T& element, unsigned index)
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
void Vector<T>::removeFrom(T& element, unsigned index)
{
    assert (index <= size);
    if (index == size - 1)
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
void Vector<T>::clear()
{
    destroy();
    size = 0;
    capacity = CAPACITY;
    arr = new T[capacity];
}

template <typename T>
std::ostream& Vector<T>::print(std::ostream& out) const
{
    if (empty())
    {
        out << "[]";
        return out;
    }
    out << "[";
    for (unsigned i = 0; i < size - 1; i++)
    {
        out << arr[i] << ", ";
    }
    out << arr[size - 1] << "]";
    return out;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const Vector<T>& v)
{
    return v.print(out);
}


#endif // VECTOR_H_INCLUDED
