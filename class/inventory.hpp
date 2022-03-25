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
#include "exception.hpp"
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
    Item* getInventoryPtr(int);
    void setInventory(int, Item&);
    int getNeff() const;
    void nextNeff();

    // Predicate checking
    bool isFull();
    bool isEmpty(int);
    bool isItemEmpty(Item&);
    bool isTool(int); // If false --> NonTool
    bool isItemTool(Item& other);

    // Functions
    // Add item to inventory
    // 1. add item, unknown slotID
    void addInventory(Item&);
    // 2. add item to specific inventory ID
    void addInventory(Item&, int);

    // Take item from inventory
    // 1. take Tool from Inventory
    Tool* takeInventory(Tool&);
    // 2. take NonTool from Inventory
    NonTool* takeInventory(NonTool&);
    // 3. take item from inventory
    Item* takeInventory(Item&);
    // 4. take item with specific slot id and quantity
    Item* takeInventory(int, int);

    // Move item from src slot to dest slot
    bool pileInventory(int, int);

    // Output
    void printInfoInventory();
    void showInventory();
    void exportInventory(string);

    // Dictionary
    void addItemDict(string);
    Item* searchDict(string, int);
};


#endif