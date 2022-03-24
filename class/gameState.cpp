#include "gameState.hpp"
#include "exception.hpp"
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
        this->craftingTable.showCraftingTable();
        this->inv.
        printInfoInventory();
    }
    else if (command == "SHOW_INFO")
    {
        for(int i  = 0; i < inv.getNeff(); i++)
        {
	    Item& temp = inv.getInventory(i);
            cout << temp.getID() << " " 
                 << temp.getName() << " "
                 << temp.getType() << endl;
        }
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
        cout << crafted.first << " " << crafted.second;
        if (crafted.first != "")
        {
            cout << "Item Created\n";
            give(crafted.first, crafted.second);
        }
        else
        {
            cout << "Item Not Created!\n";
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
            //temp_used->printInfo();
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
    cout<<it->getType()<<endl;
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

    //First param input validator
    while (!(cin >> from))
    {
        throw new InvalidCommand();
        cin.clear();
    }

    //String input validator
    while (!(cin >> N))
    {
        throw new InvalidCommand();
        cin.clear();
    }

    // Membagikan ke inventory atau crafting table
    cout << from << endl;
    char type = from[0];
    int pos = stoi(from.erase(0,1));
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

                //Mendapatkan list of inventory/crafting yang akan didistrirbusikan
                getline(cin, namaSlot);
                namaSlot.erase(0,1);
                for(auto ch : namaSlot)
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

                while(!isFull && remainingItem > 0)
                {
                    // Mengiterasikan elemen satu per satu 
                    to = slots[i%slots.size()];
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

// void GameState::moveFromInventory(int from, int to, bool toCrafting)
// {
//     if (toCrafting)
//     {
//         Item *taken = this->inv.getInventoryPtr(from);
//         if (taken->getType() == "TOOL")
//         {
//             Tool tmpItem(taken->getID(), taken->getName(), taken->getType(), taken->getQuantityDurability());
//             this->craftingTable.addToCraftingTable(tmpItem, to);

//             Item &empty = emptyTool;
//             this->inv.setInventory(from, empty);
//         }
//         else
//         {
//             Item *tk = this->inv.takeInventory(from, 1);
//             NonTool tmpItem(tk->getID(), tk->getName(), tk->getType(), 1);
//             this->craftingTable.addToCraftingTable(tmpItem, to);
//         }
//     }
//     else // to Inventory
//     {
//         Item *taken = this->inv.getInventoryPtr(from);
//         Item *dest = this->inv.getInventoryPtr(to);
//         // if (dest->getType() != "Empty")
//         //     this->inv.pileInventory(from, to);
// //else 
//         if (taken->getType() == "TOOL")
//         {
//             Tool tmpItem(taken->getID(), taken->getName(), taken->getType(), taken->getQuantityDurability());
//             Item &tmp = tmpItem;
//             this->inv.setInventory(to, tmp);

//             Item &empty = emptyTool;
//             this->inv.setInventory(from, empty);
//         }
//         else
//         {
//             Item *tk = this->inv.takeInventory(from, 1);
//             NonTool tmpItem(tk->getID(), tk->getName(), tk->getType(),1);
//             Item &tmp = tmpItem;
//             this->inv.addInventory(tmp, to);
//         }
//     }

//     // this->inv.showInventory();
//     // this->craftingTable.showCraftingTable();
// }

// void GameState::moveFromCrafting(int from, int to)
// {
//     Item *taken = this->craftingTable.takeItem(from);
//     Item *dest = this->inv.getInventoryPtr(to);
//     if (taken->getType() == "TOOL")
//     {
//         Tool tmpItem(taken->getID(), taken->getName(), taken->getType(), taken->getQuantityDurability());
//         Item &tmp = tmpItem;
//         if (dest->getType() != "Empty")
//             cout << "EXEC HANDLER" << endl; // TODO: EXEC HANDLER
//         else
//             this->inv.setInventory(to, tmp);
//     }
//     else
//     {
//         int total = taken->getQuantityDurability();
//         NonTool tmpItem(taken->getID(), taken->getName(), taken->getType(), 1);
//         Item &tmp = tmpItem;
//         if (dest->getType() != "Empty")
//             this->inv.addInventory(tmp, to);
//         else
//             this->inv.setInventory(to, tmp);

//         NonTool tmpNew(taken->getID(), taken->getName(), taken->getType(), total - 1);
//         delete taken;
//         if (total - 1 > 0)
//             this->craftingTable.addToCraftingTable(tmpNew, to);
//     }

//     // this->inv.showInventory();
//     // this->craftingTable.showCraftingTable();
// }

void GameState::moveTo(int from, int to, bool fromCrafting, bool toCrafting){
    Item* taken;
    if (fromCrafting){
        taken = this->craftingTable.takeItem(from,1);
    }
    else{
        Item* temp = this->inv.getInventoryPtr(from);
        if (temp->getType() == "TOOL"){
            taken = this->inv.takeInventory(from,temp->getQuantityDurability());
        }
        else{
            taken = this->inv.takeInventory(from,1);
        }
    }
    
    if (taken->getType() == "TOOL"){
        Tool tmpItem(taken->getID(), taken->getName(), taken->getType(), taken->getQuantityDurability());
        if (toCrafting){
            craftingTable.addToCraftingTable(tmpItem, to);
        }
        else{
            inv.addInventory(tmpItem,to);
        }
    }
    else{
        NonTool tmpItem(taken->getID(), taken->getName(), taken->getType(), 1);
        if (toCrafting){
            craftingTable.addToCraftingTable(tmpItem, to);
        }
        else{
            inv.addInventory(tmpItem,to);
        }
    }
}