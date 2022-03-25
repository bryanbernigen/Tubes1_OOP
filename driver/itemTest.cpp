#include <bits/stdc++.h>
#include "../class/item.hpp"
#include "../class/tool.hpp"
#include "../class/NonTool.hpp"
using namespace std;

int main()
{
    // Tool Functionality
    cout << "======= TOOL TESTING =======" << endl;
    Tool t1;
    Tool t2(11, "Sword", "Iron");
    Tool t3(12, "Pickaxe", "Iron", 5);
    cout << "Informasi tool kedua yang dibuat: ";
    cout << t2.getID() << " " << t2.getName() << " " << t2.getType() << endl;

    cout << "Durability tool 3: " << t3.getDurability() << endl;
    cout << "Menggunakan tool 3 sebanyak 2x" << endl;
    t3.useTool();
    t3.useTool();
    cout << "Durability tool 3: " << t3.getDurability() << endl;
    cout << "Mengubah durability tool 3 menjadi 11" << endl;
    t3.setDurability(11);

    cout << "State akhir tools: ID NAME TYPE" << endl;
    cout << t1.getID() << " " << t1.getName() << " " << t1.getType() << endl;
    cout << t2.getID() << " " << t2.getName() << " " << t2.getType() << endl;
    cout << t3.getID() << " " << t3.getName() << " " << t3.getType() << endl;
    cout << "=== END OF TOOL TESTING ===" << endl;

    // NonTool Functionality
    cout << "======= NONTOOL TESTING =======" << endl;
    NonTool nt1;
    NonTool nt2(2, "LOG", "OAK");
    NonTool nt3(3, "PLANK", "OAK", 64);

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

    return 0;
}