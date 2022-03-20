// sample main file, replace this with your own code

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "class/resep.cpp"
#include "class/crafting.cpp"
#include "class/item.cpp"
#include "class/tool.cpp"
#include "class/nontool.cpp"
#include "class/inventory.cpp"
#include "class/gameState.cpp"

using namespace std;

int main()
{
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";
    // Configure Game
    GameState game(configPath);

    // Testing
    NonTool stone = NonTool(0, "STONE", "STONE", 10);
    NonTool stick = NonTool(0, "STICK", "STICK", 10);
    Tool sword = Tool(0, "IRON SWORD", "TOOL");
    // game.craftingTable.addToCraftingTable(stone, 2);
    // game.craftingTable.addToCraftingTable(stone, 5);
    // game.craftingTable.addToCraftingTable(stone, 1);
    // game.craftingTable.addToCraftingTable(stick, 4);
    // game.craftingTable.addToCraftingTable(stick, 7);
    // game.craftingTable.craft();

    game.inv.addInventory(stone, 0);
    game.inv.addInventory(stone, 1);
    game.inv.addInventory(stick, 2);
    game.inv.addInventory(sword, 5);
    string command;
    while (1)
    {
        game.commandHandler();
    }
    return 0;
}
