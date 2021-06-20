#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

using namespace std;

/// cpp11
/// cpp14
/// cpp17
void cpp17AnyTest();
void cpp17VarientTest();
void cpp17OptionalTest();
/// cpp20
/// cpp23


template <typename... Ts>
struct overload : Ts...
{
    using Ts::operator()...; /// let the functor supply operator()
};
// base types are deduced from passed arguments:
template <typename... Ts>
overload(Ts...) -> overload<Ts...>;


struct TYPE_A
{
    int ival;
    std::vector<double> dvec;

    TYPE_A()
    {
        ival = 12;
        dvec.push_back(15.36);
        dvec.push_back(21.7);
    }

    TYPE_A(int i, double d1, double d2)
    {
        ival = i;
        dvec.push_back(d1);
        dvec.push_back(d2);
    }

    friend std::ostream &operator<<(std::ostream &os, const TYPE_A &rhs)
    {
        os << rhs.ival << std::endl;
        copy(rhs.dvec.begin(), rhs.dvec.end(), ostream_iterator<double>(cout, " "));

        return os;
    }
};

class TYPE_B
{
    char cval;
    std::vector<std::string> svec;
    TYPE_A aval;

public:
    TYPE_B()
    {
        cval = 'S';
        svec.push_back("lalala");
        svec.push_back("what is this");
    }

    TYPE_B(char c, std::string s1, std::string s2)
    {
        cval = c;
        svec.push_back(s1);
        svec.push_back(s2);
    }

    friend std::ostream &operator<<(std::ostream &os, const TYPE_B &rhs)
    {
        os << rhs.cval << std::endl;
        copy(rhs.svec.begin(), rhs.svec.end(), ostream_iterator<string>(cout, " "));

        return os;
    }
};

#endif // COMMON_H
