#include "inventory.hpp"

NonTool emptyNonTool(-1, "Empty", "Empty", 1);
Tool emptyTool(-1, "Empty", "Empty", 1);

// Constructor
inventory::inventory()
{
    this->inventories = new Item *[27];
    for (int i = 0; i < 27; i++)
    {
        this->inventories[i] = new NonTool(-1, "Empty", "Empty", 1);
    }
    this->neff = 0;
    this->itemDict;
}

// Copy Constructor
inventory::inventory(const inventory &inv)
{
    this->neff = inv.neff;
    this->inventories = new Item *[27];
    for (int i = 0; i < 27; i++)
    {
        this->inventories[i] = inv.inventories[i];
    }
}

// Assignment Operator
inventory &inventory::operator=(const inventory &inv)
{
    delete[] this->inventories;
    this->neff = inv.neff;
    this->inventories = new Item *[27];
    for (int i = 0; i < 27; i++)
    {
        this->inventories[i] = inv.inventories[i];
    }

    return *this;
}

inventory::~inventory()
{
    delete[] this->inventories;
    this->neff = 0;
}

// Getter and Setter
Item &inventory::getInventory(int id)
{
    if (id < 0 || id > 26){
        throw new IndexOutOfRange(id, "inventory");
    }
    return *this->inventories[id];
}
Item *inventory::getInventoryPtr(int id)
{
    if (id < 0 || id > 26){
        throw new IndexOutOfRange(id, "inventory");
    }
    return this->inventories[id];
}
void inventory::setInventory(int id, Item &value)
{
    if (id < 0 || id > 26){
        throw new IndexOutOfRange(id, "inventory");
    }
    this->inventories[id] = value.clone();
}

int inventory::getNeff() const
{
    return this->neff;
}
void inventory::nextNeff()
{
    if (this->isFull())
    {
        this->neff = 27;
    }
    else
    {
        bool notempty = true;
        int i = 0;
        while (notempty && i < 27)
        {
            if (isEmpty(i))
            {
                this->neff = i;
                notempty = false;
            }
            i++;
        }
    }
}

// Predicate checking
bool inventory::isFull()
{
    bool full = true;
    int i = 0;
    while (full && i < 27)
    {
        if (isEmpty(i))
        {
            full = false;
        }
        i++;
    }
    return full;
}
bool inventory::isEmpty(int idx)
{ // True if Empty
    return (this->inventories[idx]->getType() == "Empty");
}
bool inventory::isItemEmpty(Item &check)
{ // True if Empty
    return (check.getType() == "Empty");
}
bool inventory::isTool(int idx)
{ // If false --> NonTool
    return (this->inventories[idx]->getType() == "TOOL");
}
bool inventory::isItemTool(Item& other) 
{ // If false --> NonTool
    return (other.getType() == "TOOL");
}

