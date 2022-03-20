#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <tuple>
#include <math.h>
#include "item.hpp"
#include "tool.hpp"
#include "NonTool.hpp"
using namespace std;

extern NonTool emptyNonTool;
extern Tool emptyTool;

class inventory
{
private:
    map<string,tuple<int,string,string>> itemDict;
    Item** inventories;
    int neff; // first empty element index
public:
    // Constructor
    inventory();

    // Copy Constructor
    inventory(const inventory&);

    // Assignment Operator
    inventory& operator=(const inventory&);
    // Destructor
    ~inventory();

    // Getter and Setter
    Item& getInventory(int);
    void setInventory(int, Item&);
    int getNeff() const;
    void nextNeff();

    // Predicate checking
    bool isFull();
    bool isEmpty(int);
    bool isItemEmpty(Item&);
    bool isTool(int); // If false --> NonTool

    // Functions
    // Add item to inventory
    // 1. add item, unknown slotID
    void addInventory(Item&);
    // 2. add item to specific inventory ID
    void addInventory(Item&, int);

    // Take item from inventory
    Tool* takeInventory(Tool&);
    NonTool* takeInventory(NonTool&);
    Item* takeInventory(int, int);

    // Move item from src slot to dest slot
    bool pileInventory(int, int);

    // Output
    void printInfoInventory();
    int maxNeff(int);
    void showInventory();
    void exportInventory(string);

    // Dictionary
    void addItemDict(string);
    Item* searchDict(string, int);
};

class SlotFullException : public exception 
{
public:
    const char* what() const throw(){
        return "Inventory is Full!";
    }
};

class SlotStorageInsufficient : public exception 
{
public:
    const char* what() const throw(){
        return "Storage of inventory with slot ID specified is insufficient!";
    }
};

class ItemNotMatch : public exception 
{
public:
    const char* what() const throw(){
        return "Item not match!";
    }
};

class SlotInitiallyNotEmpty : public exception 
{
public:
    const char* what() const throw(){
        return "Slot is initially not empty!";
    }
};

class ItemNotFound : public exception 
{
public:
    const char* what() const throw(){
        return "There's no such item with respective quantity in inventory!";
    }
};

class ItemQtInsufficient : public exception
{
public:
    const char* what() const throw(){
        return "Quantity of available items in inventory is insufficient!";
    }
};

#endif