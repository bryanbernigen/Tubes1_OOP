#ifndef _Crafting_HPP_
#define _Crafting_HPP_

#include <list>
#include <string>
#include "resep.hpp"

using namespace std;

class Crafting
{
private:
    string *kotakresep;
    list<Resep>::iterator ptr;
    list<Resep> semuaresep;;
public:
    Crafting();
    //~Crafting();

    void addResep(Resep resep);
    void showAllResep();
};


#endif