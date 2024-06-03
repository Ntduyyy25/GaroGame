#include "CaroMedium.h"
#include <iostream>

using namespace std;

const int AttackArr[5] = {0, 3, 25, 500, 3000}; // Điểm tấn công
const int DefendArr[5] = {0, 2, 20, 300, 1200}; // Điểm phòng ngự

// Ham kiem tra o co bi chan khong
bool CaroMedium::isBlocked(int x, int y)
{
    return (x < 0 || x >= SIZE || y < 0 || y >= SIZE);
}

int CaroMedium::attackPoint(int x, int y)
{
    // Các hướng di chuyển chính
    int tX[4] = {1, 0, 1, 1};
    int tY[4] = {0, 1, 1, -1};

    int Ally[4] = {}, Enemy[4] = {}, Block[4] = {};

    for (int k = 0; k < 4; k++)
    {
        for (int dir = -1; dir <= 1; dir += 2)
        {
            for (int i = 1; i < 4; i++)
            {
                int newX = x + i * tX[k] * dir;
                int newY = y + i * tY[k] * dir;

                // Kiểm tra nếu ô cần đánh đã bị chặn
                if (isBlocked(newX, newY))
                {
                    Block[k]++;
                    break;
                }

                if (caro.board[newX][newY] == ' ')
                    continue;

                if (caro.board[newX][newY] == 'O')
                    Ally[k]++;

                if (caro.board[newX][newY] == 'X')
                {
                    Enemy[k]++;
                    break;
                }
            }
        }
    }

    int SumPoint = 0;
    for (int i = 0; i < 4; i++)
    {
        int Point = AttackArr[Ally[i]];

        // Ưu tiên đánh nước có 3 quân cờ
        if (Ally[i] == 3)
            Point = AttackArr[4];
        else if (Ally[i] == 2)
            Point = AttackArr[3];

        // Giảm điểm nếu bị chặn
        if (Enemy[i] == 1 || Block[i] == 1)
            Point /= 2;

        else if (Enemy[i] >= 1 && Block[i] == 1)
            Point = AttackArr[0];

        // Không đánh nếu bị chặn cả hai đầu
        else if (Enemy[i] == 2)
            Point = AttackArr[0];
        else if (Enemy[i] == 0 && Ally[i] == 0 && Block[i] == 1)
            Point = AttackArr[0];

        // Không đánh nếu bị chặn ở hai đầu
        else if (Enemy[i] == 1 && Ally[i] < 3 && Block[i] == 1)
            Point = AttackArr[0];

        SumPoint += Point;
    }

    return SumPoint;
}

int CaroMedium::defendPoint(int x, int y)
{
    // Các hướng di chuyển chính
    int tX[4] = {1, 0, 1, 1};
    int tY[4] = {0, 1, 1, -1};

    int Ally[4] = {}, Enemy[4] = {}, Block[4] = {};

    for (int k = 0; k < 4; k++)
    {
        for (int dir = -1; dir <= 1; dir += 2)
        {
            for (int i = 1; i < 4; i++)
            {
                int newX = x + i * tX[k] * dir;
                int newY = y + i * tY[k] * dir;

                // Kiểm tra nếu ô cần đánh đã bị chặn
                if (isBlocked(newX, newY))
                {
                    Block[k]++;
                    break;
                }

                if (caro.board[newX][newY] == ' ')
                    // continue;
                    break;

                if (caro.board[newX][newY] == 'X')
                    Enemy[k]++;

                if (caro.board[newX][newY] == 'O')
                {
                    Ally[k]++;
                    break;
                }
            }
        }
    }

    int SumPoint = 0;
    for (int i = 0; i < 4; i++)
    {
        int Point = DefendArr[Enemy[i]];

        // Ưu tiên chặn nước có 3 quân cờ
        if (Enemy[i] == 3)
            Point = DefendArr[4];

        else if (Enemy[i] == 2)
        {
            if (Block[i] == 0)
                Point = DefendArr[3];
            else
                Point = DefendArr[0];
        }

        else if (Block[i] == 1 && Enemy[i] == 1)
            Point = DefendArr[0];

        // Không đánh nếu bị chặn ở hai đầu
        else if (Ally[i] == 1 && Enemy[i] < 3 && Block[i] == 1)
            Point = DefendArr[0];

        // Không đánh nếu bị chặn cả hai đầu
        else if (Ally[i] == 2)
            Point = DefendArr[0];

        SumPoint += Point;
    }

    return SumPoint;
}

pair<int, int> CaroMedium::getBestMove()
{
    int bestScore = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    // Duyệt qua từng ô trống trên bàn cờ
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (caro.board[i][j] == ' ')
            {
                int attackScore = attackPoint(i, j);
                int defendScore = defendPoint(i, j);
                int totalScore = attackScore + defendScore;

                // Nếu điểm này tốt hơn điểm tốt nhất hiện tại, cập nhật
                if (totalScore > bestScore)
                {
                    bestScore = totalScore;
                    bestMove = {i, j};
                }
            }
        }
    }

    return bestMove;
    return pair<int, int>();
}

