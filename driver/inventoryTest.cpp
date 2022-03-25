#include <iostream>
#include "../class/item.cpp"
#include "../class/inventory.cpp"
#include "../class/tool.cpp"
#include "../class/NonTool.cpp"
using namespace std;

int main()
{
    inventory temp;
    temp.printInfoInventory();
    cout << endl;

    NonTool nt1(3, "PLANK", "OAK", 65);
    Tool t1(12, "Pickaxe", "Tools", 5);
    NonTool nt2(3, "PLANK", "OAK", 1);
    NonTool nt3(3, "PLANK", "OAK", 3);
    NonTool nt4(3, "PLANK", "OAK", 5);

    Item *temp_taken;

    temp.addInventory(nt1);
    temp.printInfoInventory();
    cout << endl;

    temp_taken = temp.takeInventory(nt1);
    cout << endl;
    temp_taken->printInfo();
    cout << endl;

    temp.printInfoInventory();
    cout << endl;

    temp.addInventory(t1);
    temp.printInfoInventory();
    cout << endl;

    temp_taken = temp.takeInventory(t1);
    cout << endl;
    temp_taken->printInfo();
    cout << endl;

    temp.printInfoInventory();
    cout << endl;

    temp.addInventory(nt2);
    temp.printInfoInventory();
    cout << endl;

    temp_taken = temp.takeInventory(nt3);
    temp.printInfoInventory();
    cout << endl;

    temp.addInventory(nt4, 3);
    temp.printInfoInventory();
    cout << endl;
    temp_taken = temp.takeInventory(3, 1);
    temp.printInfoInventory();
    cout << endl;

    cout << "is Inventory full? " << temp.isFull() << endl;
    cout << "is Inventory at id 4 empty? " << temp.isEmpty(4) << endl;
    cout << "is Inventory slot 2 a Tool ? " << temp.isTool(1) << endl;

    bool successPiling = temp.pileInventory(1, 0);
    cout << "Success Piling inventory item! " << successPiling << endl << endl;
    temp.printInfoInventory();

    temp.exportInventory("tests/example.out");

    temp.~inventory();
}