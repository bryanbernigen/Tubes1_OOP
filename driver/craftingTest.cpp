#include <iomanip>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "../class/crafting.cpp"
#include "../class/item.cpp"
#include "../class/NonTool.cpp"
#include "../class/tool.cpp"
#include "../class/resep.cpp"

using namespace std;

#define MAX_KOLOM 3
int main(){
    string configPath = "../config";
    // Configure Game
    Crafting ct;
    NonTool plank5(4, "OAK_PLANK", "PLANK",5);
    NonTool plank4(4, "OAK_PLANK", "PLANK",4);
    NonTool iron(10, "IRON_INGOT","IRON_INGOT", 2);
    for (const auto &entry :
         filesystem::directory_iterator(configPath + "/recipe"))
    {
        // cout << entry.path() << endl;
        ifstream itemConfigFile(entry.path());
        string isi_resep;
        string ukuran;
        getline(itemConfigFile, ukuran);
        isi_resep += ukuran + " ";
        int kolom = (int)ukuran[2] - '0';
        int baris = (int)ukuran[0] - '0';
        for (int j = 0; j < baris; j++)
        {
            string line;
            getline(itemConfigFile, line);
            isi_resep += line;
            for (int i = kolom; i < MAX_KOLOM; i++)
            {
                isi_resep += " -";
            }

            isi_resep += " ";
        }
        string line;
        getline(itemConfigFile, line);
        isi_resep += line + " ";
        ct.addResep(Resep(isi_resep));
    }
    cout << "============================LIST OF RECIPES================================" <<endl;
    ct.showAllResep();
    cout << "========================ADD PLANKS TO C2 and C5============================" <<endl;
    ct.addToCraftingTable(plank4,2);
    ct.addToCraftingTable(plank5,5);
    ct.showCraftingTable();
    cout << "=============================CREATE STICKS=================================" <<endl;
    auto res = ct.craft();
    cout << "Created Item " << res.first << " with quantity of " << res.second <<endl;
    ct.showCraftingTable();
    cout << "===========================TRY STACKING ITEM=================================" <<endl;
    ct.addToCraftingTable(plank5,5);
    ct.showCraftingTable();
    cout << "=========================NO RECIPE MATCH ERROR=================================" <<endl;
    cout << "===========================ADD PLANKS TO C4====================================" <<endl;
    ct.addToCraftingTable(plank5,4);
    ct.showCraftingTable();
    try{
        ct.craft();
    }
    catch(exception* e){
        cout << e->what() << endl;
    }
    ct.showCraftingTable();
    cout << "============================WRONG ITEM STACK===================================" <<endl;
    cout << "=============================ADD IRON TO C4====================================" <<endl;
    try{
        ct.addToCraftingTable(iron,4);
    }
    catch(exception* e){
        cout << e->what() << endl;
    }
    ct.showCraftingTable();
}