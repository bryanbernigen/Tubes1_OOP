#include "gameState.hpp"
#include <filesystem>
#include <fstream>

GameState::GameState(){};

GameState::GameState(string config_path)
{
    ifstream itemConfigFile(config_path);
    for (string line; getline(itemConfigFile, line);)
    {
        this->inv.addItemDict(line);
    }
    for (const auto &entry :
         filesystem::directory_iterator(config_path + "/recipe"))
    {
        // cout << entry.path() << endl;
        ifstream itemConfigFile(entry.path());
        string isi_resep;
        for (string line; getline(itemConfigFile, line);)
        {
            isi_resep += line;
            isi_resep += " ";
        }
        this->craftingTable.addResep(Resep(isi_resep));
    }
}