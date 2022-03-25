#include <bits/stdc++.h>
#include "../class/Item.cpp"
#include "../class/Tool.cpp"
#include "../class/NonTool.cpp"
using namespace std;

int main()
{
    // Tool Functionality
    cout << "======= TOOL TESTING =======" << endl;
    Tool t1;
    Tool t2(23, "IRON_SWORD", "TOOL");
    Tool t3(12, "Pickaxe", "TOOL", 1);
    cout << "================DEFAULT TOOL CONSTRUCTOR===============" << endl;
    cout << t1;
    cout << "===============CREATE IRON SWORD DEFAULT===============" << endl;
    cout << t2;
    cout << "==========CREATE WOODEN PICKAXE 1 DURABILITY===========" << endl;
    cout << t3;
    cout << "======================USE PICKAXE======================" << endl;
    t3.useTool();
    cout << t3;
    cout << "====================OVERUSE PICKAXE====================" << endl;
    try
    {
        t3.useTool();
    }
    catch (exception *e)
    {
        cout << e->what();
        cout << t3;
    }

    // NonTool Functionality
    cout << "======= NONTOOL TESTING =======" << endl;
    NonTool nt1;
    NonTool nt2(1, "OAK_LOG", "LOG");
    NonTool nt3(3, "OAK_PLANK", "PLANK", 62);

    cout << "Informasi nontool kedua yang dibuat: ";
    cout << nt2.getID() << " " << nt2.getName() << " " << nt2.getType() << endl;
    cout << "Quantity nontool pertama dengan default constructor: " << nt1.getQuantity() << endl;

    cout << "Mengambil nontool 2 yang berjumlah 1 sebanyak 2 buah" << endl;
    nt2.takeItem(2);
    cout << "Mengambil nontool 3 yang berjumlah 64 sebanyak 32 buah" << endl;
    nt3.takeItem(32);

    cout << "Quantity nontool kedua setelah diambil: " << nt2.getQuantity() << endl;

    cout << "Menambahkan nontool 2 sebanyak 9 buah" << endl;
    nt2.addItem(9);
    cout << "Quantity item 2: " << nt2.getQuantity() << endl;

    cout << "Mengambil nontool 3 sebanyak 32 buah " << endl;
    nt3.takeItem(32);
    cout << "Quantity item 2: " << nt3.getQuantity() << endl;
    cout << "Menambahkan nontool 2 sebanyak 2 buah" << endl;
    nt2.addItem(2);
    cout << "Menambahkan nontool 2 sebanyak 64 buah" << endl;
    nt2.addItem(64);
    cout << "Quantity item 2: " << nt2.getQuantity() << endl;
    cout << "Mengambil nontool 3 sebanyak 3 buah " << endl;
    nt1.takeItem(3);

    cout << "State akhir nontools: ID NAME TYPE" << endl;
    cout << nt1.getID() << " " << nt1.getName() << " " << nt1.getType() << endl;
    cout << nt2.getID() << " " << nt2.getName() << " " << nt2.getType() << endl;
    cout << nt3.getID() << " " << nt3.getName() << " " << nt3.getType() << endl;
    cout << "=== END OF NONTOOL TESTING ===" << endl;
    //
    cout << "=============DEFAULT NONTOOL CONSTRUCTOR==============" << endl;
    cout << nt1;
    cout << "================CREATE OAK LOG DEFAULT================" << endl;
    cout << nt2;
    cout << "==================CREATE OAK PLANK 62=================" << endl;
    cout << nt3;
    cout << "====================TAKE OAK PLANK 1==================" << endl;
    nt3.takeItem(1);
    cout << nt3;
    cout << "====================ADD OAK PLANK 1===================" << endl;
    nt3.addItem(1);
    cout << nt3;
    cout << "==================OVERADD OAK PLANK 10================" << endl;
    try
    {
        nt3.addItem(10);
    }
    catch (exception *e)
    {
        cout << e->what();
    }
    cout << nt3;
    cout << "===================OVERTAKE OAK PLANK================" << endl;
    try
    {
        nt3.takeItem(65);
    }
    catch (exception *e)
    {
        cout << e->what();
    }
    cout << nt3;

    return 0;
}