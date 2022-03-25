#include "NonTool.hpp"
#include "exception.hpp"
NonTool::NonTool() : Item(), quantity(1) {}
NonTool::NonTool(int id, string name, string type) : Item(id, name, type), quantity(1) {}
NonTool::NonTool(int id, string name, string type, int qty) : Item(id, name, type), quantity(qty) {}
NonTool::NonTool(const NonTool &other) : Item(other.getID(), other.getName(), other.getType()), quantity(other.getQuantity()) {}
int NonTool::getQuantity() const { return this->quantity; }

void NonTool::setQuantity(int quantity)
{
    this->quantity = quantity;
}

void NonTool::takeItem(int amount)
{
    if (amount > this->quantity)
    {
        throw new QuantityNotMetException(amount, this->quantity);
    }
    else
    {
        this->quantity -= amount;
    }
}

void NonTool::addItem(int amount)
{
    if (this->quantity + amount > MAX_QUANTITY)
    {
        throw new OverQuantityException();
    }
    else
    {
        this->quantity += amount;
    }
}

void NonTool::printInfo()
{
    cout << "[";
    cout << setfill('0') << setw(2) << this->getID();
    cout << " ";
    cout << setfill('0') << setw(2) << this->getQuantityDurability();
    cout << "]";
}

NonTool *NonTool::clone()
{
    return new NonTool(*this);
}

ostream &operator<<(ostream &os, NonTool nt)
{
    os << "ID         : " << nt.getID() << endl;
    os << "Name       : " << nt.getName() << endl;
    os << "Type       : " << nt.getType() << endl;
    os << "Quantity   : " << nt.getQuantityDurability() << endl;
    return os;
}

int NonTool::getQuantityDurability()
{
    return this->getQuantity();
}

void NonTool::setQuantityDurability(int number)
{
    this->setQuantity(number);
}