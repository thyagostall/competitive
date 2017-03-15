#include <cstdio>
#include <cstring>
#include <cmath>

#define MAX_SQR 101
#define MAX_STR 10010

char square[MAX_SQR][MAX_SQR];

char buff1[MAX_STR];
char buff2[MAX_STR];
char buff3[MAX_STR];
char buff4[MAX_STR];

bool is_alpha(char c) 
{
    return c >= 'a' && c <= 'z';
}

void hash(char in[], int size, char out[], int *out_size)
{
    int i;
    *out_size = 0;
    for (i = 0; i < size; i++) {
        if (is_alpha(in[i])) {
            out[(*out_size)++] = in[i];
        }
    }
    out[*out_size] = 0;
}

void make_square(char hashed_phrase[], int square_side)
{
    int i, j, k;

    k = 0;
    for (i = 0; i < square_side; i++) {
        for (j = 0; j < square_side; j++) {
            square[i][j] = hashed_phrase[k++];
        }
    }
}

bool is_magic_square(int square_side)
{
    int i, j, rev_i, rev_j, n, cmp;

    n = 0;
    for (i = 0; i < square_side; i++) {
        rev_i = square_side - i - 1;
        for (j = 0; j < square_side; j++) {
            rev_j = square_side - j - 1;
            
            buff1[n] = square[i][j];
            buff2[n] = square[j][i];
            buff3[n] = square[rev_i][rev_j];
            buff4[n] = square[rev_j][rev_i];
            n++;
        }
    }
    buff1[n] = 0;
    buff2[n] = 0;
    buff3[n] = 0;
    buff4[n] = 0;
    
    cmp = strcmp(buff1, buff2);
    cmp += strcmp(buff2, buff3);
    cmp += strcmp(buff3, buff4);
    return cmp == 0;
}

int get_square_side(int p)
{
    float root, fractpart, result;
    fractpart = modff(sqrt(p), &result);
    if (fractpart > 0) {
        return -1;
    } else {
        return (int) result;
    }   
}

int main()
{
    int t, n, size, square_side, hash_size;
    char raw_phrase[MAX_STR], hashed[MAX_STR];
    
    scanf("%d ", &t);
    for (n = 1; n <= t; n++) {
        fgets(raw_phrase, MAX_STR, stdin);
        size = strlen(raw_phrase);
        
        hash(raw_phrase, size, hashed, &hash_size);
       
        square_side = get_square_side(hash_size);
        make_square(hashed, square_side);

        printf("Case #%d:\n", n);
        if (square_side >= 0 && is_magic_square(square_side)) {
            printf("%d\n", square_side);
        } else {
            printf("No magic :(\n");
        }
    }
}
