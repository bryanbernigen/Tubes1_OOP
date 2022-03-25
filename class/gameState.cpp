#include "gameState.hpp"
#include "exception.hpp"
#include <filesystem>
#include <vector>
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

void GameState::commandHandler(string command)
{
    if (command == "SHOW")
    {
        this->craftingTable.showCraftingTable();
        this->inv.printInfoInventory();
    }
    else if (command == "INFO")
    {
        cout << setfill(' ') << left
             << setw(3) << "ID"
             << " "
             << setw(12) << "Name"
             << " "
             << setw(12) << "Type"
             << " "
             << "Inv ID" << endl;
        for (int i = 0; i < inv.getNeff(); i++)
        {
            Item &temp = inv.getInventory(i);
            cout << setfill(' ')
                 << setw(3) << temp.getID() << " "
                 << setw(12) << temp.getName() << " "
                 << setw(12) << temp.getType() << " "
                 << i << endl;
        }

        cout << right;
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
            throw new InvalidCommand();
        }
    }
    else if (command == "MOVE")
    {
        move();
    }
    else if (command == "USE")
    {
        // Get Inventory Id (1..27)
        int invId;

        // Use tool
        while (!(cin >> invId))
        {
            throw new InvalidCommand();
            cin.clear();
        }
        use(invId);
    }
    else if (command == "CRAFT")
    {
        pair<string, int> crafted = craftingTable.craft();
        give(crafted.first, crafted.second);
    }
    else if (command == "EXPORT")
    {
        string filename;
        cin >> filename;
        cout << "Exporting at: " << filename << endl;
        filename += ".txt";
        inv.exportInventory(filename);
    }
    else if (command == "CHECK")
    {
        string location;
        cin >> location;
        if (location[0] == 'C' || location[0] == 'I')
        {
            Item* item;
            char mode = location[0];
            location.erase(0,1);
            if (mode == 'C') item = craftingTable.getCrafting(stoi(location));
            else item = inv.getInventoryPtr(stoi(location));
            if (item->getType() == "TOOL"){
                Tool t(item->getID(), item->getName(), item->getType(), item->getQuantityDurability());
                cout << t;
            }
            else{
                NonTool t(item->getID(), item->getName(), item->getType(), item->getQuantityDurability());
                cout << t;
            }
        }
        else{
            throw new InvalidCommand();
        }
    }
    else
    {
        // throw ivalidCommand
        throw new InvalidCommand();
    }
}

void GameState::use(int invId)
{
    // mau pake try n catch atau abc
    // cara ngecek invId valid
    // ngecek item yg diambil itu object yang sama(durabilty == 0)
    // cek struktur dict, searchDict ada yg diganti 1->2

    Item &it = *inv.getInventoryPtr(invId - 1);
    if (inv.isTool(invId - 1))
    {
        it.setQuantityDurability(it.getQuantityDurability() - 1);
        if (it.getQuantityDurability() == 0)
        {
            Item *temp_used;
            temp_used = inv.takeInventory(it);
            // temp_used->printInfo();
        }
    }
    else
    {
        throw new InvalidUseCommand();
    }
}

void GameState::give(string nama, int jumlah)
{
    Item *it = this->inv.searchDict(nama, jumlah);
    this->inv.addInventory(*it);
}

void GameState::discard(int id_inventory, int jumlah)
{
    this->inv.takeInventory(id_inventory, jumlah);
}

void GameState::move()
{
    string from, to;
    int N;

    // First param input validator
    while (!(cin >> from))
    {
        throw new InvalidCommand();
        cin.clear();
    }

    // String input validator
    while (!(cin >> N))
    {
        throw new InvalidCommand();
        cin.clear();
    }

    // Membagikan ke inventory atau crafting table
    char type = from[0];
    int pos = stoi(from.erase(0, 1));
    if (type == 'I' || type == 'C')
    {
        if (N < 0)
        {
            // Jumlah negatif tidak valid
            throw new InvalidSlotAmount();
        }
        if (N > 0)
        {
            if (type == 'I' && inv.getInventory(pos).getQuantityDurability() < N)
            {
                // Jumlah move item melebihi jumlah di inventory
                throw new InvalidSlotAmount();
            }
            else if (type == 'C' && craftingTable.getCrafting(pos)->getQuantityDurability() < N)
            {
                // Jumlah moe item melebihi jumlah di crafting table
                throw new InvalidSlotAmount();
            }
            else
            {
                // Distribusikan
                string namaSlot;
                vector<string> slots;
                string temp;

                // Mendapatkan list of inventory/crafting yang akan didistrirbusikan
                getline(cin, namaSlot);
                namaSlot.erase(0, 1);
                for (auto ch : namaSlot)
                {
                    if (ch == ' ')
                    {
                        slots.push_back(temp);
                        temp = "";
                        continue;
                    }
                    temp += ch;
                }
                slots.push_back(temp);

                // Membagikan item ke tiap elemen dalam list
                int remainingItem = N;
                bool isFull = false;
                int i = 0;

                while (!isFull && remainingItem > 0)
                {
                    // Mengiterasikan elemen satu per satu
                    to = slots[i % slots.size()];
                    i++;
                    remainingItem--;
                    char mode = to[0];
                    to.erase(0, 1);
                    this->moveTo(pos, stoi(to), type == 'C', mode == 'C');
                }
            }
        }
    }
    else
    {
        throw new InvalidCommand();
    }
}

void GameState::moveTo(int from, int to, bool fromCrafting, bool toCrafting)
{
    Item *taken;
    if (fromCrafting)
    {
        taken = this->craftingTable.getCrafting(from);
    }
    else
    {
        taken = this->inv.getInventoryPtr(from);
        // if (temp->getType() == "TOOL"){
        //     taken = this->inv.getInventoryPtr(from,temp->getQuantityDurability());
        // }
        // else{
        //     taken = this->inv.getInventory(from,1);
        // }
    }

    if (taken->getType() == "TOOL")
    {
        Tool tmpItem(taken->getID(), taken->getName(), taken->getType(), taken->getQuantityDurability());
        if (toCrafting)
        {
            craftingTable.addToCraftingTable(tmpItem, to);
        }
        else
        {
            inv.addInventory(tmpItem, to);
        }
        if (fromCrafting)
        {
            this->craftingTable.takeItem(from, 1);
        }
        else
        {
            this->inv.takeInventory(from, taken->getQuantityDurability());
        }
    }
    else
    {
        NonTool tmpItem(taken->getID(), taken->getName(), taken->getType(), 1);
        if (toCrafting)
        {
            craftingTable.addToCraftingTable(tmpItem, to);
        }
        else
        {
            inv.addInventory(tmpItem, to);
        }
        if (fromCrafting)
        {
            this->craftingTable.takeItem(from, 1);
        }
        else
        {
            this->inv.takeInventory(from, 1);
        }
    }
}