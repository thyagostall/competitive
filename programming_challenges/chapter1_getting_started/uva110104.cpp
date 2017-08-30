#include <cstdio>

#define HEIGHT 30
#define WIDTH 120

int num_source[10][5][3] = {
    {
        {0, 1, 0},
        {2, 0, 2},
        {0, 0, 0},
        {2, 0, 2},
        {0, 1, 0}
	}, {	
        {0, 0, 0},
        {0, 0, 2},
        {0, 0, 0},
        {0, 0, 2},
        {0, 0, 0}
	}, {
        {0, 1, 0},
        {0, 0, 2},
        {0, 1, 0},
        {2, 0, 0},
        {0, 1, 0}
    }, {
        {0, 1, 0},
        {0, 0, 2},
        {0, 1, 0},
        {0, 0, 2},
        {0, 1, 0}
    }, {
        {0, 0, 0},
        {2, 0, 2},
        {0, 1, 0},
        {0, 0, 2},
        {0, 0, 0}
    }, {
        {0, 1, 0},
        {2, 0, 0},
        {0, 1, 0},
        {0, 0, 2},
        {0, 1, 0}
    }, {
        {0, 1, 0},
        {2, 0, 0},
        {0, 1, 0},
        {2, 0, 2},
        {0, 1, 0}
    }, {
        {0, 1, 0},
        {0, 0, 2},
        {0, 0, 0},
        {0, 0, 2},
        {0, 0, 0}
    }, {
        {0, 1, 0},
        {2, 0, 2},
        {0, 1, 0},
        {2, 0, 2},
        {0, 1, 0}
    }, {
        {0, 1, 0},
        {2, 0, 2},
        {0, 1, 0},
        {0, 0, 2},
        {0, 1, 0}
    }
};

int count_char(char *str);
void save_number(int number, int column, int size);
void print_number_matrix(int char_quant, int size);
char get_char_pos(int number, int size, int i, int j);
void clear_array();

char number_matrix[HEIGHT][WIDTH];

int quantity = 0;
int eof = 0;

int main() {
    int size = 0, char_quant, temp;

    scanf("%d", &size);

    while (1) {       
        char str[9];
        scanf("%s", str);

        char_quant = count_char(str);
        int i;

        clear_array();

        for (i = 0; i < char_quant; i++) {
            save_number(str[i] - 48, i, size);
        }

        if (quantity)
            printf("\n");

        eof = scanf("%d", &temp) == EOF;
        print_number_matrix(i, size);

        size = temp;
 
        if (!size || eof)
            break;

        quantity++;
    }

    return 0;
}

int count_char(char *str) {
    int result = 0;

    while (*str++) {
        result++;
    }

    return result;
}

void save_number(int number, int column, int size) {
    int i, j;
    int ini_pos = column * (size + 3);

    int end_wid = (size + 2) + ini_pos;
    int end_hei = (2 * size + 3);

    for (i = ini_pos; i < end_wid; i++) {
        for (j = 0; j < end_hei; j++) {
            number_matrix[j][i] = get_char_pos(number, size, j, i - ini_pos);
        }
    }

    for (j = 0; j < end_hei; j++) {
        number_matrix[j][end_wid] = ' ';
    }
}

void print_number_matrix(int char_quant, int size) {
    int i, j;
    int width, height;

    width = (size + 3) * char_quant - 1;
    height = (2 * size + 3);

    for (j = 0; j < height; j++) {
        number_matrix[j][width] = 0;
    }

    if (eof)
        for (j = width - 1; j >= 0; j--)
            if (number_matrix[height -1][j] == ' ')
                number_matrix[height -1][j] = 0;
            else
                break;

    for (i = 0; i < height; i++)
        printf("%s\n", number_matrix[i]);
}


char get_char_pos(int number, int size, int i, int j) {
    if (j == size + 1) {
        j = 2;
    } else if (j) {
        j = 1;
    }

    if (i > 0) {
        if (i < size + 1) {
            i = 1;
        } else if (i == size + 1) {
            i = 2;
        } else if (i < 2 * (size + 1)) {
            i = 3;
        } else {
            i = 4;
        }
    }
    
    if (num_source[number][i][j] == 0) {
        return ' ';
    } else if (num_source[number][i][j] == 1) {
        return '-';
    } else {
        return '|';
    }
}

void clear_array() {
    int i, j;

    for (i = 0; i < HEIGHT; i++)
        for (j = 0; j < WIDTH; j++)
            number_matrix[i][j] = 0;
}
