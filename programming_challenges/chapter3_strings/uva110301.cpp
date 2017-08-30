#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYBOARD_SIZE 47
#define STR_SIZE 1000

char equiv[] = {
    '`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\\',
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/'
};

char keys[] = {
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
    'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\\', 0,
    'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', 0,
    'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 0
};

char get_equivalent(char c) {
    int i;
    for (i = 0; i < KEYBOARD_SIZE; i++)
        if (keys[i] == c)
            return equiv[i];
            
    return c;                    
}

void decode(char *s) {
    int i, length;

    length = strlen(s);
    for (i = 0; i < length; i++) {
        s[i] = get_equivalent(s[i]);
    }
}

int main() {
    char line[STR_SIZE + 10];
    fgets(line, STR_SIZE, stdin);

    while (!feof(stdin)) {
        decode(line);
        printf("%s", line);

        fgets(line, STR_SIZE, stdin);
    }

    return EXIT_SUCCESS;
}
