/*
���. 1:
�� �� ������ ��������, ����� ������� ������ �� ����������� ������ �� ���� ����� (int ��� unsigned). �������� �� �����, ����
����� ����� � �� ������� � ��������, �������� �� �� ������ x/10 ��� ������� (���� ������������� �� �� ������ ���� ����� ���
�� �� �������� �� Ctrl + Z, ��������� ��-���� ��������� ������ �������). ���������� �� ������� ����� �� �������� � ���-��������
����� ��� ����� �� ����������� [10*i, 10*i + 9], ������ i � ������� ������ �� �������, ����:
    �) ������������� � ������� ������ �� ������� FIXED_SIZE, �.�. �����, >= FIXED_SIZE * 10, �� ��������;
    �) �������� �� ������� ���� �� ���� ���������� (�.�. ��� ������������ �� �� �������������).

���. 2:
�� ����� ������ �� �� �������� ���������� �� ���� ����� � ����������� ������, ���� �� �������� �-��� sort() �� �����
VectorIter � �� �������� �������� < � ����� PriorityQueue.

�����!!! �������� ������ �� �� � ������ ����������, � ����� � � ���� ����, �� �� ������. ���-������� -
������ � ������� ������ � ���� � ������������ �� ���� ���� �� �� ������ � main ����� ��.
*/


#include <iostream>
#include "PriorityQueue.h"
#include "VectorIter.h"
using namespace std;

const int FIXED_SIZE = 20;

void problem1_fixed_size()
{
    VectorIter <PriorityQueue <unsigned> > vpq;
    for (int i = 0; i < FIXED_SIZE; i++)
    {
        vpq.pushBack(PriorityQueue<unsigned> ());
    }
    unsigned x;
    cout << "Enter integer numbers belonging to [0; " << FIXED_SIZE*10 << "] until entering of Ctrl + Z:\n";
    while (cin >> x)
    {
        if (x < FIXED_SIZE * 10)
        {
            vpq[x/10].push(x);
        }
    }
    for (int i = 0; i < FIXED_SIZE; i++)
    {
        cout << vpq[i];
        if (!vpq[i].isEmpty())
        {
            cout << "The greatest number belonging to [" << i*10 << ", " << i*10 + 9 << "]: "
                 << vpq[i].top() << endl;
        }
        cout << "=============================================\n\n";
    }
}

//================================================================================================

void problem1_dynamic_size()
{
    VectorIter <PriorityQueue <unsigned> > vpq;
    unsigned x;
    cout << "Enter non-negative integer numbers until entering of Ctrl + Z:\n";
    while (cin >> x)
    {
        while (vpq.getSize() <= x/10)
        {
            vpq.pushBack(PriorityQueue<unsigned> ());
        }
        vpq[x/10].push(x);
    }
    for (int i = 0; i < vpq.getSize(); i++)
    {
        cout << vpq[i];
        if (!vpq[i].isEmpty())
        {
            cout << "The greatest number belonging to [" << i*10 << ", " << i*10 + 9 << "]: "
                 << vpq[i].top() << endl;
        }
        cout << "=============================================\n\n";
    }
}

//=========================================================================================

void problem2()
{
    VectorIter <PriorityQueue <unsigned> > vpq;
    unsigned x;
    cout << "Enter non-negative integer numbers until entering of Ctrl + Z:\n";
    while (cin >> x)
    {
        while (vpq.getSize() <= x/10)
        {
            vpq.pushBack(PriorityQueue<unsigned> ());
        }
        vpq[x/10].push(x);
    }

    for (int i = 0; i < vpq.getSize(); i++)
    {
        cout << vpq[i];
    }
    cout << "=======================================================\n";

    vpq.sort();

    for (int i = 0; i < vpq.getSize(); i++)
    {
        cout << vpq[i];
    }
}

int main()
{
    //problem1_fixed_size();
    //problem1_dynamic_size();
    problem2();

    return 0;
}

/*
� ������ PriorityQueue.h (�� ����� ���.):

...
class PriorityQueue
{
    ...
public:
    ...
    bool operator < (const PriorityQueue<T>& other) const
    {
        return getSize() < other.getSize();
    }
    ...
};
...
*/
