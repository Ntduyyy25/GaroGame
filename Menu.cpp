#include "Menu.h"
#include <iostream>

using namespace std;

void Menu::displayMainMenu()
{
    cout << CYAN << "*-------MAIN MENU-------*" << endl;
    cout << "1. Play with Other Player" << endl;
    cout << "2. Play with BOT" << endl;
    cout << "3. Player's Information" << endl;
    cout << "4. Search Player's Information (by name)" << endl;
    cout << "5. Guide" << endl;
    cout << "6. Exit" << RESET << endl;
}

void Menu::menuPlayWithBot()
{
    cout << CYAN << "*-------PLAY WITH BOT-------*" << endl;
    cout << "1. Easy Mode" << endl;
    cout << "2. Medium Mode" << endl;
    cout << "3. Hard Mode" << endl;
    cout << "4. Back to Main Menu" << RESET << endl;
}

void Menu::Guide()
{
    cout << ORANGE << "*-----------------------GUIDE-----------------------*" << endl;
    cout << ORANGE << "1. Game Board Size:" << RESET << " Game Caro is played on a 10x10 grid." << endl;
    cout << ORANGE << "2. Players:" << RESET << " Two players take turns placing their symbols (X or O) on the board." << endl;
    cout << ORANGE << "3. Gameplay:" << RESET << " Players input the coordinates (row and column) of the cell where they want to place their symbol from the keyboard." << endl;
    cout << ORANGE << "4. Winning Condition:" << RESET << " The first player to align four of their symbols (X or O) consecutively in a horizontal, vertical, or diagonal line wins the game." << endl;
    cout << ORANGE << "5. Features:" << endl;
    cout << ORANGE << "   - Play With Other Player:" << RESET << " Enjoy a match with a friend." << endl;
    cout << ORANGE << "   - Play With Computer:" << RESET << " Challenge the BOT." << endl;
    cout << ORANGE << "   - Replay the Match:" << RESET << " Start a new game with the same settings." << endl;
    cout << ORANGE << "   - Review the Match:" << RESET << " Watch a replay of the completed game." << endl;
    cout << ORANGE << "   - View Player's Information:" << RESET << " Check out the details of the players." << endl;
    cout << ORANGE << "   - Search for Player's Information:" << RESET << " Look up specific player statistics and info." << endl;
}
