#ifndef __ITEM_HPP_
#define __ITEM_HPP_

#include <string>

using namespace std;

class item
{
private:
    int ID;
    string Name;
    string Type;
public:
    //4 Sekawan
    item();
    item(int ID, string Name, string Type);
    //item(const item& other);
    //~item();
    //item &operator=( const item &other);

    //Getter
    const int getID();
    const string getName();
    const string getType();

    //Setter
    void setID(int ID);
    void getName(string Name);
    void getType(string Type);
};


#endif
