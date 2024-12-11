#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

#ifndef SSTREAM
#define SSTREAM
#include <sstream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef SECRETARY
#define SECRETARY
#include "Secretary/secretary.h"
#endif

#ifndef PERSON
#define PERSON
#include "Person/person.h"
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef UTIL
#define UTIL
#include "Util/util.h"
#endif

#define LINE_SIZE 5

using std::cout;
using std::cerr;
using std::cin;
using std::getline;
using std::endl;

using std::ifstream;
using std::ofstream;

using std::string;
using std::stoi;
using std::istringstream;

using std::vector;

using namespace util;

int mainMenu() {
    clear_screen();

    cout << "---" << CYAN << "OPTIONS" << RESET << "---" << endl;

    cout << GREEN << "1. " << RESET << "Students" << endl;
    cout << GREEN << "2. " << RESET << "Professors" << endl;
    cout << GREEN << "3. " << RESET << "Courses" << endl;
    cout << GREEN << "4. " << RESET << "Semester" << endl;
    cout << GREEN << "0. " << RESET << "Quit" << endl;

    return choiceLoop(0, 4);
}

int subchoiceMenu(string title) { // common sub-choices for Student, Professor and Course
    clear_screen();

    cout << "---" << CYAN << title << RESET << "---" << endl;

    cout << GREEN << "1. " << RESET << "View" << endl;
    cout << GREEN << "2. " << RESET << "Search" << endl;
    cout << GREEN << "3. " << RESET << "Add" << endl;
    cout << GREEN << "0. " << RESET << "Back" << endl;

    return choiceLoop(0, 3);
}

int semesterMenu() {
    clear_screen();

    cout << "---" << CYAN << "SEMESTER" << RESET << "---" << endl;

    cout << GREEN << "1. " << RESET << "View" << endl;
    cout << GREEN << "2. " << RESET << "Next Semester" << endl;
    cout << GREEN << "3. " << RESET << "Who graduates" << endl;
    cout << GREEN << "0. " << RESET << "Back" << endl;

    return choiceLoop(0, 3);
}

void viewMenu(const Secretary &s, string title, void(Secretary::*func)(ostream &) const) {
    clear_screen();

    cout << "---" << CYAN << title << RESET << "---" << endl;
    (s.*func)(cout);

    wait_for_enter();
}

template <typename T>  // search menu, returns pointer to object 
T *searchMenu(Secretary &s, string title,
                T*(Secretary::*idFunc)(const string &) const,
                const set<T*>*(Secretary::*nameFunc)(const string &) const = nullptr) {
    clear_screen();

    int upper = 1;
    cout << "---" << CYAN << "SEARCH" << RESET << "---" << endl;
    cout << GREEN << "1." << RESET << " By" << CYAN << " id" << RESET << endl;
    if (nameFunc) { // only search by name for Student and Professor
        cout << GREEN << "2." << RESET << " By" << CYAN << " name" << RESET << endl;
        upper = 2;
    }
    cout << GREEN << "0." << RESET << " Back" << endl;

    int choice = choiceLoop(0, upper);

    T *ptr = nullptr;
    string buf;
    switch (choice)
    {
    case 1:
        cout << "Give id: ";
        cinWithClear(cin, buf);
        try {
            ptr = (s.*idFunc)(buf);
        } catch (string id) {
            cout << title << " with id: " << RED << id << RESET << " does not exist!" << endl;
            wait_for_enter();
            return nullptr;
        }
        break;
    case 2:
        cout << "Give name: ";
        getline(cin, buf);
        try {
            const set<T *> *ps = (s.*nameFunc)(buf);
            int i = 0;

            clear_screen();

            cout << "---" << CYAN << "PICK FROM LIST" << RESET << "---" << endl; // list pick for duplicate names
            for (const auto &s : *ps)
                cout << CYAN << (i++) << RESET << ". " << *s << endl;

            int choice = choiceLoop(0, i - 1);
            ptr = *std::next((*ps).begin(), choice);           
        } catch (string name) {
            cout << "No " << title << " with name: " << RED << name << RESET << " found!" << endl;
            wait_for_enter();
            return nullptr;
        }
        break;
    case 3: 
        return nullptr;
    }

    return ptr;
}

