#pragma once
#include <iostream>

using namespace std;

class Player
{
protected:
    string m_name;
    int m_win;
    int m_loss;
    int m_draw;
    float m_winRate;

public:
    Player() {}                                                           // Ham tao khong tham so
    Player(string name) : m_name(name), m_win(0), m_loss(0), m_draw(0) {} // Ham tao co tham so
    ~Player() {}                                                          // Ham huy
    string getName() const;                                               // Ham lay ten nguoi dung
    int getWin() const;                                                   // Ham lay ra so tran thang
    int getLoss() const;                                                  // Ham lay ra so tran thua
    int getDraw() const;                                                  // Ham lay ra so tran hoa
    float getWinRate() const;                                             // Ham lay ra ty le thang
    void printPlayer() const;                                             // Ham in thong tin nguoi dung
    void increaseWin();                                                   // Ham tang so tran thang len 1
    void increaseLoss();                                                  // Ham tang so tran thua len 1
    void increaseDraw();                                                  // Ham tang so tran hoa len 1
    void setWin(int x);                                                   // Ham tang so tran thang len x don vi
    void setLoss(int x);                                                  // Ham tang so tran thua len x don vi
    void setDraw(int x);                                                  // Ham tang so tran hoa len x don vi
    void setWinRate(float x);                                             // Ham tang ty le thang len x don vi
};