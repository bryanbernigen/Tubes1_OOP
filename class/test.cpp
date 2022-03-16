#include <bits/stdc++.h>
#include "Item.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
using namespace std;

int main()
{
    // Tool Functionality
    Tool t;
    Tool t2(11, "Sword", "Iron");
    Tool t3(12, "Pickaxe", "Iron", 5);
    cout << t2.getID() << " " << t2.getName() << " " << t2.getType() << endl;

    cout << t3.getDurability() << endl;
    t3.useTool();
    t3.useTool();
    t3.printInfo();

    // NonTool Functionality
    NonTool nt;
    NonTool nt2(2, "LOG", "OAK");
    NonTool nt3(3, "PLANK", "OAK", 64);

    cout << nt2.getID() << " " << nt2.getName() << " " << nt2.getType() << endl;
    cout << nt.getQuantity() << endl;
    nt2.takeItem(2);
    nt3.takeItem(32);

    cout << nt2.getQuantity() << endl;
    nt2.addItem(9);
    nt2.printInfo();
    cout << nt3 << endl;

    return 0;
}