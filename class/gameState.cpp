#include "gameState.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

#define MAX_KOLOM 3

GameState::GameState(){};

GameState::GameState(string config_path)
{
    ifstream itemConfigFile(config_path + "/item.txt");
    for (string line; getline(itemConfigFile, line);)
    {
        this->inv.addItemDict(line);
    }
    for (const auto &entry :
         filesystem::directory_iterator(config_path + "/recipe"))
    {
        // cout << entry.path() << endl;
        ifstream itemConfigFile(entry.path());
        string isi_resep;
        string ukuran;
        getline(itemConfigFile, ukuran);
        isi_resep += ukuran+" ";
        int kolom = (int)ukuran[2] - '0';
        int baris = (int)ukuran[0] - '0';
        for (int j = 0; j < baris; j++)
        {
            string line;
            getline(itemConfigFile, line);
            isi_resep += line;
            for (int i = kolom; i <MAX_KOLOM ; i++)
            {
                isi_resep += " -";
            }

            isi_resep += " ";
        }
        string line;
        getline(itemConfigFile, line);
        isi_resep+=line+" ";
        this->craftingTable.addResep(Resep(isi_resep));
    }
}

void GameState::commandHandler()
{
    string command;
    cout << "Masukkan Input: ";
    cin >> command;
    if (command == "SHOW")
    {
        inv.showInventory();
    }
    else if (command == "GIVE")
    {
        string nama;
        int jumlah;
        cin >> nama >> jumlah;
        give(nama, jumlah);
    }
    else if (command == "DISCARD")
    {
        string id_inventory;
        int jumlah;
        cin >> id_inventory >> jumlah;
        if (id_inventory[0] == 'I')
        {
            id_inventory.erase(0, 1);
            discard(std::stoi(id_inventory), jumlah);
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
    else if (command == "MOVE")
    {
        // move();

        // DARI KAKAKNYA, HAPUS KALO UDAH GA PERLU
        string slotSrc;
        int slotQty;
        string slotDest;
        // need to handle multiple destinations
        cin >> slotSrc >> slotQty >> slotDest;
        cout << "TODO" << endl;
    }
    else if (command == "USE")
    {
        // Get Inventory Id (1..27)
        int invId;
        cin >> invId ;

        // Use tool
        try
        {
            use(invId);
        }
        catch (const char *e)
        {
            std::cerr << e << '\n';
        }
    }
    else if (command == "CRAFT")
    {
        pair<string,int> crafted = craftingTable.craft();
        if (crafted.first != ""){
            cout << "Item Created";
            give(crafted.first, crafted.second);
        }
        else{
            cout << "Item Not Created!";
        }
    }
    else if (command == "EXPORT")
    {
        string filename;
        cin >> filename;
        inv.exportInventory(filename);
    }
    else
    {
        // throw ivalidCommand
        cout << "Invalid command" << endl;
    }
}

void GameState::use(int invId)
{
    // mau pake try n catch atau abc
    // cara ngecek invId valid
    // ngecek item yg diambil itu object yang sama(durabilty == 0)
    //cek struktur dict, searchDict ada yg diganti 1->2
    
    Item& it = *inv.getInventoryPtr(invId-1);
    if(inv.isTool(invId-1))
    {
        it.setQuantityDurability(it.getQuantityDurability()-1);
        if (it.getQuantityDurability() == 0)
        {
            Item* temp_used;
            temp_used = inv.takeInventory(it);
            temp_used->printInfo();
        }
    }
    else 
    {
        throw "Choose Tool not Non-Tool";
    }
}

void GameState::give(string nama, int jumlah)
{
    try
    {
        Item *it = this->inv.searchDict(nama, jumlah);
        this->inv.addInventory(*it);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
}

void GameState::discard(int id_inventory, int jumlah)
{
    this->inv.takeInventory(id_inventory, jumlah);
}