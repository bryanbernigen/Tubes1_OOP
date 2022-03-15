#include "tool.hpp"

tool::tool() : item()
{
    this->Durability = MAX_DURABILITY;
}

tool::tool(int ID, string Name, string Type) : item(ID, Name, Type)
{
    this->Durability = MAX_DURABILITY;
}

tool::tool(int ID, string Name, string Type, int Durability) : item(ID, Name, Type)
{
    if (Durability > 0 && Durability < MAX_DURABILITY)
    {
        this->Durability = Durability;
    }
    else
    {
        this->Durability = MAX_DURABILITY;
    }
}


//getter
const int tool::getDurability()
{
    return this->Durability;
}


//setter
void tool::setDurability(int Durability){
    this->Durability=Durability;
}


//other
void tool::useTool(){
    if(this->Durability > 0){
        this->Durability--;
    }
    else{
        throw "Tool sudah tidak dapat dipakai";
    }
}