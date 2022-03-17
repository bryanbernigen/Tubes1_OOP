#include "Crafting.hpp"

Crafting::Crafting(){
  this->craftingtable = new Item* [9]; 
  this->slotStatus = new bool [9];
  for (int i = 0; i < 9; i++){
      this->slotStatus[i] = false;
  }
}

Crafting::~Crafting(){
    delete [] this->craftingtable;
    delete [] this->slotStatus;
}

void Crafting::addToCraftingTable(Item& item, int pos){
    this->craftingtable[pos] = item.clone();
    this->slotStatus[pos] = true;
}

void Crafting::addResep(Resep resep){
    this->semuaresep.push_back(resep);
}

void Crafting::showAllResep(){
    list<Resep>::iterator ptr;
    ptr = this->semuaresep.begin();
    for ( ptr; ptr!=this->semuaresep.end(); ptr++)
    {
        ptr->showResep();
    }   
}

//TODO Define return + Nontool
string Crafting::craft(){
    list<Resep>::iterator ptr;
    bool found=true;
    ptr = this->semuaresep.begin();
    string craftingstring = "";
    string flippedcraftingstring = "";
    for (int i = 0 ; i < 9 ; i++){
        if(!this->slotStatus[i]){
            craftingstring += "-";
        }
        else{
            craftingstring += this->craftingtable[i]->getType();
        }
    }


    for (int i = 0 ; i < 3 ; i++){
        for (int j = 2; j >= 0; j--){
            if(!this->slotStatus[i*3+j]){
                flippedcraftingstring += "-";
            }
            else{
                flippedcraftingstring += craftingtable[i*3+j]->getType();
            }
        }       
    }
    for ( ptr; ptr!=this->semuaresep.end(); ptr++)
    {      
        if(craftingstring.find(ptr->getResep())!= string::npos){
            string::iterator it;
            string str = craftingstring;
            str.replace(str.find(ptr->getResep()),ptr->getResep().length(),"-");
            for (it = str.begin(); it != str.end();it++) {
                cout<<*it;
                // Print current character
                if(*it != '-') {
                    found = false;
                    break;
                }
            }
            if (found){
                cout << ptr->getNamaBarang()<< endl;
                break;
            }
            //return new Tool();
        }
        
        
        if(flippedcraftingstring.find(ptr->getResep())!= string::npos){
            string::iterator it;
            string str = flippedcraftingstring;
            str.replace(str.find(ptr->getResep()),ptr->getResep().length(),"-");
            for (it = str.begin(); it != str.end();it++) {
                // Print current character
                if(*it != '-') {
                    found = false;
                    break;
                }
            }
            if (found){
                cout << ptr->getNamaBarang()<< endl;
                break;
            }
        }
    }
    return "";  
}