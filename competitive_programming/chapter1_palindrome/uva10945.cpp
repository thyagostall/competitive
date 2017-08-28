#include <cstdio>
#include <cstdlib>
#include <cstring>

#define STR_MAX 1000

char lower[] = "abcdefghijklmnopqrstuvwxyz";

bool isalpha(char c)
{
    return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z';
}

char tolower(char c)
{
    int i = c - 'A';
    if (i >= 0 && i <= 25) {
        return lower[i];
    } else {
        return c;
    }
}

void hash(char in[], int size, char out[], int *new_size)
{
    int i;
    for (i = 0; i < size; i++) {
        if (!isalpha(in[i])) {
            continue;
        }
        
        out[(*new_size)++] = tolower(in[i]);
    } 
    out[*new_size] = 0;
}

bool is_palindrome(char hashed_phrase[], int size)
{
    int i, j;
    for (i = 0, j = size - 1; j > i; i++, j--) {
        if (hashed_phrase[i] != hashed_phrase[j]) {
            return false;
        }
    }
    return true;
}

int main()
{
    char raw_phrase[STR_MAX], hashed[STR_MAX];
    int size, new_size;

    while (fgets(raw_phrase, STR_MAX, stdin) && strcmp(raw_phrase, "DONE\n") != 0) {
        size = strlen(raw_phrase);
        new_size = 0;

        hash(raw_phrase, size, hashed, &new_size);
        if (is_palindrome(hashed, new_size)) {
            printf("You won't be eaten!\n");
        } else {
            printf("Uh oh..\n");
        }
    }
}
