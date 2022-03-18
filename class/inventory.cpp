#include <iostream>
#include "inventory.hpp"
using namespace std;

// Constructor
inventory::inventory() {
    this->inventories = new Item*[27];
    for (int i = 0; i < 27; i++) {
        this->inventories[i] = NULL;
    }
    this->neff = 0;
    this->itemDict;
}
inventory::inventory(const inventory& inv) {
    this->neff = inv.neff;
    this->inventories = new Item*[27];
    for (int i = 0; i < this->neff; i++) {
        this->inventories[i] = inv.inventories[i];
    }
}
inventory::~inventory() {
    delete[] this->inventories;
    this->neff = 0;
}

// Getter and Setter
Item& inventory::getInventory(int id) {
    return *this->inventories[id];
}
void inventory::setInventory(int id, Item& value) {
    this->inventories[id] = &value;
}

int inventory::getNeff() const {
    return this->neff;
}

// Predicate checking
bool inventory::isFull() {
    return (this->neff >= 27);
}
bool inventory::isTool(int idx){ // If false --> NonTool
    return (this->inventories[idx]->getType() == "Tools");
}

// Functions
// Add item to inventory
// 1. add item, unknown slotID
void inventory::addInventory(Item& other) {
    int i = 0;
    // Skip item with different ID while not out of inventories' bound,
    // If NonTool, skip if sum of other's quantity and its quantity exceeds 64
    // If Tool, skip
    // If initially empty, skip
    while ((this->neff > 0 && i < this->neff)) {
        if (!this->isTool(i) && this->inventories[i]->getID() == other.getID() 
            && this->inventories[i]->getQuantityDurability()+other.getQuantityDurability() <= 64) {
            break;
        }
        else {
            i++;
        }
    }

    // Found item with same ID, if NonTool the sum doesn't exceeds 64, not Tool
    // or i >= inventories size (max 27)
    // or first item (initially empty)
    if (i >= this->neff && i < 27) {
        // Add to new slot
        this->setInventory(i, other);
        this->neff++;
    }
    else if (i >= this->neff && i >= 27) {
        // Can't add anymore
        cout << "Inventory is Full!" << endl;
    }
    else {
        // Add to slot i
        int total = this->inventories[i]->getQuantityDurability()+other.getQuantityDurability();
        this->inventories[i]->setQuantityDurability(total);
    }
}
// 2. add item to specific inventory ID
void inventory::addInventory(Item& other, int slotID) {
    bool added = false;
    // add to currently present item
    if (this->neff > slotID) {
        Item* temp = this->inventories[slotID];
        // If the item in slotID inventory is same item, NonTool, and addition result <= 64
        // can add item in same slotID
        if (temp->getID() == other.getID() && !this->isTool(slotID)
            && temp->getQuantityDurability() + other.getQuantityDurability() <= 64) {
            int total = other.getQuantityDurability() + this->inventories[slotID]->getQuantityDurability();
            this->inventories[slotID]->setQuantityDurability(total);
            added = true;
        }
    }
    // Add new item in slotID index
    if (!added && !this->isFull()) {
        if (this->neff < slotID) {
            this->setInventory(this->neff, other);
        }
        else {
            if (this->neff > slotID) {
                // shift to right latter elements than or equal to slotID
                for (int i = this->neff; i > slotID; i++) {
                    this->setInventory(i, *this->inventories[i-1]);
                }
            }
            this->setInventory(slotID, other);
        }
        this->neff++;
    }
}

