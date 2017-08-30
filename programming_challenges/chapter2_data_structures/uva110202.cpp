#include <cstdio>
#include <cstdlib>

#define HAND_SIZE 5
#define VALUE_MIN 2
#define VALUE_MAX 14
#define SUIT_MAX 3

typedef struct {
    char suit;
    char value;
} card;

typedef enum {
    black,
    white,
    tie
} hand;

int suit_to_code(char suit) {
    switch (suit) {
        case 'C':
            return 0;
            break;
        case 'D':
            return 1;
            break;
        case 'H':
            return 2;
            break;
        case 'S':
            return 3;
            break;
    }
}

int value_to_code(char value) {
    switch (value) {
        case 'A':
            return 14;
            break;
        case 'K':
            return 13;
            break;
        case 'Q':
            return 12;
            break;
        case 'J':
            return 11;
            break;
        case 'T':
            return 10;
            break;
        default:
            return value - '0';
            break;
    }
}

int value_occurrence[15];
int suit_occurrence[4];

void fill_occurrences(card hand[HAND_SIZE]) {
    int i;
    for (i = 0; i <= VALUE_MAX; i++) {
        value_occurrence[i] = 0;
    }
    
    for (i = 0; i <= SUIT_MAX; i++) {
        suit_occurrence[i] = 0;
    }

    for (i = 0; i < HAND_SIZE; i++) {
        value_occurrence[value_to_code(hand[i].value)]++;
        suit_occurrence[suit_to_code(hand[i].suit)]++;
    }
}

int high_occurrence(int occurr_qty, int position) {
    int i;
    for (i = VALUE_MAX; i >= VALUE_MIN; i--) {
        if (value_occurrence[i] == occurr_qty) {
            position--;

            if (!position)
                return i;
        }
    }

    return 0;
}

int high_card(card hand[HAND_SIZE], int position) {
    fill_occurrences(hand);
    return high_occurrence(1, position);
}

int pair(card hand[HAND_SIZE], int position) {
    int result;
    
    fill_occurrences(hand);
    
    if (position == 1)
        result = high_occurrence(2, 1);
    else
        result = high_occurrence(1, position - 1);

    if (result)
        result += 100;

    return result;
}

int two_pairs(card hand[HAND_SIZE], int position) {
    int result;
    
    fill_occurrences(hand);
    
    if (position == 1) {
        result = high_occurrence(2, 2);    
        if (result)
            result = high_occurrence(2, 1);
    } else if (position == 2) 
        result = high_occurrence(2, 2);
    else
        result = high_occurrence(1, 1);

    if (result)
        result += 200;

    return result;
}

int three_of_a_kind(card hand[HAND_SIZE]) {
    int result;
    
    fill_occurrences(hand);
    result = high_occurrence(3, 1);

    if (result)
        result += 300;

    return result;
}

int straight(card hand[HAND_SIZE]) {
    int i, result, value;
    
    fill_occurrences(hand);

    value = high_occurrence(1, 1);
    result = 1;

    for (i = 1; i < 5; i++) {
        result &= value_occurrence[value - i];
    }

    if (result)
        value += 400;
    else
        value = 0;

    return value;
}

int flush(card hand[HAND_SIZE], int position) {
    int i, result = 0;
    
    fill_occurrences(hand);

    for (i = 0; i <= SUIT_MAX; i++) {
        if (suit_occurrence[i] == 5) {
            result = high_occurrence(1, position);
            break;
        }
    }

    if (result)
        result += 500;

    return result;
}

int full_house(card hand[HAND_SIZE]) {
    int result;
    
    fill_occurrences(hand);
    result = high_occurrence(2, 1);

    if (result) {
        result = high_occurrence(3, 1);

        if (result)
            result += 600;
    }

    return result;
}

int four_of_a_kind(card hand[HAND_SIZE]) {
    int result;
    
    fill_occurrences(hand);
    result = high_occurrence(4, 1);

    if (result)
        result += 700;

    return result;
}

int straight_flush(card hand[HAND_SIZE]) {
    int result;
    fill_occurrences(hand);
    
    result = flush(hand, 1);

    if (result) {
        result = straight(hand);

        if (result)
            result += 400;
    }

    return result;
}

hand get_winner(card black_hand[HAND_SIZE], card white_hand[HAND_SIZE]) {
    int res_black, res_white;
    int pos;
    
    res_black = straight_flush(black_hand);
    res_white = straight_flush(white_hand);

    !res_black && (res_black = four_of_a_kind(black_hand));
    !res_white && (res_white = four_of_a_kind(white_hand));

    !res_black && (res_black = full_house(black_hand));    
    !res_white && (res_white = full_house(white_hand));
    
    pos = 0;
    if (!res_black && !res_white)
        do {
            res_black = flush(black_hand, ++pos); 
            res_white = flush(white_hand, pos);
        } while (res_black == res_white && res_black && pos < 5);

    !res_black && (res_black = straight(black_hand));    
    !res_white && (res_white = straight(white_hand));

    !res_black && (res_black = three_of_a_kind(black_hand));    
    !res_white && (res_white = three_of_a_kind(white_hand));

    pos = 0;
    if (!res_black && !res_white)
        do {
            res_black = two_pairs(black_hand, ++pos); 
            res_white = two_pairs(white_hand, pos);
        } while (res_black == res_white && res_black && pos < 5);
    
    pos = 0;
    if (!res_black && !res_white)
        do {
            res_black = pair(black_hand, ++pos);
            res_white = pair(white_hand, pos);
        } while (res_black == res_white && res_black && pos < 5);
    
    pos = 0;
    if (!res_black && !res_white)
        do {
            res_black = high_card(black_hand, ++pos);
            res_white = high_card(white_hand, pos);
        } while (res_black == res_white && res_black && pos < 5);

    if (res_black > res_white)
        return black;
    else if (res_black < res_white)
        return white;
    else
        return tie;
}

int main() {
    int i;
    card black_hand[5];
    card white_hand[5];

    while (!feof(stdin)) {
        for (i = 0; i < 5; i++) {
            scanf("%c%c ", &black_hand[i].value, &black_hand[i].suit);
        }

        for (i = 0; i < 5; i++) {
            scanf("%c%c ", &white_hand[i].value, &white_hand[i].suit);
        }
    
        hand result = get_winner(black_hand, white_hand);

        if (result == black)
            printf("Black wins.\n");
        else if (result == white)
            printf("White wins.\n");
        else
            printf("Tie.\n");
    }

    return EXIT_SUCCESS;
}
