// #include <bits/stdc++.h>
// #include "Item.hpp"
// #include "Tool.hpp"
// #include "NonTool.hpp"
// using namespace std;

// int main()
// {
//     // Tool Functionality
//     Tool t;
//     Tool t2(11, "Sword", "Iron");
//     Tool t3(12, "Pickaxe", "Iron", 5);
//     cout << t2.getID() << " " << t2.getName() << " " << t2.getType() << endl;

//     cout << t3.getDurability() << endl;
//     t3.useTool();
//     t3.useTool();
//     t3.printInfo();

//     // NonTool Functionality
//     NonTool nt;
//     NonTool nt2(2, "LOG", "OAK");
//     NonTool nt3(3, "PLANK", "OAK", 64);

//     cout << nt2.getID() << " " << nt2.getName() << " " << nt2.getType() << endl;
//     cout << nt.getQuantity() << endl;
//     nt2.takeItem(2);
//     nt3.takeItem(32);

//     cout << nt2.getQuantity() << endl;
//     nt2.addItem(9);
//     nt2.printInfo();
//     cout << nt3 << endl;

//     return 0;
// }

#include <iostream>
#include "inventory.hpp"
#include "tool.hpp"
#include "NonTool.hpp"
using namespace std;

int main() {
    inventory temp;
    NonTool nt3(3, "PLANK", "OAK", 32);
    Tool t3(12, "Pickaxe", "Tools", 5);
    NonTool nt4(3, "PLANK", "OAK", 1);
    temp.addInventory(nt3);
    cout << "1" << temp.getNeff() << endl;
    temp.addInventory(t3);
    cout << "2" << temp.getNeff() << endl;
    temp.addInventory(nt4, 2);
    cout << "3" << temp.getNeff() << endl;
    temp.displayInventory();
    bool hai = temp.pileInventory(2, 0);
    cout << "hai" << hai << endl;
    cout << "4" << temp.getNeff() << endl;
    temp.displayInventory();
    temp.exportInventory("example.txt");
}