#include <cstdio>
#include <cstdlib>
#include <cstring>

#define NOT_FOUND -1
#define ALPHA_SIZE 26
#define STR_SIZE 20
#define MAX_WORDS 1000

typedef struct {
    char hash[MAX_WORDS][STR_SIZE];
    int occur_qty[MAX_WORDS];
    int size;
} hash_occur;

typedef struct {
    char hash[MAX_WORDS][STR_SIZE];
    char word[MAX_WORDS][STR_SIZE];
    int size;
} words;

int char_code(char c) {
    return c - 'a';
}

void calc_hash(char hash[STR_SIZE], char word[STR_SIZE]) {
    int size = strlen(word);
    int i;
    char used[ALPHA_SIZE];

    for (i = 0; i < ALPHA_SIZE; i++) {
        used[i] = 0;
    }

    for (i = 0; i < size; i++) {
        int c = char_code(word[i]);
        if (used[c]) {
            hash[i] = used[c];
        } else {
            hash[i] = i + 1;
            used[c] = i + 1;
        }
    }
}

int get_hash_index(hash_occur *h, char *hash) {
    int i;
    for (i = 0; i < h->size; i++) {
        if (strcmp(h->hash[i], hash) == 0)
            return i;
    }

    return NOT_FOUND;
}

hash_occur *get_hash_occur(words *w) {
    int i, index;
    hash_occur *result = (hash_occur *) malloc(sizeof(hash_occur));
    result->size = 0;

    for (i = 0; i < w->size; i++) {
        index = get_hash_index(result, w->hash[i]);

        if (index == NOT_FOUND) {
            strcpy(result->hash[result->size], w->hash[i]);
            result->occur_qty[result->size] = 1;
            result->size++;
        } else {
            result->occur_qty[index]++;
        }
    }

    return result;
}

bool hash_compatible(hash_occur *h1, hash_occur *h2) {
    int i;
    for (i = 0; i < h2->size; i++) {
        if (get_hash_index(h1, h2->hash[i]) == NOT_FOUND)
            return false;
    }

    return true;
}

bool char_qty_compatible(char w1[MAX_WORDS][STR_SIZE], int size1, char w2[MAX_WORDS][STR_SIZE], int size2) {
    char occur1[ALPHA_SIZE], occur2[ALPHA_SIZE];
    int i, j, size, qty1 = 0, qty2 = 0;
    for (i = 0; i < ALPHA_SIZE; i++) {
        occur1[i] = 0;
        occur2[i] = 0;
    }

    for (i = 0; i < size1; i++) {
        size = strlen(w1[i]);

        for (j = 0; j < size; j++) {
            occur1[char_code(w1[i][j])]++;
        }
    }
    
    for (i = 0; i < size2; i++) {
        size = strlen(w2[i]);

        for (j = 0; j < size; j++) {
            occur2[char_code(w2[i][j])]++;
        }
    }

    for (i = 0; i < ALPHA_SIZE; i++) {
        if (occur1[i])
            qty1++;

        if (occur2[i])
            qty2++;
    }

    return qty1 >= qty2;
}

bool are_compatible(words *w1, words *w2, hash_occur *h1, hash_occur *h2) {
    return hash_compatible(h1, h2) && char_qty_compatible(w1->word, w1->size, w2->word, w2->size);
}

void discover_chars(char w1[STR_SIZE], char w2[STR_SIZE], char known[ALPHA_SIZE]) {
    int i;
    for (i = 0; i < ALPHA_SIZE; i++) {

    }
}

void print_hash(char *hash) {
    while (*hash) {
        printf("%d", *hash++);       
    }

    printf("\n");
}

void print_hash_occur(hash_occur *h) {
    int i;
    for (i = 0; i < h->size; i++) {
        printf("%d\t", h->occur_qty[i]);
        print_hash(h->hash[i]);
    }
}

void add_word(words *w, char *s) {
    int i = w->size;
    strcpy(w->word[i], s);
    calc_hash(w->hash[i], w->word[i]);
    print_hash(w->hash[i]);
    w->size++;
}

int main() {
    words* w1 = (words *) malloc(sizeof(words));
    words* w2 = (words *) malloc(sizeof(words));

    add_word(w1, "abacate");
    add_word(w1, "banana");

    add_word(w2, "bcbdbuf");
    add_word(w2, "cs");

    hash_occur *h1 = get_hash_occur(w1);
    hash_occur *h2 = get_hash_occur(w2);

    print_hash_occur(h1);
    printf("\n");
    print_hash_occur(h2);

    if (are_compatible(w1, w2, h1, h2))
        printf("Compativeis\n");
    else
        printf("Incompativeis\n");

    return EXIT_SUCCESS;
}
