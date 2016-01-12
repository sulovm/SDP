#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
struct Node
{
    T inf;
    Node<T>* next;
};

template <typename T>
class CyclicList
{
    Node<T>* start;

public:
    class Iterator
    {
        Node<T>* ptr;

    public:
        Iterator() : ptr(0) {}
        Iterator(Node<T>* newPtr) : ptr (newPtr) {}

        Iterator& operator ++()
        {
            ptr = ptr -> next;
            return *this;
        }

        Iterator& operator ++ (T n)
        {
            Iterator res (ptr);
            ptr = ptr -> next;
            return res;
        }

        T operator * () {return ptr -> inf;}
        T* operator -> () {return ptr;}

        bool operator == (const Iterator& other) const
        {
            return ptr == other.ptr;
        }

        bool operator != (const Iterator& other) const
        {
            return ptr != other.ptr;
        }
    };

    CyclicList():start(NULL)
    {
        start = NULL;
    }
    CyclicList (const CyclicList<T>& other):start(NULL)
    {
        copy(other);
    }
    ~CyclicList()
    {
        destroy();
    }
    CyclicList<T>& operator = (const CyclicList<T>& other);

    void insertAtStart (const T&);
    void insertAtEnd (const T&);
    void insertAt (unsigned, const T&);
    T removeFromStart();
    T removeFromEnd();
    T removeFrom(unsigned);
    void remove (const T&);
    bool isMember (const T&) const;
    size_t size() const;

    Iterator begin()
    {
        return Iterator (start);
    }

    Iterator end()
    {
        Iterator iter (start);
        while (iter.prt -> next != start) iter++;
        return iter;
    }

    ostream& print(ostream& out) const;

private:
    void copy (const CyclicList<T>& other);
    void destroy();
};

template <typename T>
CyclicList<T>& CyclicList<T>:: operator = (const CyclicList<T>& other)
{
     if (this != &other)
     {
           destroy();
           copy(other);
     }
     return *this;
}

template <typename T>
void CyclicList<T>::copy (const CyclicList<T>& other)
{
     assert (start == NULL);
     insertAtStart (other.start -> inf);
     Node<T>* p = other.start -> next;
     while (p != other.start)
     {
           insertAtEnd (p -> inf);
           p = p -> next;
     }
}

template <typename T>
void CyclicList<T>::destroy()
{
     if (start != NULL)
     {
           Node<T>* p = start -> next;
           while (p != start)
           {
                Node<T>* r = p;
                p = p -> next;
                delete r;
           }
           p = NULL;
           delete start;
           start = NULL;
     }
}

template <typename T>
void CyclicList<T>::insertAtStart (const T& data)
{
    if (start == NULL)
    {
        start = new Node<T>;
        assert (start != NULL);
        start -> inf = data;
        start -> next = start;
        return;
    }
    Node<T>* s = new Node<T>;
    s -> next = start -> next;
    s -> inf = start -> inf;
    start -> next = s;
    start -> inf = data;
}

template <typename T>
void CyclicList<T>::insertAtEnd (const T& data)
{
    if (start == NULL)
    {
        start = new Node<T>;
        assert (start != NULL);
        start -> inf = data;
        start -> next = start;
        return;
    }
    Node<T>* p = start -> next;
    while (p -> next != start)
        p = p -> next;
    Node<T>* s = new Node<T>;
    assert (s != NULL);
    s -> next = start;
    p -> next = s;
    s -> inf = data;
}

template <typename T>
void CyclicList<T>::insertAt(unsigned index, const T& data)
{
    if (start == NULL || index == 0)
    {
        insertAtStart(data);
        return;
    }
    if (index >= size())
    {
        insertAtEnd(data);
        return;
    }
    Node<T>* p = start;
    for (int i = 0; i < index - 1; i++)
    {
        p = p->next;
    }
    Node<T>* newBox = new Node<T>;
    newBox->inf = data;
    newBox->next = p->next;
    p->next = newBox;
}

