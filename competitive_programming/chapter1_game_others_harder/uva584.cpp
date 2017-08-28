#include <cstdio>

int value_round(char game[], int i) 
{
    if (game[i] == '_') 
        return value_round(game, i + 1);
    else if (game[i] == 'X')
        return 10;
    else if (game[i] == '/')
        return 10 - value_round(game, i - 1);
    else
        return game[i] - '0';
}

int value_frame(char game[], int i) 
{
    int result = 0;
    if (game[i] == 'X') {
        result = 10 + value_round(game, i + 2) + value_round(game, i + 3);
    } else if (game[i + 1] == '/') {
        result = 10 + value_round(game, i + 2);
    } else {
        result = value_round(game, i) + value_round(game, i + 1);
    }
    return result;
}

bool is_valid_game(char c) 
{
    return c != 'G' && c != 'a' && c != 'm' && c != 'e' && c != 'O' && c != 'v' && c != 'r';
}

int main()
{
    char game[25], c;
    int r, i, game_size, points;
    while (scanf(" %c", &c) && is_valid_game(c)) {
        for (i = 0; i < 25; i++) game[i] = '0';
        game[0] = c;
        
        game_size = 20;
        for (i = 1; i < game_size; i++) {
            if (i == 1 && game[i - 1] == 'X') {
                game[i] = '_';
                continue;
            }
            scanf(" %c", &game[i]);
            
            if (game[i] == 'X' && i == 18) game_size += 2;
            if (game[i] == '/' && i == 19) game_size += 1;
            if (game[i] == 'X' && i < 20) game[++i] = '_';
        }

        points = 0;
        for (i = 0; i < 20; i += 2) {
            points += value_frame(game, i);
//            printf("%c %c - %d\n", game[i], game[i + 1], value_frame(game, i));
        }
/*        
        printf(": %3d -> ", points);
        for (i = 0; i < game_size; i++) {
            printf("%c ", game[i]);
            if (i % 2) printf("| ");
        }
*/
        printf("%d\n", points);
    }
}
