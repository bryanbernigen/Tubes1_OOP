#include "Crafting.hpp"

Crafting::Crafting()
{
    this->craftingtable = new Item *[9];
    this->slotStatus = new bool[9];
    for (int i = 0; i < 9; i++)
    {
        this->slotStatus[i] = false;
    }
}

Crafting::~Crafting()
{
    delete[] this->craftingtable;
    delete[] this->slotStatus;
}

// Add Item to crafting table, if not successful (Not same Type or Slot Full throws exception)
void Crafting::addToCraftingTable(Item &item, int pos)
{
    // Item already exist in that slot
    if (this->slotStatus[pos])
    {
        if (this->craftingtable[pos]->getType() != item.getType() || this->craftingtable[pos]->getType() == "TOOL")
            throw new SlotFilledException();
        else
        {
            int total = this->craftingtable[pos]->getQuantityDurability() + item.getQuantityDurability();
            if (total > 64)
            {
                this->craftingtable[pos]->setQuantityDurability(64);
                throw new SlotFullException();
            }
            else
            {
                this->craftingtable[pos]->setQuantityDurability(total);
            }
        }
    }
    else
    {
        this->craftingtable[pos] = item.clone();
        this->slotStatus[pos] = true;
    }
}

// Returns pointer to item or exception
Item *Crafting::takeItem(int pos, int quantity)
{
    if (!this->slotStatus[pos])
        throw new SlotEmptyException();
    if (this->craftingtable[pos]->getQuantityDurability() == quantity || this->craftingtable[pos]->getType() == "TOOL")
    {
        this->slotStatus[pos] = false;
        Item *returnedItem = this->craftingtable[pos]->clone();
        delete this->craftingtable[pos];
        return returnedItem;
    }
    if (this->craftingtable[pos]->getQuantityDurability() < quantity)
        throw new QuantityNotMetException();
    else
    {
        Item *returnedItem = this->craftingtable[pos]->clone();
        this->craftingtable[pos]->setQuantityDurability(this->craftingtable[pos]->getQuantityDurability() - quantity);
        returnedItem->setQuantityDurability(quantity);
        return returnedItem;
    }
}

// Returns pointer to item or exception
Item *Crafting::takeItem(int pos)
{
    if (!this->slotStatus[pos])
        throw new SlotEmptyException();
    else
    {
        this->slotStatus[pos] = false;
        Item *returnedItem = this->craftingtable[pos]->clone();
        delete this->craftingtable[pos];
        return returnedItem;
    }
}

Item *Crafting::getCrafting(int pos)
{
    if (!this->slotStatus[pos])
        throw new SlotEmptyException();
    else
    {
        Item *returnedItem = this->craftingtable[pos];
        return returnedItem;
    }
}

void Crafting::addResep(Resep resep)
{
    this->semuaresep.push_back(resep);
}

void Crafting::showAllResep()
{
    list<Resep>::iterator ptr;
    ptr = this->semuaresep.begin();
    for (ptr; ptr != this->semuaresep.end(); ptr++)
    {
        ptr->showResep();
    }
}

void Crafting::showCraftingTable()
{
    for (int j = 0; j < 24; j++)
            {
                cout<<" ";
            } 
    for (int i = 0; i < 9; i++)
    {
        if (this->slotStatus[i])
        {
            this->craftingtable[i]->printInfo();
            cout<<this->craftingtable[i]->getType();
        }
        else
        {
            cout << "[EMPTY]";
        }
        if (i % 3 != 2)
        {
            cout << " ";
        }
        else
        {
            cout << endl;
            for (int j = 0; j < 24; j++)
            {
                cout<<" ";
            } 
        }
    }
    cout<<""<<endl;
}

// TODO Define return + Nontool
pair<string, int> Crafting::craft()
{
    list<Resep>::iterator ptr;
    ptr = this->semuaresep.begin();
    int Tools = 0;
    int NonTools = 0;
    int ToolId = -1;
    int dur = 0;
    for (int i = 0; i < 9 ; i++ ){
        if(this->slotStatus[i]){
            if(this->craftingtable[i]->getType() == "TOOLS"){
                Tools++;
            }
            else{
                NonTools++;
            }
        }
    }
    if (Tools == 1){
        return (make_pair("", 0));
    }

    if (Tools == 2 && NonTools == 0){
        for(int i = 0 ; i < 9 ; i++){
            if(this->slotStatus[i]){
                dur += this->craftingtable[i]->getQuantityDurability();
                if(ToolId == -1){
                    ToolId = this->craftingtable[i]->getID();
                    
                }
                else{
                    if (ToolId == this->craftingtable[i]->getID()){
                        dur = min(dur,10);
                        return (make_pair(this->craftingtable[i]->getName(), dur));
                    }
                    else{
                        throw new ToolNotMatchExc();
                    }
                }
            }
        }
    }

    string craftingstring = "";
    string flippedcraftingstring = "";
    for (int i = 0; i < 9; i++)
    {
        if (!this->slotStatus[i])
        {
            craftingstring += "-";
        }
        else
        {
            craftingstring += this->craftingtable[i]->getType();
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 2; j >= 0; j--)
        {
            if (!this->slotStatus[i * 3 + j])
            {
                flippedcraftingstring += "-";
            }
            else
            {
                flippedcraftingstring += craftingtable[i * 3 + j]->getType();
            }
        }
    }
    
    for (auto& ptr : this->semuaresep)
    {
        bool found = true;
        if (craftingstring.find(ptr.getResep()) != string::npos)
        {
            string::iterator it;
            string str = craftingstring;
            str.replace(str.find(ptr.getResep()), ptr.getResep().length(), "-");
            for (it = str.begin(); it != str.end(); it++)
            {
                // cout<<*it;
                // Print current character
                if (*it != '-')
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                return (make_pair(ptr.getNamaBarang(), ptr.getJumlah()));
            }
        }

        if (flippedcraftingstring.find(ptr.getResep()) != string::npos)
        {
            bool found = true;
            string::iterator it;
            string str = flippedcraftingstring;
            str.replace(str.find(ptr.getResep()), ptr.getResep().length(), "-");
            for (it = str.begin(); it != str.end(); it++)
            {
                // Print current character
                if (*it != '-')
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                return (make_pair(ptr.getNamaBarang(), ptr.getJumlah()));
            }
        }
    }
    return (make_pair("", 0));
}