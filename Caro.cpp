#include "Caro.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>

using namespace std;

vector<Player *> Caro::playerList;

// Khoi tao ban co rong
void Caro::initBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// In ban co
void Caro::printBoard()
{
    // In dong ghi chu
    cout << ORANGE << "\tPlayer 1 = X, Player 2 = O:" << RESET << endl;

    // In cac cot toa do
    cout << "     ";
    for (int col = 0; col < SIZE; ++col)
    {
        cout << ORANGE << col << "   ";
    }
    cout << RESET << endl;

    // In ban co
    // In phan dau
    cout << "   " << YELLOW;
    for (int col = 0; col < SIZE; ++col)
    {
        cout << "|---";
    }
    cout << "|" << RESET << endl;

    for (int row = 0; row < SIZE; ++row)
    {
        cout << ORANGE << row << "  " << RESET << YELLOW;
        for (int col = 0; col < SIZE; ++col)
        {
            cout << "| " << RESET << board[row][col] << " " << YELLOW; // In cac o voi ki tu tuong ung
        }
        cout << "|" << endl;

        // In duong ngang giua hang
        if (row < SIZE - 1)
        {
            cout << "   ";
            for (int col = 0; col < SIZE; ++col)
            {
                cout << "|---";
            }
            cout << "|" << RESET << endl;
        }
    }
    // In phan cuoi
    cout << "   " << YELLOW;
    for (int col = 0; col < SIZE; ++col)
    {
        cout << "|---";
    }
    cout << "|" << RESET << endl;
}

// Check nuoc di hop le
bool Caro::isValidMove(int row, int col)
{
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ';
}

// Check dieu kien thang
bool Caro::checkWin(int row, int col)
{
    char playerSymbol = (m_currentIndex == 0) ? 'X' : 'O';
    int count = 1;

    // Check hang ngang
    for (int i = col - 1; i >= 0 && board[row][i] == playerSymbol; i--)
    {
        count++;
    }
    for (int i = col + 1; i < SIZE && board[row][i] == playerSymbol; i++)
    {
        count++;
    }
    if (count >= 4)
        return true;

    // Check hang doc
    count = 1;
    for (int i = row - 1; i >= 0 && board[i][col] == playerSymbol; i--)
    {
        count++;
    }
    for (int i = row + 1; i < SIZE && board[i][col] == playerSymbol; i++)
    {
        count++;
    }
    if (count >= 4)
        return true;

    // Check duong cheo
    count = 1;
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0 && board[i][j] == playerSymbol; i--, j--)
    {
        count++;
    }
    for (int i = row + 1, j = col + 1; i < SIZE && j < SIZE && board[i][j] == playerSymbol; i++, j++)
    {
        count++;
    }
    if (count >= 4)
        return true;

    count = 1;
    for (int i = row - 1, j = col + 1; i >= 0 && j < SIZE && board[i][j] == playerSymbol; i--, j++)
    {
        count++;
    }
    for (int i = row + 1, j = col - 1; i < SIZE && j >= 0 && board[i][j] == playerSymbol; i++, j--)
    {
        count++;
    }
    if (count >= 4)
        return true;

    return false;
}

