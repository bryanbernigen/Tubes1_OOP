#ifndef _Crafting_HPP_
#define _Crafting_HPP_

#include <list>
#include <string>
#include "resep.hpp"
#include "item.hpp"

using namespace std;

class Crafting
{
private:
    Item **craftingtable;
    list<Resep>::iterator ptr;
    list<Resep> semuaresep;
public:
    Crafting();
    //~Crafting();

    void addResep(Resep resep);
    void addToCraftingTable(Item& item, int pos);
    void showAllResep();
    Item* craft();
    void RecipeMatch(Resep resep);
};


#endif