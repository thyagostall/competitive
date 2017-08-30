#include <cstdio>

#define SIZE 102

char mine[SIZE][SIZE];
char result[SIZE][SIZE];

void clear() {
	int i, j;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			mine[i][j] = ' ';
			result[i][j] = '0';
		}
	}
}

int count_adjacents(int x, int y) {
	int i, j;
	int result = 0;

	for (i = x - 1; i <= x + 1; i++) {
		for (j = y - 1; j <= y + 1; j++) {
			if (x == i && y == j) {
				continue;
			}
			
			if (mine[i][j] == '*') {
				result++;
			}
		}
	}
	
	return result;
}

void read_mine(int max_i, int max_j) {
	int i, j;

	for (i = 1; i <= max_i; i++) {
		for (j = 1; j <= max_j; j++) {
			while (mine[i][j] != '.' && mine[i][j] != '*') {
				scanf("%c", &mine[i][j]);
			}
		}
	}
}

void compute_result(int max_i, int max_j) {
	int i, j;

	for (i = 1; i <= max_i; i++) {
		for (j = 1; j <= max_j; j++) {
			if (mine[i][j] == '*') {
				result[i][j] = '*';
			}
		}
	}	

	for (i = 1; i <= max_i; i++) {
		for (j = 1; j <= max_j; j++) {
			if (result[i][j] != '*') {
				result[i][j] = result[i][j] + count_adjacents(i, j);
			}			
		}
	}	
}

void print_result(int field, int max_i, int max_j) {
	int i, j;

	if (field != 1) {
		printf("\n");
	}
	
	printf("Field #%d:\n", field);

	for (i = 1; i <= max_i; i++) {
		for (j = 1; j <= max_j; j++) {
			printf("%c", result[i][j]);
		}
		
		printf("\n");
	}	
}

int main() {
	int max_i = -1;
	int max_j = -1;
	int field = 0;
	
	while (1) {
		clear();
		scanf("%d %d", &max_i, &max_j);	
		
		if (!max_i) {
			break;
		}

		read_mine(max_i, max_j);
		compute_result(max_i, max_j);
		print_result(++field, max_i, max_j);
	}
}
