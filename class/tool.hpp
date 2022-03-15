#ifndef __TOOL_HPP_
#define __TOOL_HPP_

#include "item.hpp"
#include <string>

using namespace std;

#define MAX_DURABILITY 10

class tool : public item
{
private:
    int Durability;
public:
    //4 Sekawan
    tool();
    tool(int ID, string Name, string Type);
    tool(int ID, string Name, string Type, int Durability);
    // tool(const tool& other);
    // ~tool();
    // tool &operator= (const tool &other);

    //getter
    const int getDurability();

    //setter
    void setDurability(int Durability);

    //other
    void useTool();
};


#endif
