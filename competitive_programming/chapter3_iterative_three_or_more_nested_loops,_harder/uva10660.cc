#include <iostream>
#include <limits>

#define MAX 25
#define CITY_LENGTH 5

using namespace std;

int dist(int seq, int i, int j)
{
    int x = seq / CITY_LENGTH;
    int y = seq % CITY_LENGTH;

    return abs(x - i) + abs(y - j);
}

int main()
{
    int city[CITY_LENGTH][CITY_LENGTH];
    int min_places[CITY_LENGTH];
    int test_cases, population, regions, x, y, min_value, sum, temp;

    cin >> test_cases;
    while (test_cases--) {
        for (int p = 0; p < CITY_LENGTH; p++) {
            for (int q = 0; q < CITY_LENGTH; q++) {
                city[p][q] = 0;
            }
        }

        cin >> regions;
        while (regions--) {
            cin >> x >> y >> population;
            city[x][y] = population;
        }

        min_value = numeric_limits<int>::max();
        for (int i = 0; i < MAX; i++) {
            for (int j = i + 1; j < MAX; j++) {
                for (int k = j + 1; k < MAX; k++) {
                    for (int l = k + 1; l < MAX; l++) {
                        for (int m = l + 1; m < MAX; m++) {
                            sum = 0;
                            for (int p = 0; p < CITY_LENGTH; p++) {
                                for (int q = 0; q < CITY_LENGTH; q++) {
                                    if (!city[p][q]) continue;

                                    temp = dist(i, p, q);
                                    temp = min(temp, dist(j, p, q));
                                    temp = min(temp, dist(k, p, q));
                                    temp = min(temp, dist(l, p, q));
                                    temp = min(temp, dist(m, p, q));
                                    sum += temp * city[p][q];
                                }
                            }
                            if (sum < min_value) {
                                min_value = sum;
                                min_places[0] = i;
                                min_places[1] = j;
                                min_places[2] = k;
                                min_places[3] = l;
                                min_places[4] = m;
                            }
                        }
                    }
                }
            }
        }
        cout << min_places[0] << " " 
             << min_places[1] << " "
             << min_places[2] << " "
             << min_places[3] << " "
             << min_places[4] << endl;
    }
}
