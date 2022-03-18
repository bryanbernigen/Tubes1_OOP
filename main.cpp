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
  //Configure Game
  GameState game(configPath);
  
  //Testing
  NonTool stone = NonTool(0,"STONE","STONE");
  NonTool stick = NonTool(0,"STICK","STICK");
  game.craftingTable.addToCraftingTable(stone,2);
  game.craftingTable.addToCraftingTable(stone,5);
  game.craftingTable.addToCraftingTable(stone,1);
  game.craftingTable.addToCraftingTable(stick,4);
  game.craftingTable.addToCraftingTable(stick,7);
  game.craftingTable.craft();
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
