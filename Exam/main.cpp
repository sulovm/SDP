#include <iostream>

#include "StackQueue.h"
#include "LListIter.h"
#include "Vector.h"
using namespace std;

int main()
{
    StackQueue<int> sq;
    cout << sq << endl; //empty
    sq.push(5);
    cout << sq << endl; //5
    sq.push(11);
    cout << sq << endl; //5 11
    sq.push(2);
    cout << sq << endl; //5 11 2

    int removed;
    sq.pop(removed);
    cout << "Removed: " << removed << endl; //5
    cout << sq << endl; //11 2

    sq.push(16);
    cout << sq << endl; //11 2 16
    sq.push(22);
    cout << sq << endl; //11 2 16 22

    StackQueue<int> sqq = sq;

    cout << "Front: " << sq.getFront() << endl; //11
    cout << sq << endl; //11 2 16 22

    sq.pop(removed);
    sq.pop(removed);
    cout << "Removed: " << removed << endl; //2

    cout << sq << endl; //16 22

    cout << "Front: " << sq.getFront() << endl; //16
    cout << sq << endl; //16 22

    sq.push(3);
    cout << sq << endl; //16 22 3
    cout << boolalpha << sq.isEmpty() << endl; //false

    cout << "=================================================\n";

    StackQueue<int> sq1;
    sq1.push(1);
    sq1.push(2);
    sq1.push(3);
    sq1.push(4);
    cout << sq1 << endl; //1 2 3 4

    StackQueue<int> sq2;
    sq2.push(100);
    sq2.push(234);
    cout << sq2 << endl; //100 234

    sqq.push(54);
    cout << sqq << endl; //11 2 16 22 54

    LListIter <StackQueue <int> > lsq;
    lsq.toEnd(sq);
    lsq.toEnd(sq1);
    lsq.toEnd(sq2);
    lsq.toEnd(sqq);
    cout << lsq << endl;
    lsq.sort();
    cout << lsq << endl;

    Vector<int> v;
    for (int i = 0; i < lsq.size(); i++)
    {
        v.pushBack((*(lsq.begin() + i)).getFront());
    }
    cout << v << endl;

    return 0;
}
