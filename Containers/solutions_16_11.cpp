/*
Зад. 1:
Да се напише програма, която създава вектор от приоритетни опашки от цели числа (int или unsigned). Въвеждат се числа, като
всяко число х се записва в опашката, намираща се на индекс x/10 във вектора (Може предварително да се въведе брой числа или
да се въвеждат до Ctrl + Z, решенията по-долу използват втория вариант). Програмата да извежда всяка от опашките и най-големите
числа във всеки от интервалите [10*i, 10*i + 9], където i е валиден индекс на вектора, като:
    а) предварително е зададен размер на вектора FIXED_SIZE, т.е. числа, >= FIXED_SIZE * 10, не участват;
    б) размерът на вектора може да бъде произволен (т.е. при необходимост да се преоразмерява).

Зад. 2:
На същия вектор да се сортират елементите по брой числа в съответната опашка, като се използва ф-ята sort() на класа
VectorIter и се дефинира оператор < в класа PriorityQueue.

ВАЖНО!!! Хедърите трябва да са в същата директория, в която е и този файл, за да тръгне. Най-сигурно -
проект с нужните хедъри в него и съдържанието на този файл да се копира в main файла му.
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
В хедъра PriorityQueue.h (за втора зад.):

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
