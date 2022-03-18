#include "gameState.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

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
        for (string line; getline(itemConfigFile, line);)
        {
            isi_resep += line;
            isi_resep += " ";
        }
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
        // show();
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
            id_inventory.erase(0,1);
            discard(std::stoi(id_inventory),jumlah);
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
        // use();
    }
    else if (command == "CRAFT")
    {
        // craft();

        // DARI KAKAKNYA, HAPUS KALO UDAH GA PERLU
        cout << "TODO" << endl;
    }
    else if (command == "EXPORT")
    {
        // export();

        // DARI KAKAKNYA, HAPUS KALO UDAH GA PERLU
        string outputPath;
        cin >> outputPath;
        ofstream outputFile(outputPath);

        // hardcode for first test case
        outputFile << "21:10" << endl;
        outputFile << "6:1" << endl;
        for (int i = 2; i < 27; i++)
        {
            outputFile << "0:0" << endl;
        }

        cout << "Exported" << endl;
    }
    else
    {
        // throw ivalidCommand
        cout << "Invalid command" << endl;
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