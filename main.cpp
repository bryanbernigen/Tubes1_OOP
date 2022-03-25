// sample main file, replace this with your own code

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "class/resep.hpp"
#include "class/crafting.hpp"
#include "class/item.hpp"
#include "class/tool.hpp"
#include "class/nontool.hpp"
#include "class/inventory.hpp"
#include "class/gameState.hpp"

using namespace std;

int main()
{
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";
    // Configure Game
    GameState game(configPath);
    string command;
    cout << "Masukkan Input: ";
    while (cin >> command)
    {
        cout << endl;
        try
        {
            game.commandHandler(command);
        }
        catch (exception *e)
        {
            cout << e->what();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Masukkan Input: ";
    }

    return 0;
}
