#include <bits/stdc++.h>
#include "Item.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
using namespace std;

int main()
{
    // Tool Functionality
    Tool t1;
    Tool t2(11, "Sword", "Iron");
    Tool t3(12, "Pickaxe", "Iron", 5);
    cout << t2.getID() << " " << t2.getName() << " " << t2.getType() << endl;

    cout << t3.getDurability() << endl;
    t3.useTool();
    t3.useTool();
    t3.setDurability(11);
    t3.printInfo();

    cout << t1.getID() << " " << t1.getName() << " " << t1.getType() << endl;
    cout << t2.getID() << " " << t2.getName() << " " << t2.getType() << endl;
    cout << t3.getID() << " " << t3.getName() << " " << t3.getType() << endl;
    
    // NonTool Functionality
    NonTool nt1;
    NonTool nt2(2, "LOG", "OAK");
    NonTool nt3(3, "PLANK", "OAK", 64);

    cout << nt2.getID() << " " << nt2.getName() << " " << nt2.getType() << endl;
    cout << nt1.getQuantity() << endl;
    nt2.takeItem(2);
    nt3.takeItem(32);

    cout << nt2.getQuantity() << endl;
    nt2.addItem(9);
    nt2.printInfo();

    nt3.takeItem(32);

    nt2.addItem(2);

    nt2.addItem(64);

    nt1.takeItem(3);
    cout << nt1.getID() << " " << nt1.getName() << " " << nt1.getType() << endl;
    cout << nt2.getID() << " " << nt2.getName() << " " << nt2.getType() << endl;
    cout << nt3.getID() << " " << nt3.getName() << " " << nt3.getType() << endl;

    return 0;
}