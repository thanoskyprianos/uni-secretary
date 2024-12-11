#ifndef SEMESTER
#define SEMESTER
#include "semester.h"
#endif

using std::endl;

map<Student *, map<Course *, unsigned short>> Semester::passedCourses; // static passed courses

Semester::Semester() { }
Semester::~Semester() { }

Semester &Semester::operator+(Student*s) {
    auto ptr = studentCourseLookup.find(s);
    if (ptr != studentCourseLookup.end())
        throw s;

    studentCourseLookup[s];
    passedCourses[s];

    return *this;
}

Semester &Semester::operator+(Professor *p) {
    auto ptr = professorCourseLookup.find(p);
    if (ptr != professorCourseLookup.end())
        throw p;

    professorCourseLookup[p];

    return *this;
}

Semester &Semester::operator+(Course *c) {
    auto ptr = students.find(c); // check one of two structures
    if (ptr != students.end())
        throw c;

    students[c];
    professors[c];

    return *this;
}

Semester &Semester::operator-(Student *s) {
    auto ptr = studentCourseLookup.find(s);
    if (ptr == studentCourseLookup.end())
        throw s;
    
    studentCourseLookup.erase(s);
    for (auto &ptr : students)
        ptr.second.erase(s);

    passedCourses.erase(s);

    return *this;
}

Semester &Semester::operator-(Professor *p) {
    auto ptr = professorCourseLookup.find(p);
    if (ptr == professorCourseLookup.end())
        throw p;

    professorCourseLookup.erase(p);
    for (auto &ptr : professors)
        ptr.second.erase(p);
    
    return *this;
}

Semester &Semester::operator-(Course *c) {
    auto ptr = students.find(c);
    if (ptr == students.end())
        throw c;

    students.erase(c);
    professors.erase(c);

    for (auto &ptr : studentCourseLookup)
        ptr.second.erase(c);
    
    for (auto &ptr : professorCourseLookup)
        ptr.second.erase(c);

    return *this;
}

bool Semester::hasCourse(Course *c) { return students.find(c) != students.end(); }
bool Semester::hasCourse(Course *c, Student *s) { return studentCourseLookup[s].find(c) != studentCourseLookup[s].end(); }
bool Semester::hasCourse(Course *c, Professor *p) { return professorCourseLookup[p].find(c) != professorCourseLookup[p].end(); }

bool Semester::hasPassedCourse(Course *c, Student *s) { return passedCourses[s].find(c) != passedCourses[s].end(); }

void Semester::registerGrade(Course *c, Student *s, unsigned short grade) {
    auto ptr = students.find(c);
    if (ptr == students.end())
        throw c; // c not in semester

    students[c][s] = grade;
    studentCourseLookup[s].insert(c);
}

void Semester::assignProfessor(Course *c, Professor *p) {
    auto ptr = professors.find(c);
    if (ptr == professors.end())
        throw c; // c not in semester

    professors[c].insert(p);
    professorCourseLookup[p].insert(c);
}

unsigned short Semester::getGrade(Course *c, Student *s) const {
    auto ptr1 = students.find(c);
    if (ptr1 == students.end())
        throw c;  // c not in semester

    auto ptr2 = students.at((*ptr1).first).find(s);
    if (ptr2 == students.at((*ptr1).first).end())
        throw s;  // s does not attend c

    return (*ptr2).second;
}

void Semester::finalize() {
    for (const auto &p : studentCourseLookup) {
        for (const auto &c : p.second) {
            if (students[c][p.first] >= 5) {
                passedCourses[p.first][c] = students[c][p.first];

                p.first->setECTS(p.first->getECTS() + c->getECTS()); // increase ECTS if passed
            }
        }

        p.first->setSemester(p.first->getSemester() + 1);   // increment student semester
    }
}

ostream& operator<<(ostream &str, const Semester &s) {
    for (const auto &p : s.students) {
        str << p.first->getName() << ":" << endl
        
            << "PROFESSORS: " << endl;
        for (const auto &q : s.professors.at(p.first))
            str << '\t' << *q << endl;
        
        str << "STUDENTS: " << endl;
        for (const auto &q : p.second)
            str << '\t' << *(q.first) << " -> " << q.second << endl;
    }

    return str;
}