void editCourseMenu(Secretary &s, Course *ptr) {  // Edit menu for Course
    unsigned short oldSemester;
    
    while (true) {
        clear_screen();

        cout << "---" << CYAN << "EDIT" << RESET << "--- (" << *ptr << ")" << endl;

        cout << GREEN << "1. " << RESET << "Name" << endl;
        cout << GREEN << "2. " << RESET << "ECTS" << endl;
        cout << GREEN << "3. " << RESET << "Mandatory" << endl;
        cout << GREEN << "4. " << RESET << "Semester" << endl;
        cout << GREEN << "0. " << RESET << "Back" << endl;

        int choice = choiceLoop(0, 4);

        string buf;
        switch (choice)
        {
        case 1:
            cout << "Give new name: ";
            getline(cin, buf);
            ptr->setName(buf);
            break;
        case 2:
            cout << "Give new ECTS: ";
            cinWithClear(cin, buf);
            ptr->setECTS((unsigned short)stoi(buf));
            break;
        case 3:
            ptr->setMandatory(!ptr->isMandatory());
            break;
        case 4:
            oldSemester = ptr->getSemester();

            cout << "Give new semester (1 - " << Secretary::getYears() * 2 << ") ";
            ptr->setSemester((unsigned short)choiceLoop(1, Secretary::getYears() * 2));

            if (oldSemester % 2 != ptr->getSemester() % 2) {     // only have to do anything if semester period changed
                try { *s.currentSemester() + ptr; }              // if newSemester != oldSemester try adding
                catch (Course *) { *s.currentSemester() - ptr; } // already exists so remove it
            }
            break;
        case 0:
            return;
        }
    }
}

template <typename T>
void editMenu(Secretary &s, T *ptr) {  // Edit menu for Student and Professor
    string oldName = "";

    while (true) {
        clear_screen();

        cout << "---" << CYAN << "EDIT" << RESET << "--- (" << *ptr << ")" << endl;

        cout << GREEN << "1. " << RESET << "Name" << endl;
        cout << GREEN << "2. " << RESET << "Age" << endl;
        cout << GREEN << "3. " << RESET << "Address" << endl;
        cout << GREEN << "4. " << RESET << "Phone number" << endl;
        cout << GREEN << "5. " << RESET << "Email" << endl;
        cout << GREEN << "0. " << RESET << "Back" << endl;

        int choice = choiceLoop(0, 5);

        string buf;
        switch (choice) {
            case 1: 
                oldName = ptr->getName(); // Keep old name so we can update <...>ByName maps   
                
                cout << "Give new name: ";
                getline(cin, buf);
                ptr->setName(buf);
                break;
            case 2:
                cout << "Give new age: ";
                cinWithClear(cin, buf);
                ptr->setAge((unsigned short)stoi(buf));
                break;
            case 3:
                cout << "Give new address: ";
                getline(cin, buf);
                ptr->setAddress(buf);
                break;
            case 4:
                cout << "Give new phone number: ";
                getline(cin, buf);
                ptr->setPhoneNumber(buf);
                break;
            case 5:
                cout << "Give new email: ";
                getline(cin, buf);
                ptr->setEmail(buf);
                break;
            case 0:
                if (oldName != "")
                    s.updateData(oldName, ptr); // update <...>ByName maps

                return;
        }
    }
}

template <typename T>
void addMenu(Secretary &s, string title) {
    clear_screen();

    cout << "---" << CYAN << "ADD" << RESET << "---" << endl;

    T t;
    cin >> t;

    try {
        s + t;
        cout << "Inserted: " << t << endl;
    } catch (const T &p) {
        cout << title << " with id: " << RED << p.getId() << RESET << " already exists!" << endl; 
    }

    wait_for_enter();
}

template <typename T>
void deleteMenu(Secretary &s, string title, T *ptr) {
    clear_screen();

    cout << "Are you sure you want to " << RED
         << "DELETE " << RESET << title << ": " << endl << '\t' << *ptr << " (y/Y/n/N)" << endl;
        
    char choice = choiceLoop({'y', 'Y', 'n', 'N'});
    switch (choice)
    {
    case 'y': case 'Y':
        s - *ptr;
        break;
    case 'n': case 'N':
        return;
    }
}

