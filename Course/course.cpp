#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef SECRETARY
#define SECRETARY
#include "../Secretary/secretary.h"
#endif

#ifndef COURSE
#define COURSE
#include "course.h"
#endif

#ifndef UTIL
#define UTIL
#include "../Util/util.h"
#endif

using std::cout;
using std::getline;
using std::ostream;
using std::istream;

using std::string;
using std::to_string;

using namespace util;

Course::Course() : semester(0), ects(0), mandatory(false) { }
Course::Course(string id, string name, unsigned short semester, unsigned short ects, bool mandatory)
       : id(id), name(name), semester(semester), ects(ects), mandatory(mandatory) { }
    
Course::~Course() { }

string Course::getId() const { return id; }

string Course::getName() const { return name; }
void Course::setName(const string &name) { this->name = name; }

unsigned short Course::getSemester() const { return semester; }
void Course::setSemester(unsigned short semester) { this->semester = semester; }

unsigned short Course::getECTS() const { return ects; }
void Course::setECTS(unsigned short ects) { this->ects = ects; }

bool Course::isMandatory() const { return mandatory; }
void Course::setMandatory(bool mandatory) { this->mandatory = mandatory; }

ostream &operator<<(ostream &str, const Course &c) {
    str << GREEN << c.id << ": " << RESET <<
           c.name << ", " << 
           (c.semester % 2 ? "Fall" : "Spring") << " (" << c.semester << ")" <<", " << 
           c.ects << ", " << (c.mandatory ? "Mandatory" : "Not mandatory");

    return str;
}

istream &operator>>(istream &str, Course &c) {
    cout << "Give" << CYAN << " id: " << RESET;
    cinWithClear(str, c.id);

    cout << "Give" << CYAN << " name: " << RESET;
    getline(str, c.name);

    cout << "Give" << CYAN << " semester " << RESET << "(1 - " << Secretary::getYears() * 2 << "): ";
    c.semester = choiceLoop(1, Secretary::getYears() * 2);

    cout << "Give" << CYAN << " ects: " << RESET;
    cinWithClear(str, c.ects);

    cout << "Is the course " << CYAN << "mandatory" << RESET << "? (y/Y/n/N): ";
    char choice = choiceLoop({'y', 'Y', 'n', 'N'});
    
    switch (choice)
    {
    case 'y': case 'Y': c.mandatory = true;  break;
    case 'n': case 'N': c.mandatory = false; break;
    }

    return str;
}

string Course::toCSV() const {
    return id + ',' + name + ',' + to_string(semester) + ',' + to_string(ects) + ',' + to_string(mandatory);
}