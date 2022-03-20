#ifndef _Crafting_HPP_
#define _Crafting_HPP_

#include <list>
#include <string>
#include "resep.hpp"
#include "item.hpp"
#include "tool.hpp"
#include "NonTool.hpp"
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
    pair<string,int> craft();
    void RecipeMatch(Resep resep);

    void showCrafting();
};

class QuantityNotMetException : public exception
{
public:
    const char *what() const throw()
    {
        return "Quantity Not Met";
    }
};

class SlotEmptyException : public exception
{
public:
    const char *what() const throw()
    {
        return "Slot is Empty";
    }
};

class SlotFilledException : public exception
{
public:
    const char *what() const throw()
    {
        return "Slot is Filled with other item";
    }
};

#endif