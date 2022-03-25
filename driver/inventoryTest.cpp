#include <iostream>
#include "../class/inventory.cpp"
#include "../class/tool.cpp"
#include "../class/NonTool.cpp"
using namespace std;

int main()
{
    inventory temp;
    temp.printInfoInventory();

    NonTool nt1(3, "PLANK", "OAK", 65);
    Tool t1(12, "Pickaxe", "Tools", 5);
    NonTool nt2(3, "PLANK", "OAK", 1);

    Item *temp_taken;

    temp.addInventory(nt1);
    temp.printInfoInventory();
    temp_taken = temp.takeInventory(nt1);
    temp.printInfoInventory();
    temp.addInventory(nt1);

    temp.addInventory(t1);
    temp.printInfoInventory();
    temp_taken = temp.takeInventory(t1);
    temp.printInfoInventory();
    temp.addInventory(t1);

    temp.addInventory(nt2);
    temp.printInfoInventory();
    temp_taken = temp.takeInventory(nt2);
    temp.printInfoInventory();
    temp.addInventory(nt2);

    temp.addInventory(nt2, 3);
    temp.printInfoInventory();
    temp_taken = temp.takeInventory(3, 1);
    temp.printInfoInventory();
    temp.addInventory(nt2, 3);

    cout << "is Inventory full? " << temp.isFull() << endl;
    cout << "is Inventory empty? " << temp.isEmpty(4) << endl;
    cout << "is Inventory slot 2 a Tool ? " << temp.isTool(1) << endl;

    bool successPiling = temp.pileInventory(2, 0);
    cout << "Success Piling inventory item! " << successPiling << endl;
    temp.printInfoInventory();

    temp.exportInventory("tests/example.txt");

    temp.~inventory();
}