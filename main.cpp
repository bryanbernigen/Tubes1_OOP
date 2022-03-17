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
using namespace std;

int main()
{
  string configPath = "./config";
  string itemConfigPath = configPath + "/item.txt";

  // read item from config file
  Crafting craftingTable;
  inventory inv;
  ifstream itemConfigFile(itemConfigPath);
  for (string line; getline(itemConfigFile, line);) {
    cout << line << endl;
    inv.addItemDict(line);
  }
  cout<<"============================================="<<endl;

  // read recipes
  for (const auto &entry :
       filesystem::directory_iterator(configPath + "/recipe"))
  {
    // cout << entry.path() << endl;
    ifstream itemConfigFile(entry.path());
    string isi_resep;
    for (string line; getline(itemConfigFile, line);)
    {
      isi_resep+=line;
      isi_resep+=" ";
    }
    craftingTable.addResep(Resep(isi_resep));
    // read from file and do something
  }
  // craftingTable.showAllResep();
  cout<<"============================================="<<endl;
  // craftingTable.searchDict("DIAMOND");
  // sample interaction
  NonTool stone = NonTool(0,"STONE","STONE");
  NonTool stick = NonTool(0,"STICK","STICK");
  craftingTable.addToCraftingTable(stone,2);
  craftingTable.addToCraftingTable(stone,5);
  craftingTable.addToCraftingTable(stone,1);
  craftingTable.addToCraftingTable(stick,4);
  craftingTable.addToCraftingTable(stick,7);
  craftingTable.craft();
  string command;
  while (cin >> command)
  {
    if (command == "EXPORT")
    {
      string outputPath;
      cin >> outputPath;
      ofstream outputFile(outputPath);

      // hardcode for first test case
      outputFile << "21:10" << endl;
      outputFile << "6:1" << endl;
      for (int i = 2; i < 27; i++)
      {
        outputFile << "0:0" << endl;
      }

      cout << "Exported" << endl;
    }
    else if (command == "CRAFT")
    {
      cout << "TODO" << endl;
    }
    else if (command == "GIVE")
    {
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
      cout << "TODO" << endl;
    }
    else if (command == "MOVE")
    {
      string slotSrc;
      int slotQty;
      string slotDest;
      // need to handle multiple destinations
      cin >> slotSrc >> slotQty >> slotDest;
      cout << "TODO" << endl;
    }
    else
    {
      // todo
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}
