#include "Tool.hpp"
#include "exception.hpp"
Tool::Tool() : Item()
{
    this->durability = MAX_DURABILITY;
}

Tool::Tool(int ID, string Name, string Type) : Item(ID, Name, Type)
{
    this->durability = MAX_DURABILITY;
}

Tool::Tool(int id, string name, string type, int durability) : Item(id, name, type)
{
    if (durability > 0 && durability < MAX_DURABILITY)
    {
        this->durability = durability;
    }
    else
    {
        this->durability = MAX_DURABILITY;
    }
}

// getter
int Tool::getDurability() const
{
    return this->durability;
}

// setter
void Tool::setDurability(int durability)
{
    this->durability = durability;
}

// other
void Tool::useTool()
{
    if (this->durability > 0)
    {
        this->durability--;
    }
    else
    {
        throw new ToolOverused();
    }
}

void Tool::printInfo()
{
    cout << "[";
    cout << setfill('0') << setw(2) << this->getID();
    cout << " ";
    cout << setfill('0') << setw(2) << this->getQuantityDurability();
    cout << "]";
}

Tool *Tool::clone()
{
    return new Tool(*this);
}
int Tool::getQuantityDurability()
{
    return this->getDurability();
}

void Tool::setQuantityDurability(int number)
{
    this->setDurability(number);
}

ostream &operator<<(ostream &os, Tool t)
{
    os << "ID         : " << t.getID() << endl;
    os << "Name       : " << t.getName() << endl;
    os << "Type       : " << t.getType() << endl;
    os << "Durability : " << t.getQuantityDurability() << endl;
    return os;
}
