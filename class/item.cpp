#include "item.hpp"

item::item()
{
    this->ID = 0;
    this->Name = "-";
    this->Type = "-";
}

item::item(int ID, string Name, string Type)
{
    this->ID = ID;
    this->Name = Name;
    this->Type = Type;
}

// Getter
const int item::getID()
{
    return this->ID;
}
const string item::getName()
{
    return this->Name;
}
const string item::getType()
{
    return this->Type;
}

// Setter
void item::setID(int ID)
{
    this->ID = ID;
}
void item::getName(string Name)
{
    this->Name = Name;
}
void item::getType(string Type)
{
    this->Type = Type;
}