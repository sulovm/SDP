#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    ofstream fout("new_students.txt");
    if(!fout)
    {
        cerr << "The file cannot be open!\n";
        return 1;
    }
    int fn;
    char name[40];
    double grade;

    while (cin >> fn)
    {
        cin >> name >> grade;
        fout << fn << " " << name << " " << grade << endl;
    }
    return 0;
}