// Check dieu kien hoa
bool Caro::checkDraw()
{
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                if (board[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }
}

// Tao nuoc di
void Caro::makeMove(int row, int col)
{
    char symbol = (m_currentIndex == 0) ? 'X' : 'O';
    board[row][col] = symbol;
    m_moveCount++;
    lastMove = make_pair(row, col); // Vi tri nuoc di cuoi cung cua nguoi choi
}

// Doi luot nguoi choi
void Caro::switchPlayer()
{
    m_currentIndex = (m_currentIndex == 0) ? 1 : 0;
}

// Che do choi voi nguoi
void Caro::playWithPlayer()
{
    record(0, 0, 0);
    int row, col;
    initBoard();
    while (m_moveCount < SIZE * SIZE)
    {
        printBoard();

        // Nhap nuoc di tu ban phim
        do
        {
            cout << "-> Player " << player[m_currentIndex]->getName() << "'s turn. Input row and column: ";
            cin >> row >> col;
            if (cin.fail())
            {
                cout << "Invalid move. Please try again!\n";
                cin.clear();             // Xoa trang thai loi
                cin.ignore(32767, '\n'); // Loai bo ki tu khong hop le
                row = -1;
                col = -1;
            }
        } while (row < 0 || row >= 99 || col < 0 || col >= 99);
        if (isValidMove(row, col))
        {
            record(row, col, 1);
            makeMove(row, col);
            if (checkWin(row, col))
            {
                system("cls");
                printBoard();
                cout << ORANGE << "\n\t=> Player " << player[m_currentIndex]->getName() << " wins!" << RESET << endl;
                player[m_currentIndex]->increaseWin();
                player[(m_currentIndex + 1) % 2]->increaseLoss();
                break;
            }
            switchPlayer();
        }
        else
        {
            cout << "Invalid move. Please try again!" << endl;
        }
    }
    if (checkDraw())
    {
        cout << ORANGE << "\n\t=> It's a draw!" << RESET << endl;
        player[0]->increaseDraw();
        player[1]->increaseDraw();
    }

    // Cap nhat thong tin trong playerList
    updatePlayerList(player[0]);
    updatePlayerList(player[1]);
    savePlayerList();

    // Lua chon sau choi game
    bool exit = 0;
    while (!exit)
    {
        menuAfterPlay();
        int choice;
        do
        {
            cout << "Input your choice: ";
            cin >> choice;
            if (cin.fail())
            {
                cout << "Invalid choice. Please try again!\n";
                cin.clear();             // Xoa trang thai loi
                cin.ignore(32767, '\n'); // Loai bo ki tu khong hop le
                sleep(1);
            }
        } while (choice < 0 || choice >= 99);
        switch (choice)
        {
        case 1:
        {
            system("cls");
            playWithPlayer();
            break;
        }
        case 2:
        {
            system("cls");
            watchReplay();
            system("pause");
            break;
        }
        case 3:
        {
            exit = 1;
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again!";
            break;
        }
        }
    }
}

// Record game
void Caro::record(int row, int col, int mode)
{
    string fileName = "record.txt";
    ofstream fileOut;
    if (1 == mode)
    {
        fileOut.open(fileName, ios::app); // mo ghi vao cuoi file
        string data = to_string(row) + " " + to_string(col) + "\n";
        fileOut << data;
    }
    else
    {
        fileOut.open(fileName, ios::out);
    }
    fileOut.close();
}

// Watch replay game
void Caro::watchReplay()
{
    int row, col;
    string fileName = "record.txt";
    ifstream fileIn;
    fileIn.open(fileName);
    string line;
    initBoard();
    char symbol = 'X';
    while (getline(fileIn, line))
    {
        stringstream ss(line);
        ss >> row >> col;
        board[row][col] = symbol;
        symbol = (symbol != 'X') ? 'X' : 'O';
        printBoard();
        // system("pause");
        sleep(2);
    }
    fileIn.close();
}

// Update player list
void Caro::updatePlayerList(Player *p)
{
    for (Player *player : playerList)
    {
        if (player->getName() == p->getName())
        {
            player->setWin(p->getWin());
            player->setLoss(p->getLoss());
            player->setDraw(p->getDraw());
            return;
        }
    }
    playerList.push_back(new Player(*p));
}

// Save player list to file
void Caro::savePlayerList()
{
    ofstream fileOut("playerInfo.txt");
    if (fileOut.is_open())
    {
        for (Player *player : playerList)
        {
            fileOut << player->getName() << " "
                    << player->getWin() << " "
                    << player->getLoss() << " "
                    << player->getDraw() << " "
                    << player->getWinRate() << endl;
        }
        fileOut.close();
    }
    else
    {
        cerr << "Cannot open file for writing." << endl;
    }
}

// Print player list
void Caro::outputList()
{
    sortPlayerList();
    cout << ORANGE << "\t\t\t\t\tPLAYER'S INFORMATION: " << endl;
    cout << "Name\t\t\tWin\t\t\tLoss\t\t\tDraw\t\t\tWinRate" << RESET << endl;
    for (int i = 0; i < playerList.size(); i++)
    {
        cout << playerList[i]->getName() << "\t\t\t" << playerList[i]->getWin() << "\t\t\t" << playerList[i]->getLoss() << "\t\t\t" << playerList[i]->getDraw() << "\t\t\t" << playerList[i]->getWinRate() << endl;
    }
}

// Sort playerList
void Caro::sortPlayerList()
{
    for (int i = 0; i < playerList.size(); i++)
    {
        for (int j = i + 1; j < playerList.size(); j++)
        {
            if (playerList[i]->getWinRate() > playerList[j]->getWinRate())
            {
                swap(playerList[i], playerList[j]);
            }
        }
    }
}

// Find player by name
void Caro::findPlayer(const string &name)
{
    sortPlayerList();
    int check = 0;
    for (int i = 0; i < playerList.size(); i++)
    {
        if (playerList[i]->getName() == name)
        {
            check = 1;
            cout << ORANGE << "Player's information you want to find: " << endl;
            cout << "Name\t\t\tWin\t\t\tLoss\t\t\tDraw\t\t\tWinRate" << RESET << endl;
            playerList[i]->printPlayer();
            cout << ORANGE << "Player with the same Win Rate: " << endl;
            cout << "Name\t\t\tWin\t\t\tLoss\t\t\tDraw\t\t\tWinRate" << RESET << endl;
            if (i == 0)
            {
                playerList[i + 1]->printPlayer();
            }
            else if (i == playerList.size() - 1)
            {
                playerList[i - 1]->printPlayer();
            }
            else
            {
                playerList[i - 1]->printPlayer();
                playerList[i + 1]->printPlayer();
            }
        }
    }
    if (check == 0)
    {
        cout << "Cannot find player with name:  " << name << ". Please check again!" << endl;
    }
}

// Load players from file to list
void Caro::loadPlayerList()
{
    ifstream fileIn;
    fileIn.open("playerInfo.txt");
    if (fileIn.is_open())
    {
        string line;
        string name;
        int win, loss, draw;
        float winRate;
        while (getline(fileIn, line))
        {
            stringstream ss(line);
            ss >> name >> win >> loss >> draw >> winRate;
            Player *player = new Player(name);
            player->setWin(win);
            player->setLoss(loss);
            player->setDraw(draw);
            player->setWinRate(winRate);
            updatePlayerList(player);
        }
        fileIn.close();
    }
}

// Menu after play
void Caro::menuAfterPlay()
{
    cout << "\nPress number to choice: " << endl;
    cout << "1. Replay Game" << endl;
    cout << "2. Watch Replay" << endl;
    cout << "3. Back to Main Menu" << endl;
}