template <typename T>
T CyclicList<T>::removeFromStart()
{
    if (start != NULL)
    {
        Node<T>* r = start;
        Node<T>* p = start -> next;
        while (p -> next != start)
            p = p -> next;
        start = start -> next;
        p -> next = start;
        T removed = r -> inf;
        delete r;
        return removed;
    }
}

template <typename T>
T CyclicList<T>::removeFromEnd()
{
    if (start != NULL)
    {
        if (start -> next == start)
        {
            T removed = start -> inf;
            delete start;
            return removed;
        }
        Node<T>* p = start -> next;
        while (p -> next -> next != start)
            p = p -> next;
        Node<T>* r = p -> next;
        assert (r -> next == start);
        p -> next = start;
        T removed = r -> inf;
        delete r;
        return removed;
    }
}

template <typename T>
T CyclicList<T>::removeFrom(unsigned index)
{
    if (start != NULL)
    {
        if (index == 0)
        {
            return removeFromStart();
        }
        if (index >= size() - 1)
        {
            return removeFromEnd();
        }
        Node<T>* p = start;
        for (int i = 0; i < index - 1; i++)
        {
            p = p->next;
        }
        Node<T>* r = p->next;
        p->next = r->next;
        T removed = r->inf;
        delete r;
        return removed;
    }
}

template <typename T>
void CyclicList<T>::remove (const T& what)
{
    if (start != NULL)
    {
        if (start -> inf == what)
        {
            removeFromStart();
            return;
        }
        Node<T>* p = start -> next;
        while (p != start && p -> next -> inf != what)
            p = p -> next;
        if (p == start)
        {
            cout << "There's no such element - " << what << "!\n";
            return;
        }
        Node<T>* r = p -> next;
        p -> next = p -> next -> next;
        delete r;
    }
}

template <typename T>
bool CyclicList<T>::isMember(const T& what) const
{
    if (start == NULL) return false;
    if (start -> inf == what) return true;
    Node<T>* p = start -> next;
    while (p != start && p -> inf != what)
        p = p -> next;
    if (p == start) return false;
    return true;
}

template <typename T>
size_t CyclicList<T>::size() const
{
    if (start == 0)
    {
        return 0;
    }
    size_t count = 1;
    Node<T>* p = start ->next;
    while (p != start)
    {
        p = p->next;
        count++;
    }
    return count;
}

template <typename T>
ostream& CyclicList<T>::print(ostream& out) const
{
    if (start != NULL)
    {
        out << start -> inf << " ";
        Node<T>* p = start -> next;
        while (p != start)
        {
            out << p -> inf << " ";
            p = p -> next;
        }
    }
    out << endl;
    return out;
}

template <typename T>
ostream& operator << (ostream& out, const CyclicList<T>& list)
{
    list.print(out);
    return out;
}

int main ()
{
    CyclicList<int> cl;
    cl.insertAtStart (2);
    cout << cl;
    cl.insertAtStart (4);
    cout << cl;
    cl.insertAtStart (8);
    cout << cl;
    cl.insertAtEnd (10);
    cout << cl;
    cl.insertAtEnd (20);
    cout << cl;
    //8, 4, 2, 10, 20

    cl.insertAt (2, 25);
    cout << cl;
    //8, 4, 25, 2, 10, 20

    cout << "================================================================\n";
    CyclicList<int> lst = cl;
    cout << lst;
    cout << boolalpha << lst.isMember(10) << endl;
    cout << boolalpha << lst.isMember(15) << endl;
    cout << "Removed: " << lst.removeFromStart() << endl;
    cout << lst;
    cout << "Removed: " << lst.removeFromEnd() << endl;
    cout << lst;

    cout << "Removed: " << lst.removeFrom(2) << endl;
    cout << lst;

    cout << "=================================================================\n";
    lst = cl;
    cout << lst;
    cout << "Size: " << lst.size() << endl;
    lst.remove (8);
    cout << lst;
    lst.remove (16);
    cout << lst;

    return 0;
}
