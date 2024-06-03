#include "Caro.h"
#include <unistd.h>

class CaroMedium
{
private:
    Caro caro;

public:
    bool isBlocked(int x, int y);  // Ham kiem tra o co bi chan khong
    int attackPoint(int x, int y); // Tinh diem tan cong cua o [x][y]
    int defendPoint(int x, int y); // Tinh diem phong ngu o [x][y]
    pair<int, int> getBestMove();  // Tim nuoc di tot nhat
    void playMedium();             // Choi muc trung binh
    void playHard();               // Choi muc kho
};