void assignProfessorsMenu(Secretary &s, Course *c) {
    auto ps = s.getProfessors();
    set<Professor *> eligible;  // Professors that don't teach c already

    for (const auto &p : ps) {
        if (!s.currentSemester()->hasCourse(c, p)) {
            eligible.insert(p);
        }
    }

    while (true) {
        clear_screen();

        cout << "---" << CYAN << "PICK FROM LIST (-1 to exit)" << RESET << "---" << endl;

        int i = 0;
        for (const auto &ptr : eligible)
            cout << CYAN << i++ << RESET << ": " 
                 << GREEN << ptr->getId() << RESET << " - "
                 << ptr->getName() << endl;
        
        int choice = choiceLoop(-1, i - 1);
        if (choice == -1) return;

        auto ptr = *std::next(eligible.begin(), choice);
        s.currentSemester()->assignProfessor(c, ptr);
        eligible.erase(ptr);  // already assigned
    }
}

void registerCoursesMenu(Secretary &s, Student *ptr) {
    auto cs = s.getCourses();
    set<Course *> eligible; // Courses that ptr has not passed and whose semester <= ptr->semester

    for (const auto &c : cs) {
        if (c->getSemester() <= ptr->getSemester() && s.currentSemester()->hasCourse(c) 
            && !s.currentSemester()->hasCourse(c, ptr) && !Semester::hasPassedCourse(c, ptr)) {
                eligible.insert(c);
            }
    }

    while (true) {
        clear_screen();

        cout << "---" << CYAN << "PICK FROM LIST (-1 to exit)" << RESET << "---" << endl;

        int i = 0;
        for (const auto &c : eligible) {
            cout << CYAN << i++ << RESET << ": " 
                 << GREEN << c->getId() << RESET << " - "
                 << c->getName() << " | Semester: " 
                 << c->getSemester() << " | ECTS: "
                 << c->getECTS()
                 << (c->isMandatory() ? " | Mandatory" : " | Not Mandatory") << endl;
        }

        int choice = choiceLoop(-1, i - 1);
        if (choice == -1) return;

        auto c = *std::next(eligible.begin(), choice);
        s.currentSemester()->registerGrade(c, ptr);
        eligible.erase(c);  // already registered
    }
}

void setGradesMenu(Secretary &s, Professor *p) {
    auto ss = s.getStudents();
    auto cs = s.getCourses();
    map <Course *, set<Student *>> eligible;    // Courses p teaches

    for (const auto &c : cs) {
        if (s.currentSemester()->hasCourse(c, p)) {
            eligible[c];

            for (const auto &ptr : ss) {
                if (s.currentSemester()->hasCourse(c, ptr))
                    eligible[c].insert(ptr);
            }
        }
    }

    while (true) {
        clear_screen();

        cout << "---" << CYAN << "PICK FROM LIST (-1 to exit)" << RESET << "---" << endl;
        int i = 0;

        for (const auto &ptr : eligible) {
            Course *c = ptr.first;
            cout << CYAN << i++ << RESET << ": " 
            << GREEN << c->getId() << RESET << " - "
            << c->getName() << " | Semester: " 
            << c->getSemester() << endl;
        }

        int choice = choiceLoop(-1, i - 1);
        if (choice == -1) return;
        Course *t = (*std::next(eligible.begin(), choice)).first;

        while (true) {
            clear_screen();

            cout << "---" << CYAN << "PICK FROM LIST (-1 to go back)" << RESET << "---" << endl;
            
            i = 0;
            for (const auto &st : eligible[t])  {
                unsigned short grade = s.currentSemester()->getGrade(t, st);
                cout << CYAN << i++ << RESET << ": " 
                     << GREEN << st->getId() << RESET << " - "
                     << st->getName() << " | Semester: " << st->getSemester()
                     << " | Grade: " << (grade >= 5 ? GREEN : RED)
                     << grade << RESET << endl;
            }

            choice = choiceLoop(-1, i - 1);
            if (choice == -1) break;
            Student *ts = *std::next(eligible[t].begin(), choice);

            cout << "Give grade (0-10): ";
            unsigned int grade = (unsigned int)choiceLoop(0, 10);
            s.currentSemester()->registerGrade(t, ts, grade);
        }
    }
}

