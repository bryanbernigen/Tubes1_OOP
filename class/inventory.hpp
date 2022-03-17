#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#include <iostream>
#include <fstream>
#include "item.hpp"
#include "tool.hpp"
#include "NonTool.hpp"
using namespace std;

class inventory
{
private:
    Item** inventories;
    int neff; // indeks efektif terakhir
public:
    // Constructor
    inventory();
    inventory(const inventory& inv);
    ~inventory();

    // Getter and Setter
    Item& getInventory(int id);
    void setInventory(int id, Item& value);
    int getNeff() const;

    // Predicate checking
    bool isFull();
    bool isTool(int idx); // If false --> NonTool

    // Functions
    // Add item to inventory
    // 1. add item, unknown slotID
    void addInventory(Item& other);
    // 2. add item to specific inventory ID
    void addInventory(Item& other, int slotID);

    // Take item from inventory
    bool takeInventory(Item& other);
    bool takeInventory(int slotID, int quantity);

    // Move item from src slot to dest slot
    bool pileInventory(int idx_src, int idx_dest);

    // Output
    void displayInventory();
    void exportInventory(string filename);
};

#endif