#include "Crafting.hpp"

Crafting::Crafting(){
  this->kotakresep = new string[9]; 
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