// Functions
// Add item to inventory
// 1. add item, unknown slotID
/*
    I.S. unknown slotID, item quantity not guaranteed <= 64
    F.S. item added to inventory.
    N.B. Item can be partitioned. E.g. item with quantity of 70.
    1. There's a slot containing same item, quantity 20.
        To be added item stacked up to that slot of inventory until full.
        Current inventory's quantity = 64. Item to be added's left quantity = 50.
        Add to other slot in same manner or add to a new slot if there isn't any
        slot fullfill requirements
    2. There's not any slot containing same item.
        Add item to new slot, partition to 64 and 6 each.
*/
void inventory::addInventory(Item &other)
{
    // If NonTool, can stack
    if (!isItemTool(other)) {
        int numItem = other.getQuantityDurability();
        int i = 0;
        while (numItem > 0 && i < 27) {
            if (this->isEmpty(i)) {
                this->setInventory(this->neff, other);
                if  (other.getQuantityDurability() > 64) {
                    // item quantity exceeds 64, limit to 64
                    this->inventories[i]->setQuantityDurability(64);
                    other.setQuantityDurability(other.getQuantityDurability()-64);
                    numItem -= 64;
                }
                else {
                    // item quantity less than 64
                    this->inventories[i]->setQuantityDurability(numItem);
                    numItem -= other.getQuantityDurability();
                }
                this->nextNeff();
            }
            else if (!this->isEmpty(i) && this->inventories[i]->getID() == other.getID() && this->inventories[i]->getQuantityDurability() < 64) {
                int freeSlot = 64 - this->inventories[i]->getQuantityDurability();
                if (other.getQuantityDurability() <= freeSlot) {
                    // directly enter without partitioning
                    int total = this->inventories[i]->getQuantityDurability() + other.getQuantityDurability();
                    this->inventories[i]->setQuantityDurability(total);
                    other.setQuantityDurability(other.getQuantityDurability()-total);
                    numItem = 0;
                }
                else {
                    // partition. Fill first (as much as freeSlot)
                    int total = this->inventories[i]->getQuantityDurability() + freeSlot;
                    this->inventories[i]->setQuantityDurability(total);
                    other.setQuantityDurability(other.getQuantityDurability()-freeSlot);
                    numItem -= freeSlot;
                }
            }
            i++;
        }
        if (numItem > 0 && i >= 27) {
            // Can't add anymore
            throw new SlotFullException();
        }
    }
    // Tool, can add to new slot directly
    else {
        // as long as not full can add
        if (!this->isFull()) {
            this->setInventory(this->neff, other);
            this->nextNeff();
        }
        // in case of full, throw exception
        else {
            // Can't add anymore
            throw new SlotFullException();
        }
    }
    
}
// 2. add item to specific inventory ID
void inventory::addInventory(Item &other, int slotID)
{
    if (slotID < 0 || slotID > 26){
        throw new IndexOutOfRange(slotID, "inventory");
    }
    bool added = false;
    // add to currently present item
    if (slotID >= 0 && slotID < 27 && !isEmpty(slotID))
    {
        Item *tempItem = this->inventories[slotID];
        // If the item in slotID inventory is same item, NonTool, and addition result <= 64
        // can add item in same slotID
        if (tempItem->getID() == other.getID() && !this->isTool(slotID) && (tempItem->getQuantityDurability() + other.getQuantityDurability() <= 64))
        {
            int total = other.getQuantityDurability() + tempItem->getQuantityDurability();
            this->inventories[slotID]->setQuantityDurability(total);
            added = true;
        }
        else if (tempItem->getID() == other.getID() && !this->isTool(slotID) && tempItem->getQuantityDurability() + other.getQuantityDurability() > 64)
        {
            throw new SlotStorageInsufficient();
        }
        else if (tempItem->getID() != other.getID() && !this->isTool(slotID))
        {
            throw new ItemNotMatch();
        }
    }
    // Add new item in slotID index
    if (!added && !this->isFull())
    {
        if (this->isEmpty(slotID))
        {
            this->setInventory(slotID, other);
            this->nextNeff();
        }
        else
        {
            throw new SlotInitiallyNotEmpty();
        }
    }
}

