#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef enum {
    none,
    black,
    white
} color;

void check_board(int game);
bool check_opponent(char piece, int i_b, int j_b);
bool check_position(char a[6][6], int arr_piece_size, int i, int j, int ib, int jb, int offset);
bool get_board_position(int arr_piece_size, int il, int jl, int *ib, int *jb, int offset);
color get_color(char piece);
void get_piece_movements(char piece, char arr_mov[6][6], int *arr_size);
bool read_board();
bool is_board_valid();
bool is_empty(char item);

char board[8][8];

int main() {
    int game = 0;

    while (read_board())
        check_board(++game);
}

void check_board(int game) {
    int i, j;

    for (i = 0; i < 8; i++) 
        for (j = 0; j < 8; j++) {
            if (!is_empty(board[i][j]) && check_opponent(board[i][j], i, j)) {
                if (get_color(board[i][j]) == black)
                    printf("Game #%d: white king is in check.\n", game);
                else
                    printf("Game #%d: black king is in check.\n", game);

                return;
            }
        }

    printf("Game #%d: no king is in check.\n", game);
}

bool check_opponent(char piece, int ib, int jb) {
    char a[6][6];
    int i, j, size;
    bool result = false;
    get_piece_movements(piece, a, &size);

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (a[i][j] != '0' && a[i][j] != 'X') {
                if (check_position(a, size, i, j, ib, jb, 0))
                    return true;
            }
        }
    }

    return false;
}

bool check_position(char a[6][6], int arr_piece_size, int i, int j, int ib, int jb, int offset) {
    int lib = ib, ljb = jb;

    if (get_board_position(arr_piece_size, i, j, &lib, &ljb, offset)) {
        if (get_color(board[ib][jb]) == black && board[lib][ljb] == 'K' || get_color(board[ib][jb]) == white && board[lib][ljb] == 'k') 
            return true;
        else if (is_empty(board[lib][ljb]) && a[i][j] == '2')
            return check_position(a, arr_piece_size, i, j, ib, jb, offset + 1);
        else
            return false;
    } else {
        return false;
    }
}

bool get_board_position(int arr_piece_size, int il, int jl, int *ib, int *jb, int offset) {
    arr_piece_size = arr_piece_size / 2;

    *ib = *ib - arr_piece_size + il;
    *jb = *jb - arr_piece_size + jl;

    if (il < arr_piece_size)
        *ib = *ib - offset;
    else if (il > arr_piece_size)
        *ib = *ib + offset;

    if (jl < arr_piece_size)
        *jb = *jb - offset;
    else if (jl > arr_piece_size)
        *jb = *jb + offset;

    if (*ib < 0 || *ib > 7)
        return false;
    
    if (*jb < 0 || *jb > 7)
        return false;

    return true;
}

color get_color(char piece) {
    if (piece == '.')
        return none;

    if (piece < 96)
        return white;
    else
        return black;
}

void get_piece_movements(char piece, char arr_mov[6][6], int *arr_size) {
    if (piece == 'n' || piece == 'N')
        *arr_size = 5;
    else
        *arr_size = 3;

    switch (piece) {
        case 'p':
            strcpy(arr_mov[0], "000");
            strcpy(arr_mov[1], "0X0");
            strcpy(arr_mov[2], "101");
            break;
        case 'P':
            strcpy(arr_mov[0], "101");
            strcpy(arr_mov[1], "0X0");
            strcpy(arr_mov[2], "000");
            break;
        case 'r':
        case 'R':
            strcpy(arr_mov[0], "020");
            strcpy(arr_mov[1], "2X2");
            strcpy(arr_mov[2], "020");
            break;
        case 'b':
        case 'B':
            strcpy(arr_mov[0], "202");
            strcpy(arr_mov[1], "0X0");
            strcpy(arr_mov[2], "202");
            break;
        case 'q':
        case 'Q':
            strcpy(arr_mov[0], "222");
            strcpy(arr_mov[1], "2X2");
            strcpy(arr_mov[2], "222");
            break;
        case 'k':
        case 'K':
            strcpy(arr_mov[0], "111");
            strcpy(arr_mov[1], "1X1");
            strcpy(arr_mov[2], "111");
            break;
        case 'n':
        case 'N':
            strcpy(arr_mov[0], "01010");
            strcpy(arr_mov[1], "10001");
            strcpy(arr_mov[2], "00X00");
            strcpy(arr_mov[3], "10001");
            strcpy(arr_mov[4], "01010");
            break;
    }
}

bool read_board() {
    int i;

    for (i = 0; i < 8; i++) {
        scanf("%s", board[i]);
    }

    return is_board_valid();
}

bool is_empty(char item) {
    return item == '.';
}

bool is_board_valid() {
    int i, j;

    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            if (board[i][j] != '.')
                return true;

    return false;
}
