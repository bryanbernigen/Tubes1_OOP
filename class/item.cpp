#include "Item.hpp"

Item::Item()
{
    this->id = 0;
    this->name = "-";
    this->type = "-";
}

Item::Item(int id, string name, string type)
{
    this->id = id;
    this->name = name;
    this->type = type;
}

// Getter
int Item::getID() const
{
    return this->id;
}
string Item::getName() const
{
    return this->name;
}
string Item::getType() const
{
    return this->type;
}

// Setter
void Item::setID(int id)
{
    this->id = id;
}
void Item::setName(string name)
{
    this->name = name;
}
void Item::setType(string type)
{
    this->type = type;
}