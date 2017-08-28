#include <iostream>
#include <sstream>

using namespace std;

char board[10][10];

void init_board()
{
    int i, j;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            board[i][j] = ' ';
}

bool empty(int i, int j)
{
    return board[i][j] == ' ' || board[i][j] == 'x';
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
        if (!empty(i, oj)) break;
        board[i][oj] = 'x';
    }
    for (i = oi + 1; i < 8; i++) {
        if (!empty(i, oj)) break;
        board[i][oj] = 'x';
    }
    for (j = oj - 1; j >= 0; j--) {
        if (!empty(oi, j)) break;
        board[oi][j] = 'x';
    }
    for (j = oj + 1; j < 8; j++) {
        if (!empty(oi, j)) break;
        board[oi][j] = 'x';
    }
}

void check_diag(int oi, int oj)
{
    int i, j;
    for (i = oi - 1, j = oj - 1; i >= 0 && j >= 0; i--, j--) {
        if (!empty(i, j)) break;
        board[i][j] = 'x';
    }
    for (i = oi - 1, j = oj + 1; i >= 0 && j < 8; i--, j++) {
        if (!empty(i, j)) break;
        board[i][j] = 'x';
    }
    for (i = oi + 1, j = oj - 1; i < 8 && j >= 0; i++, j--) {
        if (!empty(i, j)) break;
        board[i][j] = 'x';
    }
    for (i = oi + 1, j = oj + 1; i < 8 && j < 8; i++, j++) {
        if (!empty(i, j)) break;
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
    char c;
    int i, j, v, result;
    string line;
    stringstream ss;

    while (getline(cin, line)) {
        ss << line;
        init_board();
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8;) {
                ss >> c;
                v = c - '0';       
                if (v > 0 && v < 9) {
                    j += v;
                } else if (c != '/') {
                    board[i][j++] = c;
                }
            }
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                switch (board[i][j]) {
                    case 'p':
                        check_p(i, j); break;
                    case 'P':
                        check_P(i, j); break;
                    case 'n':
                    case 'N':
                        check_n(i, j); break;
                    case 'b':
                    case 'B':
                        check_b(i, j); break;
                    case 'r':
                    case 'R':
                        check_r(i, j); break;
                    case 'q':
                    case 'Q':
                        check_q(i, j); break;
                    case 'k':
                    case 'K':
                        check_k(i, j); break;
                }
            }
        }
        result = 0;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (board[i][j] == ' ') result++;
            }
        }
        cout << result << endl;
    }
}
