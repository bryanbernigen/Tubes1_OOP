#ifndef _Crafting_HPP_
#define _Crafting_HPP_

#include <list>
#include <string>
#include "resep.hpp"
#include "item.hpp"
#include "tool.hpp"
#include "NonTool.hpp"
#include <map>
#include <tuple>

using namespace std;

class Crafting
{
private:
    map<string,tuple<int,string,string>> itemDict;
    Item **craftingtable;
    bool* slotStatus;
    list<Resep> semuaresep;
public:
    Crafting();
    virtual ~Crafting();

    void addItemDict(string line);
    void addResep(Resep resep);
    void addToCraftingTable(Item& item, int pos);
    void showAllResep();
    string craft();
    void RecipeMatch(Resep resep);
    void searchDict(string nama);
};


#endif