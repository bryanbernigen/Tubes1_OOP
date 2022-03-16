#include "Crafting.hpp"

Crafting::Crafting(){
  this->craftingtable = new Item * [9]; 
  
}

Crafting::~Crafting(){
    delete [] this->craftingtable;
}

void Crafting::addItemDict(string line){
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
    if(temp[2]==temp[1]){
        temp[2]=temp[1];
    }
    // this->itemDict.insert(pair<string,tuple<int,string,string>>(temp[1],(std::stoi(temp[0]),temp[2],temp[3])));
    this->itemDict.insert(make_pair(temp[1], make_tuple(stoi(temp[0]),temp[2],temp[3])));
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
            return new Tool();
        }
    }
    return new Tool();  
}