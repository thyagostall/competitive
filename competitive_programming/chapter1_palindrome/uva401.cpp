#include <cstdio>
#include <cstring>

char equivalent_letters[] = "ABCD3FGHILKJMNOPQR2TUVWXY5";
char equivalent_numbers[] = "1SE4Z6789";

char does_mirror_letters[] = "A   3  HIL JM O   2TUVWXY5";
char does_mirror_numbers[] = "1SE Z  8 ";

char equivalent(char c)
{
    if (c < 'A')
        return equivalent_numbers[c - '1'];
    else
        return equivalent_letters[c - 'A'];
}

void reverse(char word[], char rev[], int size) 
{
    int i;
    for (i = 0; i < size; i++) {
        rev[i] = equivalent(word[i]);
    }
    rev[i] = 0;
}

bool is_palindrome(char word[], int size)
{
    int i, j;
    for (i = 0, j = size - 1; j > i; i++, j--) {
        if (word[i] != word[j]) {
            return false;   
        }
    }
    return true;
}

bool does_mirror(char c)
{
    if (c < 'A')
        return does_mirror_numbers[c - '1'] != ' ';
    else
        return does_mirror_letters[c - 'A'] != ' ';
}

bool is_mirrored(char word[], char rev[], int size)
{
    int i;
    for (i = 0; i < size; i++) {
        if (word[i] != rev[size - 1 - i] || !does_mirror(word[i]))
            return false;
    }
    return true;    
}

int main() 
{
    int size;
    char word[25], rev[25];
    bool mirrored, palindrome;
    while (scanf("%s", word) != EOF) {
        size = strlen(word);
        reverse(word, rev, size);

        mirrored = is_mirrored(word, rev, size);
        palindrome = is_palindrome(word, size);

        printf("%s", word);
        if (mirrored) {
            if (palindrome) {
                printf(" -- is a mirrored palindrome.");
            } else {
                printf(" -- is a mirrored string.");
            }
        } else {
            if (palindrome) {
                printf(" -- is a regular palindrome.");
            } else {
                printf(" -- is not a palindrome.");
            }
        }
        printf("\n\n");
    }
}
