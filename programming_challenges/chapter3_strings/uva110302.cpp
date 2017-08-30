#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 52

char game[SIZE][SIZE];
int rows, cols;

typedef struct {
    int x;
    int y;
} point;

bool find_word_place(char *word, int x, int y, int inc_x, int inc_y) {
    int word_len = strlen(word);
    int i;
    bool result = true;

    for (i = 0; i < word_len; i++) {
        result &= word[i] == game[x][y];

        x += inc_x;
        y += inc_y;

        if (x < 0 || x > rows || y < 0 || y > cols)
            return false;
    }

    return result;
}

point *find_word_internal(char *word, int x, int y) {
    int i, j;
    point *result;

    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)
				continue;
				
            if (find_word_place(word, x, y, i, j)) {
				result->x = x;
				result->y = y;
				return result;
			}
        }
    }

    result = (point *) malloc(sizeof(point));
    result->x = -1;
    result->y = -1;
    return result;
}

bool is_valid_point(point *p) {
    return p->x != -1 && p->y != -1;
}

point *find_word(char *word) {
    int i, j;
    point *result;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            result = find_word_internal(word, i, j);
            if (is_valid_point(result))
                return result;
        }
    }
    
    result = (point *) malloc(sizeof(point));
    result->x = -1;
    result->y = -1;
    return result;
}

void lowerword(char *word) {
    while (*word) {
        *word = tolower(*word);
        word++;
    }
}

int main() {
    char word[SIZE];
    char *l;

    int test_cases, words, len, c, i;

    scanf("%d", &test_cases);

    for (c = 0; c < test_cases; c++) {
        scanf("%d %d", &rows, &cols);

        for (i = 0; i < rows; i++) {
            scanf("%s", game[i]);
            lowerword(game[i]);
        }

        scanf("%d", &words);

        for (i = 0; i < words; i++) {
            scanf("%s", word);
            lowerword(word);
            point *result = find_word(word);
            printf("%d %d\n", result->x + 1, result->y + 1);
        }
    }

    return EXIT_SUCCESS;
}