void semesterCoursePassesMenu(Secretary &s, Course *c, Semester *ptr, int semesterNum) {
    clear_screen();
    
    cout << "---" << CYAN << "PASSED " << c->getName() << RESET << "---" << endl;
    
    ofstream fptr;
    string fileName = "./Grades/" + c->getId() + "_" + "Sem_" + std::to_string(semesterNum) + ".csv";
    fptr.open(fileName); // fileName : ./Grades/<ID>_Sem_<#SEM>.csv

    fptr << "id,name,grade";

    auto ss = s.getStudents();
    for (const auto &st : ss) {
        try {  // will execute if c in ptr and st has c
            unsigned short grade = ptr->getGrade(c, st);
            if (ptr->hasPassedCourse(c, st)) {
                cout << GREEN << st->getId() << RESET << " - "
                     << st->getName() << ": " << GREEN 
                     << grade << RESET << endl;

                fptr << endl << st->getId() << ',' << st->getName() << ',' << grade;
            }
        }
        catch(Course *) { continue; }
        catch(Student *) { continue; }
    }

    fptr.close();
}

void professorStatisticsMenu(Secretary &s, Professor *p, Semester *ptr) {
    clear_screen();

    cout << "---" << CYAN << "STATISTICS (" << p->getName() << ")" << RESET << "---" << endl;

    for (const auto &c : s.getCourses()) {
        if (ptr->hasCourse(c, p)) {

            cout << CYAN << c->getName() << RESET << endl;

            for (const auto &st : s.getStudents()) {
                try {  // will execute if c in ptr and st has c
                    unsigned short grade = ptr->getGrade(c, st);
                    cout << '\t' << GREEN << st->getId() << RESET
                         << st->getName() << ": " << (grade >= 5 ? GREEN : RED)
                         << grade << RESET << endl;
                } 
                catch (Course *) { }
                catch (Student *) { }
            }
        }
    }
}

void whoGraduatesMenu(Secretary &s) {
    clear_screen();

    cout << "---" << CYAN << "GRADUATES" << RESET << "---" << endl;

    for (const auto &st : s.getStudents()) {
        bool graduates = true; 

        if (st->getECTS() < Secretary::getECTS())  // no reason to look further
            continue;

        for (const auto &c : s.getCourses()) {
            if (c->isMandatory() && !Semester::hasPassedCourse(c, st)) {
                graduates = false;
                break;
            }
        }

        if (graduates) {
            cout << GREEN << st->getId() << RESET << " - "
                 << st->getName() << endl;
        }
    }
}

void studentStatisticsMenu(Secretary &s, Student *st, Semester *ptr) {
    clear_screen();

    cout << "---" << CYAN << "STATISTICS (" << st->getName() << ")" << RESET << "---" << endl;
    
    for (const auto &c : s.getCourses()) {
        try {  // will execute if c in ptr and st has c
            unsigned short grade = ptr->getGrade(c, st);
            cout << GREEN << c->getId() << RESET <<  " - " 
                 <<  c->getName() << " : " << (grade >= 5 ? GREEN : RED) 
                 << grade << RESET << endl;
        }
        catch (Course *) { }
        catch (Student *) { }
    }
}

