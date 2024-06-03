#ifndef CARO_H
#define CARO_H

#include "Player.h"
#include <vector>
#include <utility>

const int SIZE = 10;

// Định nghĩa các mã màu ANSI
#define RESET "\033[0m"
#define RED "\033[31m"          /* Đỏ */
#define GREEN "\033[32m"        /* Xanh lá cây */
#define YELLOW "\033[33m"       /* Vàng */
#define ORANGE "\033[38;5;208m" /*Cam*/
#define BLUE "\033[34m"         /* Xanh dương */
#define MAGENTA "\033[35m"      /* Tím */
#define CYAN "\033[36m"         /* Xanh dương nhạt */

class Caro
{
private:
    char board[SIZE][SIZE];
    Player *player[2];
    int m_currentIndex;
    int m_moveCount;
    static vector<Player *> playerList;
    pair<int, int> lastMove; // Vi tri nuoc di cuoi cung cua nguoi choi

public:
    Caro() {}
    ~Caro() {}
    Caro(Player *player1, Player *player2) : m_currentIndex(0), m_moveCount(0)
    {
        player[0] = player1;
        player[1] = player2;
        initBoard();
    }
    void initBoard();                           // Khoi tao ban co rong
    void printBoard();                          // In ban co va gan gia tri
    bool isValidMove(int row, int col);         // Kiem tra tinh hop le cua nuoc di
    bool checkWin(int row, int col);            // Kiem tra dieu kien thang
    bool checkDraw();                           // Kiem tra dieu kien hoa
    void makeMove(int row, int col);            // Tao nuoc di
    void switchPlayer();                        // Doi luot nguoi choi
    void record(int row, int col, int mode);    // Record lai van dau vao file
    void watchReplay();                         // Xem lai van dau
    void playWithPlayer();                      // Choi voi nguoi khac
    static void updatePlayerList(Player *p);    // Cap nhat thong tin player list
    void savePlayerList();                      // Luu thong tin player list vao file
    static void sortPlayerList();               // Sap sep playerList theo chieu winRate tang dan
    static void loadPlayerList();               // Doc thong tin player tu file
    static void findPlayer(const string &name); // Tim kiem thong tin player
    static void outputList();                   // In thong tin player list
    void menuAfterPlay();                       // Menu sau choi game
    friend class CaroMedium;                    // Medium Mode
    friend class CaroEasy;                      // Easy Mode
};

#endif // CARO_H