// Take item from inventory
Tool *inventory::takeInventory(Tool &other)
{
    if (this->neff > 0)
    {
        int i = 0;

        // Skip item with different ID while not out of inventories' bound,
        // If NonTool, skip if num > quantity
        // while (this->inventories[i]->getID() != other.getID() && i < this->neff
        //         && !this->isTool(i) && this->inventories[i]->getQuantityDurability() < other.getQuantityDurability() ) {
        //     i++;
        // }
        while (i < 27)
        {
            if (this->inventories[i]->getID() == other.getID())
            {
                if ((this->isTool(i)) || (this->inventories[i]->getQuantityDurability() >= other.getQuantityDurability()))
                {
                    break;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                i++;
            }
        }

        // Found item with same ID, if NonTool, the quantity is more than num
        // or i >= inventories size (max 27)
        if (i < 27)
        {
            // Take in slot i
            int total = this->inventories[i]->getQuantityDurability() - other.getQuantityDurability();
            if (total > 0)
            {
                this->inventories[i]->setQuantityDurability(total);
            }
            else if (total == 0)
            {
                this->setInventory(this->neff, emptyNonTool);
                this->nextNeff();
            }
            return &other;
        }
        else
        {
            throw new ItemNotFound();
        }
    }
    return &emptyTool;
}
NonTool *inventory::takeInventory(NonTool &other)
{
    if (this->neff > 0)
    {
        int i = 0;

        // Skip item with different ID while not out of inventories' bound,
        // If NonTool, skip if num > quantity
        // while (this->inventories[i]->getID() != other.getID() && i < this->neff
        //         && !this->isTool(i) && this->inventories[i]->getQuantityDurability() < other.getQuantityDurability() ) {
        //     i++;
        // }
        while (i < 27)
        {
            if (this->inventories[i]->getID() == other.getID())
            {
                if ((this->isTool(i)) || (this->inventories[i]->getQuantityDurability() >= other.getQuantityDurability()))
                {
                    break;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                i++;
            }
        }

        // Found item with same ID, if NonTool, the quantity is more than num
        // or i >= inventories size (max 27)
        if (i < 27)
        {
            // Take in slot i
            int total = this->inventories[i]->getQuantityDurability() - other.getQuantityDurability();
            if (total > 0)
            {
                this->inventories[i]->setQuantityDurability(total);
            }
            else if (total == 0)
            {
                this->setInventory(this->neff, emptyNonTool);
                this->nextNeff();
            }
            return &other;
        }
        else
        {
            throw new ItemNotFound();
        }
    }
    return &emptyNonTool;
}
Item *inventory::takeInventory(Item &other)
{
    if (this->neff > 0)
    {
        int i = 0;

        // Skip item with different ID while not out of inventories' bound,
        // If NonTool, skip if num > quantity
        // while (this->inventories[i]->getID() != other.getID() && i < this->neff
        //         && !this->isTool(i) && this->inventories[i]->getQuantityDurability() < other.getQuantityDurability() ) {
        //     i++;
        // }
        while (i < 27)
        {
            if (this->inventories[i]->getID() == other.getID())
            {
                if ((this->isTool(i)) || (this->inventories[i]->getQuantityDurability() >= other.getQuantityDurability()))
                {
                    break;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                i++;
            }
        }

        // Found item with same ID, if NonTool, the quantity is more than num
        // or i >= inventories size (max 27)
        if (i < 27)
        {
            // Take in slot i
            int total = this->inventories[i]->getQuantityDurability() - other.getQuantityDurability();
            if (total > 0)
            {
                this->inventories[i]->setQuantityDurability(total);
            }
            else if (total == 0)
            {
                this->setInventory(this->neff, emptyNonTool);
                this->nextNeff();
            }
            return &other;
        }
        else
        {
            throw new ItemNotFound();
        }
    }
    return &emptyNonTool;
}
Item *inventory::takeInventory(int slotID, int quantity)
{
    if (slotID < 0 || slotID > 26){
        throw new IndexOutOfRange(slotID, "inventory");
    }
    Item *tempItemInv = this->inventories[slotID]->clone();
    Item *copy = this->inventories[slotID];
    copy->setQuantityDurability(quantity);
    NonTool tempItem(tempItemInv->getID(), tempItemInv->getName(), tempItemInv->getType(), quantity);
    if (tempItemInv->getID() != -1 && slotID < 27 && slotID >= 0 && tempItemInv->getQuantityDurability() >= quantity)
    {
        int total = tempItemInv->getQuantityDurability() - quantity;
        if (!this->isTool(slotID) && total > 0)
        {
            this->inventories[slotID]->setQuantityDurability(total);
        }
        else if (this->isTool(slotID) || (!this->isTool(slotID) && total == 0))
        {
            this->setInventory(slotID, emptyNonTool);
            this->nextNeff();
        }
        delete tempItemInv;
        return copy;
    }
    else if (slotID < 27 && slotID >= 0 && tempItemInv->getQuantityDurability() < quantity && tempItemInv->getName() != "Empty")
    {
        delete tempItemInv;
        throw new ItemQtInsufficient();
    }
    else
    {
        delete tempItemInv;
        throw new ItemNotFound();
    }

    return &emptyNonTool;
}

// Move item from src slot to dest slot
bool inventory::pileInventory(int idx_src, int idx_dest)
{
    if (idx_src < 0 || idx_src > 26){
        throw new IndexOutOfRange(idx_src, "inventory");
    }
    if (idx_dest < 0 || idx_dest > 26){
        throw new IndexOutOfRange(idx_dest, "inventory");
    }
    // Only take if NonTool, shares same ID, and total quantity <= 64
    Item *temp_src = this->inventories[idx_src];
    Item *temp_dest = this->inventories[idx_dest];
    if (temp_src->getID() == temp_dest->getID() && temp_src->getType() != "Tool" && temp_src->getQuantityDurability() + temp_dest->getQuantityDurability() <= 64)
    {
        // Take item from inventory
        if (!this->isTool(idx_src))
        {
            // NonTool
            Item *temp_taken;
            temp_taken = this->takeInventory(idx_src, temp_src->getQuantityDurability());
            if (temp_taken->getName() != "Empty")
            {
                // successfully taken, move to other inventory slot
                this->addInventory(*temp_taken, idx_dest);
                return true;
            }
        }
        else
        {
            // Tool
            Item *temp_taken;
            temp_taken = this->takeInventory(idx_src, temp_src->getQuantityDurability());
            if (!isItemEmpty(*temp_taken))
            {
                // successfully taken, move to other inventory slot
                this->addInventory(*temp_taken, idx_dest);
                return true;
            }
        }
    }
    return false;
}

// Output
void inventory::printInfoInventory()
{
    for (int i = 0; i < 27; i++)
    {
        if (!this->isEmpty(i))
        {
            this->inventories[i]->printInfo();
        }
        else
        {
            cout << "[EMPTY]";
        }
        if (i % 9 != 8)
        {
            cout << " ";
        }
        else
        {
            cout << endl;
        }
    }
}

void inventory::showInventory()
{
    int rows = (int)round((double)this->neff / (double)9);
    int idx = this->neff;
    int i;
    int j;
    for (i = 0; i < 27; i++)
    {
        cout << i << ". ";
        this->getInventory(i).printInfo();
        // cout << "[I";
        // cout << setfill(' ') << setw(2) << i;
        // cout << "]";
        // if (i % 9 != 8)
        // {
        //     cout << " ";
        // }
        // else
        // {
        //     cout << endl;
        // }
    }
}
void inventory::exportInventory(string filename)
{
    ofstream exportFile;
    exportFile.open(filename);
    for (int i = 0; i < 27; i++)
    {
        if (this->isEmpty(i))
        {
            exportFile << "0:0\n";
        }
        else
        {
            exportFile << this->inventories[i]->getID() << ":" << this->inventories[i]->getQuantityDurability() << "\n";
        }
    }
    exportFile.close();
}

// Dictionary
void inventory::addItemDict(string line)
{
    int i = 0;
    string temp[4];
    for (auto x : line)
    {
        if (x == ' ')
        {
            i++;
        }
        else
        {
            temp[i] += x;
        }
    }
    if (temp[3] == "TOOL")
    {
        temp[2] = temp[3];
    }
    if (temp[2] == "-" || temp[2]=="LOG")
    {
        temp[2] = temp[1];
    }
    // this->itemDict.insert(pair<string,tuple<int,string,string>>(temp[1],(std::stoi(temp[0]),temp[2],temp[3])));
    this->itemDict.insert(make_pair(temp[1], make_tuple(stoi(temp[0]), temp[2], temp[3])));
    this->itemDict.insert(make_pair("Empty", make_tuple(-1, "Empty", "Empty")));
}

Item *inventory::searchDict(string Nama, int jumlah)
{
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
    if (this->itemDict.find(Nama) == this->itemDict.end())
    {
        throw new ItemNotExist();
    }
    else
    {
        tuple<int, string, string> temp; //<ID , Type, Tool/NonTool>
        temp = this->itemDict.at(Nama);
        if (get<2>(temp) == "NONTOOL")
        {
            return new NonTool(get<0>(temp), Nama, get<1>(temp), jumlah);    
        }
        else
        {
            return new Tool(get<0>(temp), Nama, get<1>(temp),jumlah);
        }
    }
}