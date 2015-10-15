#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    ifstream fin("students.txt");
    if (!fin)
    {
        cerr << "The file cannot be open!\n";
        return 1;
    }

    int fn;
    char name[40];
    double grade;

    while (fin >> fn)
    {
        fin >> name >> grade;
        cout << fn << " " << name << " " << grade << endl;
    }

    return 0;
}
