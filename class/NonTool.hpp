#ifndef _NONTOOL_HPP_
#define _NONTOOL_HPP_

#include "Item.hpp"
using namespace std;

#define MAX_QUANTITY 64

class NonTool : public Item
{
private:
    int quantity;

public:
    NonTool();
    NonTool(int, string, string);
    NonTool(int, string, string, int);
    NonTool(const NonTool&);
    // ~NonTool();
    // NonTool &operator= (const NonTool&);

    int getQuantity() const;
    void setQuantity(int quantity);
    void takeItem(int);
    void addItem(int);

    void printInfo();
    NonTool * clone();
    int getQuantityDurability();
    void setQuantityDurability(int);

    friend ostream &operator<<(ostream &, NonTool);
};

#endif