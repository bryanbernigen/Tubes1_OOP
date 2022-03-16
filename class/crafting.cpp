#include "Crafting.hpp"

Crafting::Crafting(){
  this->craftingtable = new Item * [9]; 
}

void Crafting::addToCraftingTable(Item& item, int pos){
    this->craftingtable[pos] = item.clone();
}
void Crafting::addResep(Resep resep){
    this->semuaresep.push_back(resep);
}

void Crafting::showAllResep(){
    this->ptr = this->semuaresep.begin();
    for ( this->ptr; this->ptr!=this->semuaresep.end(); this->ptr++)
    {
        this->ptr->showResep();
    }   
}

//TODO Define return + Nontool
Item* Crafting::craft(){
    this->ptr = this->semuaresep.begin();
    string craftingstring = "";
    string flippedcraftingstring = "";
    for (int i = 0 ; i < 9 ; i++){
        if(craftingtable[i] == NULL){
            craftingstring += "-";
        }
        else{
            craftingstring += craftingtable[i]->getName();
        }
    }
    for (int i = 0 ; i < 3 ; i++){
        for (int j = 2; j >= 0; j--){
            if(craftingtable[i*3+j] == NULL){
                craftingstring += "-";
            }
            else{
                craftingstring += craftingtable[i*3+j]->getName();
            }
        }       
    }
    for ( this->ptr; this->ptr!=this->semuaresep.end(); this->ptr++)
    {
        if(craftingstring.find(this->ptr->getResep())!= string::npos){
            //return new Item();
        }
    }  
}