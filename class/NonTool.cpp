#include "NonTool.hpp"

NonTool::NonTool() : Item(), quantity(1) {}
NonTool::NonTool(int id, string name, string type) : Item(id, name, type), quantity(1) {}
NonTool::NonTool(int id, string name, string type, int qty) : Item(id, name, type), quantity(qty) {}
NonTool::NonTool(const NonTool& other) : Item(other.getID(), other.getName(), other.getType()), quantity(other.getQuantity()) {}
int NonTool::getQuantity() const { return this->quantity; }

void NonTool::setQuantity(int quantity) {
    this->quantity = quantity;
}

void NonTool::takeItem(int amount)
{
    if (amount > this->quantity)
    {
        cout << "You don't have that many item! Aborting..." << endl;
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
        cout << "Aaaah!! You add too many item! Please separate them. Aborting... " << endl;
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
    //cout << "Name: " << this->getName() << endl;
    //cout << "Quantity: " << this->getQuantity() << endl;
}

NonTool * NonTool::clone()
{
    return new NonTool(*this);
}

ostream &operator<<(ostream &os, NonTool nt)
{
    os << nt.getName() << ", " << nt.getQuantity();
    return os;
}
int NonTool::getQuantityDurability() {
    return this->getQuantity();
}

void NonTool::setQuantityDurability(int number) {
    this->setQuantity(number);
}

// ostream &operator<<(ostream &os, NonTool nt)
// {
//     os << nt.getName() << ", " << nt.getQuantity();
//     return os;
// }
