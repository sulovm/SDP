#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

const unsigned N = 1000;

struct Student
{
    unsigned fn;
    char name[39];
    float grade;

    Student(unsigned f = 0, const char* n = "", float g = 0.00)
    {
        strcpy(name, n);
        fn = f;
        grade = g;
    }
};

ostream& operator <<(ostream& out, const Student& student)
{
    out << student.fn << " " << student.name << " " << setprecision(2) << fixed << student.grade << endl;
}

void addStudent (fstream& f, const Student& student)
{
    if(student.fn >= 80000 && student.fn <= 80000 + N)
    {
        f.seekp((student.fn - 80000) * sizeof(Student));
        f.write((const char*) &student, sizeof(Student));
    }
}


void removeStudent (fstream& f, unsigned facNum)
{
    Student student;
    if(facNum >= 80000 && facNum <= 80000 + N)
    {
        f.seekp((facNum - 80000) * sizeof(Student));
        f.write((const char*) &student, sizeof(Student));
    }
}

void setStudent (fstream& f, unsigned facNum, const char* name, float grade)
{
    Student student(facNum, name, grade);
    addStudent(f, student);
}

void printStudents(fstream& f)
{
    for (int i = 0; i < N; i++)
    {
        Student student;
        f.seekg(i * sizeof(Student));
        f.read ((char*)&student, sizeof(Student));
        if (student.fn != 0)
        {
            cout << student;
        }
    }
}

int main()
{
    fstream f("bin_students.bin");

    if (!f)
    {
        cerr << "The file cannot be open!\n";
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        Student student;
        f.seekg(i*sizeof(Student));
        f.write((char*)&student, sizeof(Student));
    }


    addStudent(f, Student(80963, "Momchil Sulov", 5.24));
    addStudent(f, Student(80974, "Dragan Ivanov", 5.73));
    addStudent(f, Student(80955, "Ivan Draganov", 3.45));
    addStudent(f, Student(80056, "Petkan Petkanov", 4.65));
    addStudent(f, Student(84567, "Matthias Jabs", 6.00));
    printStudents(f);
    cout << "\n\n===================================================\n\n";

    setStudent(f, 80567, "Rudolf Schenker", 5.08);
    printStudents(f);
    cout << "\n\n===================================================\n\n";

    setStudent(f, 80974, "Klaus Meine", 5.73);
    printStudents(f);
    cout << "\n\n===================================================\n\n";

    removeStudent(f, 80955);
    printStudents(f);

    system("pause");

    return 0;
}
