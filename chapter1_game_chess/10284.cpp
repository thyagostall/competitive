#include <iostream>

using namespace std;

char board[10][10];

void init_board()
{
    int i, j;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            board[i][j] = ' ';
}

void print_board() 
{
    int i, j;
    for (i = 0; i < 8; i++) {
        cout << "|";
        for (j = 0; j < 8; j++) {
            cout << board[i][j] << "|";
        }
        cout << endl;
    }
}

void check_straight(int oi, int oj)
{
    int i, j;
    for (i = oi - 1; i >= 0; i--) {
        if (board[i][oj] != ' ') break;
        board[i][oj] = 'x';
    }
    for (i = oi + 1; i < 8; i++) {
        if (board[i][oj] != ' ') break;
        board[i][oj] = 'x';
    }
    for (j = oj - 1; j >= 0; j--) {
        if (board[oi][j] != ' ') break;
        board[oi][j] = 'x';
    }
    for (j = oj + 1; j < 8; j++) {
        if (board[oi][j] != ' ') break;
        board[oi][j] = 'x';
    }
}

void check_diag(int oi, int oj)
{
    int i, j;
    for (i = oi - 1, j = oj - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] != ' ') break;
        board[i][j] = 'x';
    }
    for (i = oi - 1, j = oj + 1; i >= 0 && j < 8; i--, j++) {
        if (board[i][j] != ' ') break;
        board[i][j] = 'x';
    }
    for (i = oi + 1, j = oj - 1; i < 8 && j >= 0; i++, j--) {
        if (board[i][j] != ' ') break;
        board[i][j] = 'x';
    }
    for (i = oi + 1, j = oj + 1; i < 8 && j < 8; i++, j++) {
        if (board[i][j] != ' ') break;
        board[i][j] = 'x';
    }
}

void check_spec(int i, int j) 
{
    if (i < 0 || j < 0 || i >= 8 || j >= 8 || board[i][j] != ' ') return;
    board[i][j] = 'x';
}

void check_p(int i, int j)
{
    check_spec(i + 1, j - 1);
    check_spec(i + 1, j + 1);
}

void check_P(int i, int j)
{
    check_spec(i - 1, j - 1);
    check_spec(i - 1, j + 1);
}

void check_b(int i, int j)
{
    check_diag(i, j);
}

void check_r(int i, int j)
{
    check_straight(i, j);
}

void check_q(int i, int j)
{
    check_diag(i, j);
    check_straight(i, j);
}

void check_k(int oi, int oj)
{
    int i, j;
    for (i = oi - 1; i <= oi + 1; i++) {
        for (j = oj - 1; j <= oj + 1; j++) {
            if (i == oi && j == oj) continue;
            check_spec(i, j);
        }
    }
}

void check_n(int i, int j)
{
    check_spec(i - 1, j - 2);
    check_spec(i - 2, j - 1);
    
    check_spec(i - 1, j + 2);
    check_spec(i - 2, j + 1);
    
    check_spec(i + 1, j - 2);
    check_spec(i + 2, j - 1);
    
    check_spec(i + 1, j + 2);
    check_spec(i + 2, j + 1);
}

int main()
{
    init_board();
    check_n(3, 3);
    print_board();
}
