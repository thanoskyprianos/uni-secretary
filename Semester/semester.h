#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef MAP
#define MAP
#include <map>
#endif

#ifndef SET
#define SET
#include <set>
#endif

#ifndef COURSE
#define COURSE
#include "../Course/course.h"
#endif

#ifndef PERSON
#define PERSON
#include "../Person/person.h"
#endif

using std::ostream;

using std::map;
using std::set;

class Semester {
private:
    map<Course *, map<Student *, unsigned short>> students;
    map<Course *, set<Professor *>> professors;

    map<Student *, set<Course *>> studentCourseLookup;
    map<Professor *, set<Course *>> professorCourseLookup;

    static map<Student *, map<Course *, unsigned short>> passedCourses;
public:
    Semester();
    ~Semester();

    Semester &operator+(Student*s);
    Semester &operator+(Professor *p);
    Semester &operator+(Course *c);

    Semester &operator-(Student *s);
    Semester &operator-(Professor *p);
    Semester &operator-(Course *c);

    bool hasCourse(Course *c);               // check if c in semester
    bool hasCourse(Course *c, Student *s);   // check if s attends c
    bool hasCourse(Course *c, Professor *p); // check if p teaches c

    static bool hasPassedCourse(Course *c, Student *s);                  // static lookup for passed courses (throws)

    void registerGrade(Course *c, Student *s, unsigned short grade = 0); // register s in c with optional grade (throws)
    void assignProfessor(Course *c, Professor *p);                       // assign p in c (throws)

    unsigned short getGrade(Course *c, Student *s) const;                // get grade of s in c (throws)
    
    void finalize(); // finalize student grades, used for advancing to next semester

    friend ostream &operator<<(ostream &str, const Semester &s);
};