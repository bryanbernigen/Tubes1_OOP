#ifndef _Crafting_HPP_
#define _Crafting_HPP_

#include <list>
#include <string>
#include "resep.hpp"
#include "item.hpp"
#include "tool.hpp"
#include "NonTool.hpp"
#include "exception.hpp"
#include <iostream>
using namespace std;

using namespace std;

class Crafting
{
private:
    Item **craftingtable;
    bool *slotStatus;
    list<Resep> semuaresep;

public:
    Crafting();
    virtual ~Crafting();

    void addResep(Resep resep);
    int addToCraftingTable(Item &item, int pos);
    Item *takeItem(int pos, int quantity);
    Item *takeItem(int pos);
    void showAllResep();
    void showCraftingTable();
    pair<string,int> craft();
    void RecipeMatch(Resep resep);

    void showCrafting();
};



#endif

// MOVE I0 2 C0 C1 C2 (Works)
// MOVE I0 64 I1 I2