// Take item from inventory
bool inventory::takeInventory(Item& other) {
    bool taken = false;
    if (this->neff > 0) {
        int i = 0;
        // Skip item with different ID while not out of inventories' bound,
        // If NonTool, skip if num > quantity
        // while (this->inventories[i]->getID() != other.getID() && i < this->neff
        //         && !this->isTool(i) && this->inventories[i]->getQuantityDurability() < other.getQuantityDurability() ) {
        //     i++;
        // }
        while (i < this->neff) {
            if (this->inventories[i]->getID() == other.getID()) {
                if (this->isTool(i)) {
                    break;
                }
                else if (this->inventories[i]->getQuantityDurability() >= other.getQuantityDurability()) {
                    break;
                }
                else {
                    i++;
                }
            }
            else {
                i++;
            }
        }

        // Found item with same ID, if NonTool, the quantity is more than num
        // or i >= inventories size (max 27)
        if (i < this->neff) {
            // Take in slot i
            int total = this->inventories[i]->getQuantityDurability() - other.getQuantityDurability();
            if (total > 0) {
                this->inventories[i]->setQuantityDurability(total);
                taken = true;
            }
            else if (total == 0) {
                for (int j = i; j < this->neff; j++) {
                    this->setInventory(j, *this->inventories[j+1]);
                }
                taken = true;
                this->neff--;
            }
        }

        if (!taken) {
            // Nothing to delete
            cout << "Can't Take Items!" << endl;
        }
    }
    return taken;
}
bool inventory::takeInventory(int slotID, int quantity) {
    bool taken = false;

    if (slotID < this->neff && this->inventories[slotID]->getQuantityDurability() >= quantity) {
        int total = this->inventories[slotID]->getQuantityDurability() - quantity;
        if (!this->isTool(slotID) && total > 0) {
            this->inventories[slotID]->setQuantityDurability(total);
            taken = true;
        }
        else if (this->isTool(slotID) || (!this->isTool(slotID) && total == 0)) {
            for (int j = slotID; j < this->neff; j++) {
                this->setInventory(j, *this->inventories[j+1]);
            }
            taken = true;
            this->neff--;
        }
    }

    if (!taken) {
        // Nothing to delete
        cout << "Can't Take Items!" << endl;
    }

    return taken;
}

// Move item from src slot to dest slot
bool inventory::pileInventory(int idx_src, int idx_dest) {
    // Only take if NonTool, shares same ID, and total quantity <= 64
    Item* temp_src = this->inventories[idx_src];
    Item* temp_dest = this->inventories[idx_src];
    if (temp_src->getID() == temp_dest->getID() && temp_src->getType() != "Tool"
        && temp_src->getQuantityDurability()+temp_dest->getQuantityDurability() <= 64) {
        // Take item from inventory
        if (this->takeInventory(idx_src, temp_src->getQuantityDurability())) {
            // successfully taken, move to other inventory slot
            this->addInventory(*temp_src, idx_dest);
            return true;
        }
    }
    return false;
}

// Output
void inventory::displayInventory() {
    for(int i = 0; i < this->neff; i++) {
        this->inventories[i]->printInfo();
    }
}
void inventory::exportInventory(string filename) {
    ofstream exportFile;
    exportFile.open (filename);
    for (int i = 0; i < 27; i++) {
        if (i >= this->neff) {
            exportFile << "0:0\n";
        }
        else {
            exportFile << this->inventories[i]->getID() << ":" << this->inventories[i]->getQuantityDurability() << "\n";
        }
    }
    exportFile.close();
}

// Dictionary
void inventory::addItemDict(string line){
    int i=0;
    string temp[4];
    for (auto x : line)
    {
        if(x == ' '){
            i++;
        }
        else{
            temp[i]+=x;
        }
    }
    if(temp[3]=="Tool"){
        temp[2]==temp[3];
    }
    if(temp[2]=="-"){
        temp[2]=temp[1];
    }
    // this->itemDict.insert(pair<string,tuple<int,string,string>>(temp[1],(std::stoi(temp[0]),temp[2],temp[3])));
    this->itemDict.insert(make_pair(temp[1], make_tuple(stoi(temp[0]),temp[2],temp[3])));
}

Item* inventory::searchDict(string Nama, int jumlah){
    /*
    Exceptionnya masih belom bagus
    Pemakaian sementara sebelom dibenerin kayak gini:
    try
    {
        Item *it = this->inv.searchDict(nama);
        this->inv.addInventory(*it);
        this->inv.displayInventory();
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    */
    if(this->itemDict.find(Nama)==this->itemDict.end()){
        throw "Item not Found";
    }
    else{
        tuple<int, string, string> temp;
        temp = this->itemDict.at(Nama);
        if (get<2>(temp)=="TOOL")
        {
            return new Tool(get<0>(temp), Nama, get<1>(temp));
        }
        else{
            return new NonTool(get<0>(temp), Nama, get<1>(temp), jumlah);
        }
    }
}