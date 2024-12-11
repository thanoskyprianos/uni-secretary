#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef SET
#define SET
#include <set>
#endif

#ifndef INIT_LIST
#define INIT_LIST
#include <initializer_list>
#endif

#ifndef MAP
#define MAP
#include <map>
#endif

#ifndef PERSON
#define PERSON
#include "../Person/person.h"
#endif

#ifndef COURSE
#define COURSE
#include "../Course/course.h"
#endif

#ifndef SEMESTER
#define SEMESTER
#include "../Semester/semester.h"
#endif

using std::vector;
using std::set;
using std::initializer_list;
using std::map;

using std::ostream;
using std::istream;

class Secretary {
private:
    map<string, Student *> studentsById;
    map<string, set<Student *>> studentsByName;

    map<string, Professor *> professorsById;
    map<string, set<Professor *>> professorsByName;

    map<string, Course *> coursesById;

    vector<Semester *> semesters;
    
    static unsigned short YEARS;    // studying years
    static unsigned short ECTS;     // required ECTS
public:

    Secretary();
    ~Secretary();

    Student *findStudentById(const string &id) const;
    Professor *findProfessorById(const string &id) const;
    Course *findCourseById(const string &id) const;

    const set<Student *> *findStudentByName(const string &name) const;      // set of Students with duplicate name
    const set<Professor *> *findProfessorByName(const string &name) const;  // set of Professors with duplicate name

    void updateData(const string &oldName, Student *s);    // update studentsByName map when s->name changed
    void updateData(const string &oldName, Professor *p);  // update professorsByName map when p->name changed

    set<Student *> getStudents() const;             // get all Students in a set
    set<Professor *> getProfessors() const;         // get all Professors in a set
    set<Course *> getCourses() const;               // get all Courses in a set

    Semester *currentSemester();                         // pointer to current semester
    const Semester *semesterAt(std::size_t index) const; // pointer to n-th semester
    void nextSemester();                                 // advance to next semester
    int semesterCount() const;                           // how many semesters

    Secretary &operator+(const Student &s);
    Secretary &operator+(const Professor &p);
    Secretary &operator+(const Course &c);

    Secretary &operator-(const Student &s);
    Secretary &operator-(const Professor &p);
    Secretary &operator-(const Course &c);

    friend ostream &operator<<(ostream &str, const Secretary &secretary);

    void printStudents(ostream &str) const;
    void printProfessors(ostream &str) const;
    void printCourses(ostream &str) const;

    set<string> studentsToCSV() const;      // used when writing files
    set<string> professorsToCSV() const;    // used when writing files
    set<string> coursesToCSV() const;       // used when writing files

    static unsigned short getYears() { return YEARS; }
    static void setYears(unsigned short years) { YEARS = years; }

    static unsigned short getECTS() { return ECTS; }
    static void setECTS(unsigned short ects) { ECTS = ects; }
};