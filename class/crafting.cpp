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
    if(temp[2]=="-"){
        temp[2]=temp[1];
    }
    // this->itemDict.insert(pair<string,tuple<int,string,string>>(temp[1],(std::stoi(temp[0]),temp[2],temp[3])));
    this->itemDict.insert(make_pair(temp[1], make_tuple(stoi(temp[0]),temp[2],temp[3])));
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

void Crafting::searchDict(string Nama){
    tuple<int, string, string> temp;
    temp = this->itemDict.at(Nama);
    cout<<"key: "<<get<0>(temp)<<endl;
    cout<<"nama: "<<Nama<<endl;
    cout<<"tipe: "<<get<1>(temp)<<endl;
    cout<<"tipetool: "<<get<2>(temp)<<endl;
}