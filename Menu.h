#pragma once

// Định nghĩa các mã màu ANSI
#define RESET "\033[0m"
#define RED "\033[31m"          /* Đỏ */
#define GREEN "\033[32m"        /* Xanh lá cây */
#define YELLOW "\033[33m"       /* Vàng */
#define ORANGE "\033[38;5;208m" /*Cam*/
#define BLUE "\033[34m"         /* Xanh dương */
#define MAGENTA "\033[35m"      /* Tím */
#define CYAN "\033[36m"         /* Xanh dương nhạt */

class Menu
{
public:
    static void displayMainMenu(); // Menu chinh
    static void menuPlayWithBot(); // Menu play with BOT
    static void Guide();           // Huong dan choi game
};