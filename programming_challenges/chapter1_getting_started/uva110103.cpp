#include <cstdio>

#define SIZE 1000 

void get_values(int);
double compute(int); 

double values[SIZE];

int main() {
	int student_quantity;

	while (scanf("%d", &student_quantity) != EOF) {
		if (!student_quantity) {
			break;
		}

		get_values(student_quantity);
		printf("$%.2lf\n", compute(student_quantity));
	}

	return 0;
}

void get_values(int qtd) {
	int i;

	for (i = 0; i < qtd; i++) {
		scanf("%lf\n", &values[i]);
	}
}

double compute(int qtd) {
	double sum_p = 0, sum_n = 0, sum = 0;
	double avg;
	double diff;
	int i;

	for (i = 0; i < qtd; i++) {
		sum += values[i];
	}

	avg = sum / qtd;

	for (i = 0; i < qtd; i++) {
		diff = (int) ((avg - values[i]) * 100) / 100.0;

		if (diff < 0) {
			sum_n -= diff;
		} else {
			sum_p += diff;
		}
	}

	if (sum_p > sum_n) {
		return sum_p;
	} else {
		return sum_n;
	}
}
