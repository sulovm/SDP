#include <iostream>
#include <cassert>
#include "LList.h"
using namespace std;

template <class T>
class Graph
{
    LList <LList <T> > g;
public:
    void addTop (const T& x)
    {
        LList<T> empty;
        empty.ToEnd (x);
        g.ToEnd (empty);
    }
    elem_link1<T>* point (const T& x)
    {
        g.IterStart();
        elem_link1<LList <T> > *p;
        elem_link1<T> *q;
        do
        {
            p = g.Iter();
            p -> inf.IterStart();
            q = p -> inf.Iter();
        }
        while (q -> inf != x);
        return q;
    }

    void addRib (const T& x, const T& y)
    {
        elem_link1 <T> *p = point(x), *q;
        q = new elem_link1<T>;
        assert (p != NULL);
        q -> inf = y;
        q -> link = p -> link;
        p -> link = q;
    }

    bool rib (const T& x, const T& y)
    {
        elem_link1 <T> *p = point(x);
        do
        {
            p = p -> link;
        }
        while (p -> inf != y && p);

        return p != NULL;
    }

    void print()
    {
        g.IterStart();
        elem_link1 <LList <T> >* p = g.Iter();
        do
        {
            //p -> inf.IterStart();
            //cout << p -> inf.Iter() -> inf << ": ";
            p -> inf.print();
            p = p -> link;
        }
        while (p);
    }
};

int main()
{
    Graph<int> gr;
    gr.addTop (1);
    gr.addTop (2);
    gr.addTop (3);
    gr.addTop (4);

    gr.addRib (1, 2);
    gr.addRib (4, 2);
    gr.addRib (3, 4);
    gr.addRib (3, 1);
    gr.addRib (3, 2);
    gr.addRib (1, 4);

    gr.print();

    //cout << boolalpha << gr.rib (4, 2) << " " << gr.rib (4, 1) << endl; //true false

    //gr.print();
    return 0;
}
