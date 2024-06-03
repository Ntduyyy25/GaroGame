#include "Player.h"
#include "Caro.h"
#include "CaroEasy.h"
#include "CaroMedium.h"
#include "Menu.h"
#include <iostream>

using namespace std;

int main()
{
    Caro::loadPlayerList();
    int choice;
    while (true)
    {
    Display:
        system("cls");
        Menu::displayMainMenu();
        do
        {
            cout << "Input your choice: ";
            cin >> choice;
            if (cin.fail())
            {
                cout << "Invalid choice. Please try again!\n";
                cin.clear();             // Xoa trang thai loi
                cin.ignore(32767, '\n'); // Loai bo ki tu khong hop le
                system("pause");
            }
        } while (choice < 0 || choice >= 99);
        switch (choice)
        {
        case 1:
        {
            cout << ORANGE << "\tPLAY WITH OTHER PLAYER: " << RESET << endl;
            // Khởi tạo người chơi
            string play1, play2;
            cout << "Input player 1: ";
            cin.ignore();
            getline(cin, play1);
            cout << "Input player 2: ";
            getline(cin, play2);
            Player *player1 = new Player(play1);
            Player *player2 = new Player(play2);
            Caro game(player1, player2); // Khoi tao tro choi voi 2 nguoi choi
            game.playWithPlayer();
            delete player1;
            delete player2;
            system("pause");
            break;
        }
        case 2:
        {
            system("cls");
            int choice1;
            Menu::menuPlayWithBot();
            do
            {
                cout << "Input your choice: ";
                cin >> choice1;
                if (cin.fail())
                {
                    cout << "Invalid choice. Please try again!\n";
                    cin.clear();             // Xoa trang thai loi
                    cin.ignore(32767, '\n'); // Loai bo ki tu khong hop le
                    system("pause");
                }
            } while (choice < 0 || choice >= 99);
            switch (choice1)
            {
            case 1:
            {
                // Easy Mode
                CaroEasy caroEasy;
                cout << ORANGE << "\tPlay with BOT: Easy Mode" << endl;
                cout << "\t   Human = X. BOT = O." << RESET << endl;

                // Choi che do Easy
                caroEasy.playEasy();
                system("pause");
                goto Display;
                break;
            }
            case 2:
            {
                // Medium Mode
                CaroMedium caroMedium;
                cout << ORANGE << "\tPlay with BOT: Medium Mode" << endl;
                cout << "\t   Human = X. BOT = O." << RESET << endl;

                // Choi che do Medium
                caroMedium.playMedium();
                system("pause");
                goto Display;
                break;
            }
            case 3:
            {
                // Hard Mode
                CaroMedium caroHard;
                cout << ORANGE << "\tPlay with BOT: Hard Mode" << endl;
                cout << "\t   Human = X. BOT = O." << RESET << endl;

                // Choi che do Hard
                caroHard.playHard();
                system("pause");
                goto Display;
                break;
            }
            case 4:
            {
                // Thoat ra man hinh chinh
                cout << "Exiting to Main Menu..." << endl;
                system("pause");
                goto Display;
                break;
            }
            default:
                // Nhap ki tu khong hop le
                cout << "Invalid choice. Please try again!" << endl;
                system("pause");
                goto Display;
                break;
            }
            break;
        }
        case 3:
        {
            // In ra thong tin nguoi dung
            Caro::outputList();
            system("pause");
            break;
        }
        case 4:
        {
            // Tim kiem thong tin nguoi dung
            cout << ORANGE << "\t\t\t\t\tSEARCH PLAYER'S INFORMATION: " << RESET << endl;
            string name;
            cout << "Input player you want to find: ";
            cin.ignore();
            getline(cin, name);
            Caro::findPlayer(name);
            system("pause");
            break;
        }
        case 5:
        {
            // Huong dan choi game Caro
            Menu::Guide();
            system("pause");
            break;
        }
        case 6:
        {
            // Thoat khoi chuong trinh
            cout << "Exiting..." << endl;
            return 0;
            break;
        }
        default:
        {
            // Nhap ki tuj khong hop le
            cout << "Invalid choice. Please try again!" << endl;
            break;
        }
        }
    }
    return 0;
}