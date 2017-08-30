#include <cstdio>
#include <cstdlib>
#include <cstring>

#define INFINITE 10000
#define NO_WINNER -1

typedef struct {
    char name[85];
    int vote_qty;
    bool available;
} candidate;

typedef struct {
    int votes[22];
    int current_vote;
    bool available;
} ballot;

candidate candidates[21];
ballot ballots[1000];

void initialize_available(int qty) {
    int i;

    for (i = 0; i < qty; i++) {
        ballots[i].available = true;
        ballots[i].current_vote = 0;
    }
}

void count_available_votes(int ballots_qty, int candidate_qty) {
    int i;

    for (i = 0; i < ballots_qty; i++) {
        if (ballots[i].available) {
            while (!candidates[ballots[i].votes[ballots[i].current_vote]].available && ballots[i].current_vote < candidate_qty - 1)
                ballots[i].current_vote++;

            candidates[ballots[i].votes[ballots[i].current_vote++]].vote_qty++;    
            ballots[i].available = false;
        }
    }
}

int get_winner(int ballots_qty, int candidates_qty) {
    int maior = 0;
    int i, j;

    for (i = 1; i <= candidates_qty; i++) {
        if (candidates[i].vote_qty > maior) {
            maior = candidates[i].vote_qty;
            j = i;
        }
    }

    if (maior > ballots_qty / 2.)
        return j;
    else
        return NO_WINNER;
}

void print_candidates(int candidates_qty) {
    int i;
    
    for (i = 1; i <= candidates_qty; i++) {
        if (candidates[i].available)
            printf("%s", candidates[i].name);
    }
}

bool all_candidates_tied(int candidate_qty) {
    int vote_qty, i = 0;

    while (!candidates[++i].available);

    vote_qty = candidates[i].vote_qty;

    for (i = 1; i <= candidate_qty; i++) {
        if (candidates[i].available && vote_qty != candidates[i].vote_qty)
            return false;
    }

    return true;
}

bool eliminate_last_tied_candidates(int candidate_qty, int ballots_qty) {
    int min = INFINITE;
    int i, j;

    for (i = 1; i <= candidate_qty; i++) {
        if (candidates[i].vote_qty < min && candidates[i].available) {
            min = candidates[i].vote_qty;
        }
    }

    if (all_candidates_tied(candidate_qty))
        return false;
    
    for (i = 1; i <= candidate_qty; i++) {
        if (candidates[i].vote_qty == min && candidates[i].available) {
            candidates[i].available = false;

            for (j = 0; j < ballots_qty; j++) {
                if (ballots[j].votes[ballots[j].current_vote - 1] == i)
                    ballots[j].available = true;
            }
        }
    }

    return true;
}

int main() {
    int test_case_qty, candidate_qty;
    int i;
    int winner, ballots_qty;

    scanf("%d", &test_case_qty);
    while (test_case_qty-- > 0 && !feof(stdin)) {
        scanf("%d\n", &candidate_qty);

        for (i = 1; i <= candidate_qty; i++) {
            fgets(candidates[i].name, 80, stdin);
            candidates[i].vote_qty = 0;
            candidates[i].available = true;
        }

        char *line = (char *) malloc(sizeof(char) * 101);
        fgets(line, 100, stdin);

        ballots_qty = 0;

        while (strcmp(line, "\n") && !feof(stdin)) {
            for (i = 0; i < candidate_qty; i++) {
                sscanf(line, "%d", &ballots[ballots_qty].votes[i]);

                if (ballots[ballots_qty].votes[i] > 10)
                    line++;

                line += 2;
            }

            ballots_qty++;
            fgets(line, 100, stdin);
        }

        initialize_available(ballots_qty);

        do {
            count_available_votes(ballots_qty, candidate_qty);
            winner = get_winner(ballots_qty, candidate_qty);
        } while (winner == NO_WINNER && eliminate_last_tied_candidates(candidate_qty, ballots_qty));

        if (winner == NO_WINNER) {
            print_candidates(candidate_qty);
        } else {
            printf("%s", candidates[winner].name);
        }
        
        if (test_case_qty > 0)
            printf("\n");
    }

    return EXIT_SUCCESS;
}
