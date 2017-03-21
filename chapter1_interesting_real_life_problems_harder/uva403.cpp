#include <cstdio>
#include <cstring>
#include <cmath>

#define GRID 61

char fonts[][6][7] = {
    {".***..",
     "*...*.",
     "*****.",
     "*...*.",
     "*...*."},

    {"****..",
     "*...*.",
     "****..",
     "*...*.",
     "****.."},

    {".****.",
     "*...*.",
     "*.....",
     "*.....",
     ".****."},

    {"****..",
     "*...*.",
     "*...*.",
     "*...*.",
     "****.."},

    {"*****.",
     "*.....",
     "***...",
     "*.....",
     "*****."},

    {"*****.",
     "*.....",
     "***...",
     "*.....",
     "*....."},

    {".****.",
     "*.....",
     "*..**.",
     "*...*.",
     ".***.."},

    {"*...*.",
     "*...*.",
     "*****.",
     "*...*.",
     "*...*."},

    {"*****.",
     "..*...",
     "..*...",
     "..*...",
     "*****."},

    {"..***.",
     "...*..",
     "...*..",
     "*..*..",
     ".**..."},

    {"*...*.",
     "*..*..",
     "***...",
     "*..*..",
     "*...*."},

    {"*.....",
     "*.....",
     "*.....",
     "*.....",
     "*****."},

    {"*...*.",
     "**.**.",
     "*.*.*.",
     "*...*.",
     "*...*."},

    {"*...*.",
     "**..*.",
     "*.*.*.",
     "*..**.",
     "*...*."},

    {".***..",
     "*...*.",
     "*...*.",
     "*...*.",
     ".***.."},

    {"****..",
     "*...*.",
     "****..",
     "*.....",
     "*....."},

    {".***..",
     "*...*.",
     "*...*.",
     "*..**.",
     ".****."},

    {"****..",
     "*...*.",
     "****..",
     "*..*..",
     "*...*."},

    {".****.",
     "*.....",
     ".***..",
     "....*.",
     "****.."},

    {"*****.",
     "*.*.*.",
     "..*...",
     "..*...",
     ".***.."},

    {"*...*.",
     "*...*.",
     "*...*.",
     "*...*.",
     ".***.."},

    {"*...*.",
     "*...*.",
     ".*.*..",
     ".*.*..",
     "..*..."},

    {"*...*.",
     "*...*.",
     "*.*.*.",
     "**.**.",
     "*...*."},

    {"*...*.",
     ".*.*..",
     "..*...",
     ".*.*..",
     "*...*."},

    {"*...*.",
     ".*.*..",
     "..*...",
     "..*...",
     "..*..."},

    {"*****.",
     "...*..",
     "..*...",
     ".*....",
     "*****."}

};

void parse_three_args(char *font, int *r, int *c, char *string)
{
    scanf("%s", font);
    scanf("%d %d", r, c);
    scanf(" %[^\n]", string);
}

void parse_two_args(char *font, int *r, char *string)
{
    scanf("%s", font);
    scanf("%d", r);
    scanf(" %[^\n]", string);
}

bool is_p(char *command)
{
    return strcmp(command, ".P") == 0;
}

bool is_l(char *command)
{
    return strcmp(command, ".L") == 0;
}

bool is_r(char *command)
{
    return strcmp(command, ".R") == 0;
}

bool is_c(char *command)
{
    return strcmp(command, ".C") == 0;
}

bool is_eop(char *command)
{
    return strcmp(command, ".EOP") == 0;
}

bool is_c1_font(char *font)
{
    return strcmp(font, "C1") == 0;
}

void clear_page(char page[GRID][GRID]) 
{
    int i, j;
    for (i = 1; i < GRID; i++) {
        for (j = 1; j < GRID; j++) {
            page[i][j] = '.';
        }
    }
}

void print(char page[GRID][GRID]) 
{
    int i, j;
    for (i = 1; i < GRID; i++) {
        for (j = 1; j < GRID; j++) {
            printf("%c", page[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (i = 1; i < GRID; i++) {
        printf("-");
    }
    printf("\n\n");
}

void print_c1_char(char x, int r, int c, char page[GRID][GRID])
{
    if (x == ' ') {
        return;
    }

    page[r][c] = x;
}

void print_c5_char(char x, int r, int c, char page[GRID][GRID])
{
    if (x < 'A' || x > 'Z') {
        return;
    }

    int i, j;
    char t;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++) {
            if (r + i < 0 || r + i >= GRID || c + j < 0 || c + j >= GRID) {
                continue;
            }

            t = fonts[x - 'A'][i][j];
            if (t != '.') {
                page[r + i][c + j] = t;
            }
        }
    }
}

void print_c1_string(char *string, int r, int c, char page[GRID][GRID])
{
    int i, len;
    
    len = strlen(string) - 1;
    for (i = 1; i < len; i++, c++) {
        if (c >= GRID) {
            continue;
        }

        print_c1_char(string[i], r, c, page);
    }
}

void print_c5_string(char *string, int r, int c, char page[GRID][GRID])
{
    int i, len;
    
    len = strlen(string) - 1;
    for (i = 1; i < len; i++, c += 6) {
        print_c5_char(string[i], r, c, page);
    }
}

int main()
{
    int r, c, len;
    char command[5], font[3], string[65], page[GRID][GRID];
    
    clear_page(page);
    while (scanf("%s", command) != EOF) {
        if (is_p(command)) {
            parse_three_args(font, &r, &c, string);
            if (is_c1_font(font)) {
                print_c1_string(string, r, c, page);
            } else {
                print_c5_string(string, r, c, page);
            }
        } else if (is_l(command)) {
            parse_two_args(font, &r, string);
            if (is_c1_font(font)) {
                print_c1_string(string, r, 1, page);
            } else {
                print_c5_string(string, r, 1, page);
            }
        } else if (is_r(command)) {
            parse_two_args(font, &r, string);
            len = strlen(string) - 2;
            if (is_c1_font(font)) {
                print_c1_string(string, r, GRID - len, page);
            } else {
                print_c5_string(string, r, GRID - len * 6, page);
            }
        } else if (is_c(command)) {
            parse_two_args(font, &r, string);
            len = strlen(string) - 2;
            if (is_c1_font(font)) {
                c = 30 - len / 2 + 1;
                print_c1_string(string, r, c, page);
            } else {
                len *= 6;
                c = 30 - len / 2 + 1;
                print_c5_string(string, r, c, page);
            }
        } else if (is_eop(command)) {
            print(page);
            clear_page(page);
        }
    }    
}
