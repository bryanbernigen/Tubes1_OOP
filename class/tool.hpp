#ifndef __TOOL_HPP_
#define __TOOL_HPP_

#include "Item.hpp"
#include <string>

using namespace std;

#define MAX_DURABILITY 10

class Tool : public Item
{
private:
    int durability;

public:
    // 4 Sekawan
    Tool();
    Tool(int, string, string);
    Tool(int, string, string, int);
    // Tool(const Tool& other);
    // ~Tool();
    // Tool &operator= (const Tool &other);

    // getter
    int getDurability() const;

    // setter
    void setDurability(int);

    // other
    void useTool();
    void printInfo();
<<<<<<< Updated upstream
    Tool * clone();
=======
    int getQuantityDurability();
    void setQuantityDurability(int);

    // friend ostream &operator<<(ostream &, NonTool nt);
    // friend ostream &operator<<(ostream &, Tool);
>>>>>>> Stashed changes
};

// ostream &operator<<(ostream &os, Tool nt)
// {
//     os << nt.getName() << ", " << nt.getQuantity();
//     return os;
// }

#endif