int main(int argc, char **argv) {
    if (argc < 6) {
        cerr << "Invalid number of arguments." << endl;
        return 1;
    }

    Secretary::setYears((unsigned short)stoi(argv[4]));
    Secretary::setECTS((unsigned short)stoi(argv[5]));

    Secretary s;

    ifstream fptr;
    string line_buf, word_buf;
    vector<string> tokens;

    // READ STUDENTS
    fptr.open(argv[1]);
    getline(fptr, line_buf); // ignore title bar
    while(!fptr.eof()) {
        tokens.clear();
        
        getline(fptr, line_buf);
        istringstream iss {line_buf};

        while (getline(iss, word_buf, ','))
            tokens.push_back(word_buf);

        Student temp { 
            tokens[0], tokens[1],
            (unsigned short)stoi(tokens[2]), tokens[3],
            tokens[4], tokens[5],
            (unsigned short)stoi(tokens[6]), (unsigned short)stoi(tokens[7])
        };

        try { s + temp; }
        catch (const Student &s) { }
    }

    fptr.close();

    // READ PROFESSORS
    fptr.open(argv[2]);
    getline(fptr, line_buf); // ignore title bar
    while(!fptr.eof()) {
        tokens.clear();
        
        getline(fptr, line_buf);
        istringstream iss {line_buf};

        while (getline(iss, word_buf, ','))
            tokens.push_back(word_buf);

        Professor temp { 
            tokens[0], tokens[1], (unsigned short)stoi(tokens[2]),
            tokens[3], tokens[4], tokens[5],
        };

        try { s + temp; }
        catch (const Professor &) { }
    }

    fptr.close();

    // READ COURSES
    fptr.open(argv[3]);
    getline(fptr, line_buf);  // ignore title bar
    while(!fptr.eof()) {
        tokens.clear();
        
        getline(fptr, line_buf);
        istringstream iss {line_buf};

        while (getline(iss, word_buf, ','))
            tokens.push_back(word_buf);

        Course temp { tokens[0], tokens[1], (unsigned short)stoi(tokens[2]), (unsigned short)stoi(tokens[3]), (bool)stoi(tokens[4]) };

        try { s + temp; } 
        catch (const Course &) { }
    }
    
    fptr.close();

    s.nextSemester(); // begin first Semester

    bool running = true;
    while(running) {

        Student *sp = nullptr;
        Professor *pp = nullptr;
        Course *cp = nullptr;

        int choice = mainMenu();
        switch (choice)
        {
        case 1:
            choice = subchoiceMenu("STUDENTS");
            switch (choice)
            {
            case 1:
                viewMenu(s, "STUDENTS", &Secretary::printStudents);
                break;
            case 2:
                sp = searchMenu<Student>(s, "Student", &Secretary::findStudentById, &Secretary::findStudentByName);
                if (sp) {
                    cout << GREEN << "Found: " << *sp << endl;

                    cout << CYAN << "0. " << RESET << "Back | " << 
                            CYAN << "1. " << RESET << "Edit | " <<
                            CYAN << "2. " << RESET << "Delete | " << 
                            CYAN << "3. " << RESET << "Register Courses | " <<
                            CYAN << "4. " << RESET << "Statistics" << endl;

                    choice = choiceLoop(0, 4);

                    switch (choice)
                    {
                    case 1:
                        editMenu(s, sp);
                        break;
                    case 2:
                        deleteMenu(s, "Student", sp);
                        break;
                    case 3:
                        registerCoursesMenu(s, sp);
                        break;
                    case 4:
                        cout << "Choose semester (1 - " << s.semesterCount() << ") ";
                        choice = choiceLoop(1, s.semesterCount());
                        studentStatisticsMenu(s, sp, const_cast<Semester *>(s.semesterAt(choice - 1)));
                        break;
                    case 0:
                        break;
                    }

                    wait_for_enter();
                }
                break;
            case 3:
                addMenu<Student>(s, "Student");
                break;
            case 0:
                break;
            }
            break;
        case 2:
            choice = subchoiceMenu("PROFESSORS");
            switch (choice)
            {
            case 1:
                viewMenu(s, "PROFESSORS", &Secretary::printProfessors);
                break;
            case 2:
                pp = searchMenu<Professor>(s, "Professor", &Secretary::findProfessorById, &Secretary::findProfessorByName);
                if (pp) {
                    cout << GREEN << "Found: " << *pp << endl;

                    cout << CYAN << "0. " << RESET << "Back | " << 
                            CYAN << "1. " << RESET << "Edit | " <<
                            CYAN << "2. " << RESET << "Delete | " << 
                            CYAN << "3. " << RESET << "Set Grades | " << 
                            CYAN << "4. " << RESET << "Statistics" << endl;

                    choice = choiceLoop(0, 4);

                    switch (choice)
                    {
                    case 1:
                        editMenu(s, pp);
                        break;
                    case 2:
                        deleteMenu(s, "Course", pp);
                        break;
                    case 3:
                        setGradesMenu(s, pp);
                        break;
                    case 4:
                        cout << "Choose semester (1 - " << s.semesterCount() << ") ";
                        choice = choiceLoop(1, s.semesterCount());
                        professorStatisticsMenu(s, pp, const_cast<Semester *>(s.semesterAt(choice - 1)));
                        break;
                    case 0:
                        break;
                    }

                    wait_for_enter();
                }
                break;
            case 3:
                addMenu<Professor>(s, "Professor");
                break;
            case 0:
                break;
            }
            break;
        case 3:
            choice = subchoiceMenu("COURSES");
            switch (choice)
            {
            case 1:
                viewMenu(s, "COURSES", &Secretary::printCourses);
                break;
            case 2:
                cp = searchMenu<Course>(s, "Course", &Secretary::findCourseById);
                if (cp) {
                    cout << GREEN << "Found: " << *cp << endl;

                    cout << CYAN << "0. " << RESET << "Back | " << 
                            CYAN << "1. " << RESET << "Edit | " <<
                            CYAN << "2. " << RESET << "Delete | " << 
                            CYAN << "3. " << RESET << "Assign Professors | " <<
                            CYAN << "4. " << RESET << "Who passed" << endl;

                    choice = choiceLoop(0, 5);

                    switch (choice)
                    {
                    case 1:
                        editCourseMenu(s, cp);
                        break;
                    case 2:
                        deleteMenu(s, "Course", cp);
                        break;
                    case 3:
                        assignProfessorsMenu(s, cp);
                        break;
                    case 4:
                        cout << "Choose semester (1 - " << s.semesterCount() << ") ";
                        choice = choiceLoop(1, s.semesterCount());
                        if (choice == s.semesterCount())
                            cout << "Semester has not yet finished. " 
                                 << CYAN << "Advance to next semester" 
                                 << RESET << " to see results." << endl;
                        else
                            semesterCoursePassesMenu(s, cp, const_cast<Semester *>(s.semesterAt(choice - 1)), choice);
                        break;
                    case 0:
                        break;
                    }

                    wait_for_enter();
                }
                break;
            case 3:
                addMenu<Course>(s, "Course");
                break;
            case 0:
                break;
            }
            break;
        
        case 4:
            choice = semesterMenu();
            switch (choice)
            {
            case 1:
                clear_screen();
                cout << "---" << GREEN << "CURRENT SEMESTER" << RESET <<"---" << endl;
                cout << *s.currentSemester();
                wait_for_enter();
                break;
            case 2:
                clear_screen();
                cout << "Are you sure you want to advance to " << RED << "NEXT SEMESTER"
                     << RESET << "? (y/Y/n/N) ";
                choice = choiceLoop({'y', 'Y', 'n', 'N'});
                switch (choice)
                {
                case 'y': case 'Y': s.nextSemester(); break;
                case 'n': case 'N': break;
                }

                wait_for_enter();
                break;
            case 3:
                whoGraduatesMenu(s);
                wait_for_enter();
                break;
            case 0:
                break;
            }
            break;
        case 0:
            running = false;
            break;
        }
    }

    // Create new temp files, delete old ones and rename the new ones

    // Write Students
    ofstream ofptr;
    ofptr.open("./Input/students.temp.csv");
    ofptr << "Id,Name,Age,Address,Phone Number,Email,ECTS,Semester";
    for (auto s : s.studentsToCSV())
        ofptr << endl << s;
    ofptr.close();
    std::remove("./Input/students.csv");
    std::rename("./Input/students.temp.csv", "./Input/students.csv");


    // Write Professors
    ofptr.open("./Input/professors.temp.csv");
    ofptr << "Id,Name,Age,Address,Phone Number,Email";
    for (auto s : s.professorsToCSV())
        ofptr << endl << s;
    ofptr.close();
    std::remove("./Input/professors.csv");
    std::rename("./Input/professors.temp.csv", "./Input/professors.csv");

    // Write Courses
    ofptr.open("./Input/courses.temp.csv");
    ofptr << "Id,Name,Semester,ECTS,Mandatory";
    for (auto s : s.coursesToCSV())
        ofptr << endl << s;
    ofptr.close();
    std::remove("./Input/courses.csv");
    std::rename("./Input/courses.temp.csv", "./Input/courses.csv");

    return 0;
}