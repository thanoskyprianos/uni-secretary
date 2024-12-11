#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

using std::ostream;
using std::istream;

using std::string;

class Course {
private:
    string id;
    string name;
    unsigned short semester;
    unsigned short ects;
    bool mandatory;
public:
    Course();
    Course(string id, string name, unsigned short semester, unsigned short ects, bool mandatory);
    ~Course();

    string getId() const;

    string getName() const;
    void setName(const string &name);

    unsigned short getSemester() const;
    void setSemester(unsigned short semester);

    unsigned short getECTS() const;
    void setECTS(unsigned short ects);

    bool isMandatory() const;
    void setMandatory(bool mandatory);

    friend ostream &operator<<(ostream &str, const Course &c);
    friend istream &operator>>(istream &str, Course &c);

    string toCSV() const;
};