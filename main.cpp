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
/*
GIVE WOODEN_SWORD 3
SHOW
MOVE I0 1 I1
*/

    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";
    // Configure Game
    GameState game(configPath);

    string command;
    while (1){
        try
        {
            game.commandHandler();
        }        
        catch (exception* e)
        {
            // system("pause");
            // cout << "test";
            cout << e->what();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } 
        
    return 0;
}
