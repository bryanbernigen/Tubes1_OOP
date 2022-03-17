#ifndef __ITEM_HPP_
#define __ITEM_HPP_

#include <iostream>
#include <string>

using namespace std;

class Item
{
private:
    int id;
    string name;
    string type;

public:
    // 4 Sekawan
    Item();
    Item(int, string, string);
    // Item(const Item& other);
    //~Item();
    // Item &operator=( const Item &other);

    // Getter
    int getID() const;
    string getName() const;
    string getType() const;

    // Setter
    void setID(int);
    void setName(string);
    void setType(string);

    // Pure Virtual, supaya jadi ABC
    virtual void printInfo() = 0;
    virtual Item* clone() = 0;
    virtual int getQuantityDurability() = 0;
    virtual void setQuantityDurability(int) = 0;
};

#endif
