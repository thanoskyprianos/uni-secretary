#ifndef IOSTREAM
#include <iostream>
#define IOSTREAM
#endif

#ifndef STRING
#include <string>
#define STRING
#endif

using std::ostream;
using std::istream;

using std::string;

class Person {
private:
    static unsigned int objectCount;

    string id;
    string name;
    unsigned short age;
    string address;
    string phoneNumber;
    string email;
public:
    static unsigned int getObjectCount();

    Person();
    Person(
        const string &id,
        const string &name,
        unsigned short age,
        const string &address,
        const string &phoneNumber,
        const string &email
    );

    virtual ~Person();

    string getId() const;

    string getName() const;
    void setName(const string &name);

    unsigned short getAge() const;
    void setAge(unsigned short age);
    
    string getAddress() const;
    void setAddress(const string &address);

    string getPhoneNumber() const;
    void setPhoneNumber(const string &phoneNumber);

    string getEmail() const;
    void setEmail(const string &email);

    friend ostream &operator<<(ostream &str, const Person &p);
    friend istream &operator>>(istream &str, Person &p);
    
    virtual string toCSV() const = 0;
};

class Student : public Person {
private:
    unsigned short ects;
    unsigned short semester;
public:
    Student();
    Student(
        const string &id,
        const string &name,
        unsigned short age,
        const string &address,
        const string &phoneNumber,
        const string &email,
        unsigned short ects,
        unsigned short semester
    );
    ~Student();

    unsigned short getECTS() const;
    unsigned short getSemester() const;

    void setECTS(unsigned short ects);
    void setSemester(unsigned short semester);

    friend ostream &operator<<(ostream &str, const Student &s);
    friend istream &operator>>(istream &str, Student &s);

    string toCSV() const override;
};

class Professor : public Person { 
public:
    Professor();
    Professor(
        const string &id,
        const string &name,
        unsigned short age,
        const string &address,
        const string &phoneNumber,
        const string &email
    );

    friend ostream &operator<<(ostream &str, const Professor &s);
    friend istream &operator>>(istream &str, Professor &s);

    string toCSV() const override;
};