void CaroMedium::playMedium()
{
    caro.record(0, 0, 0);
    bool gameOver = false;
    bool playerTurn = true; // Lượt của người chơi đầu tiên
    caro.initBoard();
    caro.m_currentIndex = 0;

    while (!gameOver)
    {
        // In bàn cờ sau mỗi lượt đi
        caro.printBoard();
        if (playerTurn)
        {
            // Lượt của người chơi
            int row, col;

            // Nhap nuoc di tu ban phim
            do
            {
                cout << "-> Your turn. Input row and column: ";
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
            if (caro.isValidMove(row, col))
            {
                caro.record(row, col, 1);
                caro.makeMove(row, col);

                if (caro.checkWin(row, col))
                {
                    caro.printBoard();
                    cout << ORANGE << "\n\t=> Congratulations! You win!" << RESET << endl;
                    gameOver = true;
                }
                else if (caro.checkDraw())
                {
                    caro.printBoard();
                    cout << ORANGE << "\n\t=> It's a draw!" << RESET << endl;
                    gameOver = true;
                }
                caro.switchPlayer();
                playerTurn = false;
            }
            else
            {
                cout << "Invalid move! Try again." << endl;
            }
        }
        else
        {
            // Lượt của máy chơi
            pair<int, int> aiMove = getBestMove();
            int aiRow = aiMove.first;
            int aiCol = aiMove.second;
            caro.record(aiRow, aiCol, 1);
            cout << "-> BOT moves to: " << aiRow << ", " << aiCol << endl;
            caro.makeMove(aiRow, aiCol);

            if (caro.checkWin(aiRow, aiCol))
            {
                caro.printBoard();
                cout << ORANGE << "\n\t=> BOT wins!" << RESET << endl;
                gameOver = true;
            }
            else if (caro.checkDraw())
            {
                caro.printBoard();
                cout << ORANGE << "\n\t=> It's a draw!" << RESET << endl;
                gameOver = true;
            }
            caro.switchPlayer();
            playerTurn = true;
        }
    }
    // Lua chon sau choi game
    bool exit = 0;
    while (!exit)
    {
        caro.menuAfterPlay();
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
            playMedium();
            break;
        }
        case 2:
        {
            system("cls");
            caro.watchReplay();
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

void CaroMedium::playHard()
{
    caro.record(0, 0, 0);
    bool gameOver = false;
    bool playerTurn = true;
    caro.initBoard();
    caro.m_currentIndex = 1;

    // Kiểm tra xem bot có đánh trước ở vị trí (5, 5) hay không
    bool botStarts = true; // Đặt thành true nếu bạn muốn bot đánh trước, false nếu muốn người chơi đánh trước
    if (botStarts)
    {
        // Lượt của bot
        pair<int, int> aiMove = {5, 5};
        int aiRow = aiMove.first;
        int aiCol = aiMove.second;

        caro.record(aiRow, aiCol, 1);
        cout << "-> BOT moves to: " << aiRow << ", " << aiCol << endl;
        caro.makeMove(aiRow, aiCol);
        caro.switchPlayer();
        playerTurn = true;
    }
    while (!gameOver)
    {
        // In ban co sau moi luot di
        caro.printBoard();
        if (playerTurn)
        {
            // Lượt của người chơi
            int row, col;

            // Nhap nuoc di tu ban phim
            do
            {
                cout << "-> Your turn. Input row and column: ";
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

            if (caro.isValidMove(row, col))
            {
                caro.record(row, col, 1);
                caro.makeMove(row, col);
                if (caro.checkWin(row, col))
                {
                    caro.printBoard();
                    cout << ORANGE << "\n\t=> Congratulations! You win!" << RESET << endl;
                    gameOver = true;
                }
                else if (caro.checkDraw())
                {
                    caro.printBoard();
                    cout << ORANGE << "\n\t=> It's a draw!" << RESET << endl;
                    gameOver = true;
                }
                caro.switchPlayer();
                playerTurn = false;
            }
            else
            {
                cout << "Invalid move! Please try again!" << endl;
            }
        }
        else
        {
            // Lượt của máy chơi
            pair<int, int> aiMove = getBestMove();
            int aiRow = aiMove.first;
            int aiCol = aiMove.second;
            caro.record(aiRow, aiCol, 1);

            cout << "-> BOT moves to: " << aiRow << ", " << aiCol << endl;
            caro.makeMove(aiRow, aiCol);

            if (caro.checkWin(aiRow, aiCol))
            {
                caro.printBoard();
                cout << ORANGE << "\n\t=> BOT wins!" << RESET << endl;
                gameOver = true;
            }
            else if (caro.checkDraw())
            {
                caro.printBoard();
                cout << ORANGE << "\n\t=> It's a draw!" << RESET << endl;
                gameOver = true;
            }
            caro.switchPlayer();
            playerTurn = true;
        }
    }
    // Lua chon sau choi game
    bool exit = 0;
    while (!exit)
    {
        caro.menuAfterPlay();
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
            playHard();
            break;
        }
        case 2:
        {
            system("cls");
            caro.watchReplay();
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
