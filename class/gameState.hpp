#ifndef _GAMESTATE_HPP_
#define _GAMESTATE_HPP_

#include "inventory.hpp"
#include "crafting.hpp"

class GameState
{
public:
    /*Dibikin public soalnya menurut gw lebih rapih kalo:
    game.craftingTable.addItem()
    dibanding kalo:
    game.getCraftingTable().addItem()*/
    inventory inv;
    Crafting craftingTable;
public:
    GameState();
    /*Ngisi inventory ama crafting table berdasarkan file di config_path
    di path config_path harus terdapat folder recipe*/
    GameState(string path_item);
    // ~GameState();
    
    void commandHandler();
    void give(string nama, int jumlah);
    void discard(int id_inventory, int jumlah);
};


#endif