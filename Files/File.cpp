#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

struct Student
{
    unsigned fn;
    char name[40];
    float grade;

    Student (unsigned f = 0, char* n = "", float g = 0.00)
    {
        fn = f;
        strcpy(name, n);
        grade = g;
    }

    Student (const Student& other)
    {
        fn = other.fn;
        strcpy(name, other.name);
        grade = other.grade;
    }

    Student& operator =(const Student& other)
    {
        if (this != &other)
        {
            fn = other.fn;
            strcpy(name, other.name);
            grade = other.grade;
        }
        return *this;
    }

    bool operator >(const Student& other) const
    {
        return grade > other.grade;
    }
};

ostream& operator <<(ostream& out, const Student& student)
{
    out << student.fn << " " << student.name << " " << setprecision(2) << fixed << student.grade << endl;
}

int main()
{
    Student students[100];

    fstream f("txt_students.txt", ios::in|ios::out);
    if (!f)
    {
        cerr << "The file cannot be open!\n";
        return 1;
    }

    unsigned n = 0;
    unsigned fn;
    while (f >> fn)
    {
        students[n].fn = fn;
        f.getline(students[n].name, 39);
        f >> students[n].grade;
        n++;
    }

    for (unsigned i = 0; i < n - 1; i++)
    {
        Student max = students[i];
        unsigned k = i;
        for (unsigned j = i + 1; j < n; j++)
        {
            if (students[j] > max)
            {
                max = students[j];
                k = j;
            }
        }
        max = students[i];
        students[i] = students[k];
        students[k] = max;
    }

    f.clear();
    f.seekp(ios::beg);
    for (unsigned i = 0; i < n; i++)
    {
        f << students[i];
    }

    return 0;
}
