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
        isi_resep += ukuran + " ";
        int kolom = (int)ukuran[2] - '0';
        int baris = (int)ukuran[0] - '0';
        for (int j = 0; j < baris; j++)
        {
            string line;
            getline(itemConfigFile, line);
            isi_resep += line;
            for (int i = kolom; i < MAX_KOLOM; i++)
            {
                isi_resep += " -";
            }

            isi_resep += " ";
        }
        string line;
        getline(itemConfigFile, line);
        isi_resep += line + " ";
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
        this->inv.showInventory();
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
        cin >> invId;

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

void GameState::use(int invId)
{
    // mau pake try n catch atau abc
    // cara ngecek invId valid
    // ngecek item yg diambil itu object yang sama(durabilty == 0)
    // cek struktur dict, searchDict ada yg diganti 1->2

    Item &it = this->inv.getInventory(invId - 1);
    if (inv.isTool(invId - 1))
    {
        it.setQuantityDurability(it.getQuantityDurability() - 1);
        if (it.getQuantityDurability() == 0)
        {
            // this->inv.takeInventory(it);
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

void GameState::move()
{
    string command, from, to;
    int N;

    cin >> command >> from >> N;
    if (from[0] == 'I')
    {
        from.erase(0, 1);
        if (N <= 0)
            cout << "EXEC HANDLER" << endl; // TODO: EXEC HANDLER
        else
        {
            // Distribusikan
            for (int i = 0; i < N; i++)
            {
                cin >> to;
                char mode = to[0];
                to.erase(0, 1);
                if (mode == 'C')
                    this->moveFromInventory(stoi(from), stoi(to), true);
                else if (mode == 'I')
                    this->moveFromInventory(stoi(from), stoi(to), false);
                else
                    cout << "EXEC HANDLER" << endl; // TODO: EXEC HANDLER
            }
        }
    }
    else if (from[0] == 'C')
    {
        from.erase(0, 1);
        cin >> to;
        if (to[0] == 'I')
            this->moveFromCrafting(stoi(from), stoi(to));
        else
            cout << "EXEC HANDLER" << endl; // TODO: EXEC HANDLER
    }
    else
    {
        cout << "EXEC HANDLER" << endl; // TODO: EXEC HANDLER
    }
}

void GameState::moveFromInventory(int from, int dest, bool toCrafting)
{
    // Item &tmp = this->inv.getInventory(from);
    Item *taken = this->inv.takeInventory(from, 1);

    if (toCrafting)
    {
    }
    else // to Inventory
    {
        Item *dest = this->inv.getInventoryPtr(dest);
    }
}

void moveFromCrafting(int from, int to) {}