#include <iostream>
#include <fstream>
using namespace std;

struct StudentData
{
    int fn; //1000 - 100 000
    char name[100];
};

struct SubjectData
{
    int code; //0 - 200
    char name[100];
    char teacher[100];
};

struct GradeData
{
    int studentFn, subjectCode;
    int d, m, y;
    double value;
};

void createStudents()
{
    ifstream inpStud ("students.txt");
    ofstream outpStud ("students.bin", ios::binary);

    StudentData student;

    while (inpStud >> student.fn)
    {
        inpStud.getline (student.name, 100);
        cout << "Read student: " << student.name << endl;
        outpStud.seekp ((student.fn - 1000) * sizeof (StudentData));
        outpStud.write ((char*)&student, sizeof (StudentData));
    }
}

void createSubjects()
{
    ifstream inpSubj ("subjects.txt");
    ofstream outpSubj ("subjects.bin", ios::binary);

    SubjectData subject;

    while (inpSubj >> subject.code)
    {
        inpSubj.getline (subject.name, 100);
        inpSubj.getline (subject.teacher, 100);
        cout << "Read subject: " << subject.name << endl;
        outpSubj.seekp ((subject.code) * sizeof (SubjectData));
        outpSubj.write ((char*)&subject, sizeof (SubjectData));
    }
}

void createGrade()
{
    ifstream inp ("grades.txt");
    ofstream outp ("grades.bin", ios::binary);

    GradeData gr;

    while (inp >> gr.studentFn)
    {
        inp >> gr.subjectCode >> gr.d >> gr.m >> gr.y >> gr.value;
        cout << "Read grade of " << gr.studentFn << endl;
        outp.seekp ((gr.studentFn) * sizeof (GradeData));
        outp.write ((char*)&gr, sizeof (GradeData));
    }
}

int main ()
{
    createStudents();
    createSubjects();
    createGrade();

    //system ("pause");
    return 0;
}

//stranxter - gitHub
