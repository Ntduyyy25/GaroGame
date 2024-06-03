#include "Player.h"
#include <cmath>

string Player::getName() const
{
    return m_name;
}
int Player::getWin() const
{
    return m_win;
}

int Player::getLoss() const
{
    return m_loss;
}

int Player::getDraw() const
{
    return m_draw;
}

float Player::getWinRate() const
{
    float winRate = ((getWin() + getLoss() + getDraw()) > 0 ? static_cast<float>(getWin()) / (getWin() + getLoss() + getDraw()) : 0);
    return round(winRate * 100) / 100;
}

void Player::printPlayer() const
{
    cout << getName() << "\t\t\t" << getWin() << "\t\t\t" << getLoss() << "\t\t\t" << getDraw() << "\t\t\t" << getWinRate() << endl;
}

void Player::increaseWin()
{
    m_win++;
}

void Player::increaseLoss()
{
    m_loss++;
}

void Player::increaseDraw()
{
    m_draw++;
}

void Player::setWin(int x)
{
    m_win += x;
}

void Player::setLoss(int x)
{
    m_loss += x;
}

void Player::setDraw(int x)
{
    m_draw += x;
}
void Player::setWinRate(float x)
{
    m_winRate += x;
}