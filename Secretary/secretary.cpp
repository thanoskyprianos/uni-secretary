#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef INIT_LIST
#define INIT_LIST
#include <initializer_list>
#endif

#ifndef MAP
#define MAP
#include <map>
#endif

#ifndef SECRETARY
#define SECRETARY
#include "secretary.h"
#endif

#ifndef COURSE
#define COURSE
#include "../Course/course.h"
#endif

#ifndef SEMESTER
#define SEMESTER
#include "../Semester/semester.h"
#endif

#ifndef UTIL
#define UTIL
#include "../Util/util.h"
#endif

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

using std::initializer_list;

unsigned short Secretary::YEARS;
unsigned short Secretary::ECTS;

Secretary::Secretary() { }

Secretary::~Secretary() {
    for (auto &p : studentsById)
        delete p.second;

    for (auto &p : professorsById)
        delete p.second;

    for (auto &p : coursesById)
        delete p.second;

    for (auto &p : semesters)
        delete p;
}

Student *Secretary::findStudentById(const string &id) const {
    auto ptr = studentsById.find(id);

    if (ptr == studentsById.end())
        throw id;  // no Student with id: id

    return ptr->second;
}


Professor *Secretary::findProfessorById(const string &id) const {
    auto ptr = professorsById.find(id);

    if (ptr == professorsById.end())
        throw id;  // no Professor with id: id

    return ptr->second;
}

Course *Secretary::findCourseById(const string &id) const {
    auto ptr = coursesById.find(id);

    if (ptr == coursesById.end())
        throw id; // no Course with id: id

    return ptr->second;
}

const set<Student *> *Secretary::findStudentByName(const string &name) const {
    auto ptr = studentsByName.find(name);

    if (ptr == studentsByName.end())
        throw name;  // no Student with name: name

    return &(ptr->second);
}

const set<Professor *> *Secretary::findProfessorByName(const string &name) const {
    auto ptr = professorsByName.find(name);

    if (ptr == professorsByName.end())
        throw name;  // no Professor with name: name

    return &(ptr->second);
}

void Secretary::updateData(const string &oldName, Student *s) {    
    studentsByName[oldName].erase(s);
    if (studentsByName[oldName].empty())  // no more Students with name: oldName
        studentsByName.erase(oldName);

    studentsByName[s->getName()].insert(s);
}

void Secretary::updateData(const string &oldName, Professor *p) {
    professorsByName[oldName].erase(p);
    if (professorsByName[oldName].empty())  // no more Professors with name: oldName
        professorsByName.erase(oldName);

    professorsByName[p->getName()].insert(p);
}

Semester *Secretary::currentSemester() {
    return semesters.back();
}

const Semester *Secretary::semesterAt(std::size_t index) const {
    if (index > semesters.size() - 1)
        throw index;

    return semesters[index];
}

set<Student *> Secretary::getStudents() const
{ return util::mapToSet<Student>(studentsById); }

set<Professor *> Secretary::getProfessors() const 
{ return util::mapToSet<Professor>(professorsById); }

set<Course *> Secretary::getCourses() const
{ return util::mapToSet<Course>(coursesById); }

void Secretary::nextSemester() {
    if (!semesters.empty())
        semesters.back()->finalize();       // finalize grades

    semesters.push_back(new Semester {});   // create new semester

    // add all Student, Professor, Course pointers to new Semester

    for (const auto &p : coursesById) {
        if (((p.second)->getSemester() % 2 == semesters.size() % 2))
            *semesters.back() + p.second;
    }

    for (const auto &p : studentsById)
        *semesters.back() + p.second;

    for (const auto &p : professorsById)
        *semesters.back() + p.second;
}

int Secretary::semesterCount() const { return semesters.size(); }

Secretary &Secretary::operator+(const Student &s) {
    try {
        findStudentById(s.getId()); // check if exists
        throw s;                    // already exists, throw
    } catch (string) {
        studentsById[s.getId()] = new Student(s);
        studentsByName[s.getName()].insert(studentsById[s.getId()]);

        if (!semesters.empty())
            *semesters.back() + studentsById[s.getId()];
    }

    return *this;
}

Secretary &Secretary::operator+(const Professor &p) {
    try {
        findProfessorById(p.getId()); // check if exists, if not add
        throw p;                      // already exists, throw
    } catch(string) {
        professorsById[p.getId()] = new Professor(p);
        professorsByName[p.getName()].insert(professorsById[p.getId()]);

        if (!semesters.empty())
            *semesters.back() + professorsById[p.getId()];
    }

    return *this;
}

Secretary &Secretary::operator+(const Course &c) {
    try {
        findCourseById(c.getId()); // check if exists, if not add
        throw c;                   // already exists, throw
    } catch(string) {
        coursesById[c.getId()] = new Course(c);

        if (!semesters.empty())
            *semesters.back() + coursesById[c.getId()];
    }

    return *this;
}

Secretary &Secretary::operator-(const Student &s) {
    auto ptr = findStudentById(s.getId());
    studentsById.erase(s.getId());
    studentsByName[s.getName()].erase(ptr);

    if (studentsByName[s.getName()].empty())
        studentsByName.erase(s.getName());

    if (!semesters.empty())
        *semesters.back() - ptr;

    delete ptr;

    return *this;
}

Secretary &Secretary::operator-(const Professor &p) {
    auto ptr = findProfessorById(p.getId());
    professorsById.erase(p.getId());
    professorsByName[p.getName()].erase(ptr);

    if (professorsByName[p.getName()].empty())
        professorsByName.erase(p.getName());

    if (!semesters.empty())
        *semesters.back() - ptr;

    delete ptr;

    return *this;
}

Secretary &Secretary::operator-(const Course &c) {
    auto ptr = findCourseById(c.getId());
    coursesById.erase(c.getId());

    if (!semesters.empty())
        *semesters.back() - ptr;

    delete ptr;

    return *this;
}

ostream &operator<<(ostream &str, const Secretary &secretary) {
    str << "---STUDENTS---" << endl;
    for (const auto &p : secretary.studentsById)
        str << *p.second << endl;

    str << "---PROFESSORS---" << endl;
    for (const auto &p : secretary.professorsById)
        str << *p.second << endl;

    str << "---COURSES---" << endl;
    for (const auto &p : secretary.coursesById)
        str << *p.second << endl;

    return str;
}

void Secretary::printStudents(ostream &str) const {
    util::mapPrint(str, studentsById);
}

void Secretary::printProfessors(ostream &str) const {
    util::mapPrint(str, professorsById);
}

void Secretary::printCourses(ostream &str) const {
    util::mapPrint(str, coursesById);
}

set<string> Secretary::studentsToCSV() const {
    return util::DataToCSV(studentsById);
}

set<string> Secretary::professorsToCSV() const {
    return util::DataToCSV(professorsById);
}

set<string> Secretary::coursesToCSV() const {
    return util::DataToCSV(coursesById);
}