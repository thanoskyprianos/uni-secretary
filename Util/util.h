#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef SET
#define SET
#include <set>
#endif

#ifndef MAP
#define MAP
#include <map>
#endif

#ifndef INIT_LIST
#define INIT_LIST
#include <initializer_list>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef LIMITS
#define LIMITS
#include <limits>
#endif

using std::istream;
using std::ostream;

using std::set;
using std::map;
using std::initializer_list;

using std::string;

using std::numeric_limits;
using std::streamsize;

namespace util {
    
    const string CYAN = "\033[0;96m";
    const string RED = "\033[0;91m";
    const string GREEN = "\033[0;92m";
    const string RESET = "\033[0m";

    template <typename T>
    void cinWithClear(istream &str, T &dest) {
        str >> dest;
        str.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    template <typename T>
    set<string> DataToCSV(map<string, T> data) {    // used by writing processes at program end
        set<string> lines;
        for (const auto &p : data)
            lines.insert((*p.second).toCSV());

        return lines;
    }

    template <typename U, typename V>
    void mapPrint(ostream &str, map<U, V> m) {      // print values of m
        for (const auto &p : m) 
            str << *p.second << std::endl;
    }

    template <typename T>
    set<T *> mapToSet(map<string, T *> m) {         // get values of m and insert them into a set
        set<T *> res;
        for (const auto &p : m)
            res.insert(p.second);

        return res;
    }

    int choiceLoop(int lower, int upper);           // choose in range [lower, upper]
    char choiceLoop(initializer_list<char> args);   // choose between args

    void clear_buf(istream &str);
    void clear_screen();
    void clear_lines(unsigned int c = 1);
    void wait_for_enter();

}