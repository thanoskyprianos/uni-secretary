#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef PERSON
#define PERSON
#include "person.h"
#endif

#ifndef UTIL
#define UTIL
#include "../Util/util.h"
#endif

using std::cout;
using std::istream;
using std::ostream;

using std::getline;

using std::string;
using std::to_string;

using namespace util;

unsigned int Person::objectCount = 0;
unsigned int Person::getObjectCount() { return Person::objectCount; }

Person::Person() : age(0) {
    Person::objectCount++;
}

Person::Person(
    const string &id, const string &name, unsigned short age,
    const string &address, const string &phoneNumber, const string &email
): id(id), name(name), age(age),
   address(address), phoneNumber(phoneNumber), email(email)
{
    Person::objectCount++;
}

Person::~Person() {
    Person::objectCount--;
}

string Person::getId() const { return id; }

string Person::getName() const { return name; }
void Person::setName(const string &name) { this->name = name; }

unsigned short Person::getAge() const { return age; }
void Person::setAge(unsigned short age) { this->age = age; }

string Person::getAddress() const { return address; }
void Person::setAddress(const string &address) { this->address = address; }

string Person::getPhoneNumber() const { return phoneNumber; }
void Person::setPhoneNumber(const string &phoneNumber) { this->phoneNumber = phoneNumber; }

string Person::getEmail() const { return email; }
void Person::setEmail(const string &email) { this->email = email; }

ostream &operator<<(ostream &str, const Person &p) {
    str << GREEN << p.id << ": " << RESET <<
           p.name << ", " <<
           p.age << ", " <<
           p.address  << ", " <<
           p.phoneNumber << ", " <<
           p.email;

    return str;
}

istream &operator>>(istream &str, Person &p) {
    cout << "Give" << CYAN << " id: " << RESET;
    cinWithClear(str, p.id);

    cout << "Give" << CYAN << " name: " << RESET;
    getline(str, p.name);

    cout << "Give" << CYAN << " age: " << RESET;
    cinWithClear(str, p.age);

    cout << "Give" << CYAN << " address: " << RESET;
    getline(str, p.address);

    cout << "Give" << CYAN << " phone number: " << RESET;
    getline(str, p.phoneNumber);

    cout << "Give" << CYAN << " email: " << RESET;
    cinWithClear(str, p.email);

    return str;
}

string Person::toCSV() const {
    return id + ',' + name + ',' + to_string(age) + ',' + address + ',' + phoneNumber + ',' + email;
}

Student::Student() : Person(), ects(0), semester(1) { }
Student::Student(
    const string &id, const string &name, unsigned short age,
    const string &address, const string &phoneNumber, const string &email,
    unsigned short ects, unsigned short year
) : Person(id, name, age, address, phoneNumber, email), ects(ects), semester(year)
{ }

Student::~Student() { }

unsigned short Student::getECTS() const { return ects; }
unsigned short Student::getSemester() const { return semester; }

void Student::setECTS(unsigned short ects) { this->ects = ects; }
void Student::setSemester(unsigned short semester) { this->semester = semester; }

ostream &operator<<(ostream &str, const Student &s) {
    str << (Person &)s;
    str << ", " << s.ects << ", " << s.semester;

    return str;
}

istream &operator>>(istream &str, Student &s) {
    str >> (Person &)s;

    cout << "Give" << CYAN << " ects: " << RESET;
    cinWithClear(str, s.ects);

    cout << "Give" << CYAN << " semester: " << RESET;
    cinWithClear(str, s.semester);

    return str;
}

string Student::toCSV() const {
    return Person::toCSV() + ',' + to_string(ects) + ',' + to_string(semester);
}

Professor::Professor() : Person() { }
Professor::Professor(
    const string &id, const string &name, unsigned short age,
    const string &address, const string &phoneNumber, const string &email
): Person(id, name, age, address, phoneNumber, email)
{ }

ostream &operator<<(ostream &str, const Professor &s) {
    str << (Person &)s;
    
    return str;
}

istream &operator>>(istream &str, Professor &s) {
    str >> (Person &)s;

    return str;
}

string Professor::toCSV() const {
    return Person::toCSV();
}