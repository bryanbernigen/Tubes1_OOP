#include <fstream>
#ifndef _EXEC_HPP__
#define _EXEC_HPP__
using namespace std;

class InvalidCommand : public exception
{
public:
    const char *what() const throw()
    {
        return "We dont know what are you saying?! Please try it again.\n";
    }
};

class InvalidSlotAmount : public exception
{
public:
    const char *what() const throw()
    {
        return "You input an invalid slot amount! Please try it again.\n";
    }
};

#endif