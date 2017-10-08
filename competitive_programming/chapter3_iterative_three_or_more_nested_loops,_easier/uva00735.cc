#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int create_unordered(int a, int b, int c)
{
    return c + b * 100 + a * 10000;
}

int create_ordered(int a, int b, int c, vector<int> &input)
{
    input[0] = a;
    input[1] = b;
    input[2] = c;
    sort(input.begin(), input.end());
    return create_unordered(input[0], input[1], input[2]);
}

int main()
{
    int score, sum;
    vector<int> points, temp;
    
    temp.assign(3, 0);
    points.push_back(0);
    for (int i = 1; i <= 20; i++) {
        points.push_back(i);
        points.push_back(i * 2);
        points.push_back(i * 3);
    }
    points.push_back(50);

    while (cin >> score && score > 0) {
        unordered_set<int> permutations, combinations;

        for (int i = 0; i <= points.size(); i++) {
            for (int j = 0; j <= points.size(); j++) {
                for (int k = 0; k <= points.size(); k++) {
                    sum = points[i] + points[j] + points[k];
                        
                    if (sum == score) {
                        int unordered = create_unordered(points[i], points[j], points[k]);
                        int ordered = create_ordered(points[i], points[j], points[k], temp);

                        permutations.insert(unordered);
                        combinations.insert(ordered);
                    }
                }
            }
        }

        if (permutations.size()) {
            cout << "NUMBER OF COMBINATIONS THAT SCORES " << score << " IS " << combinations.size() << "." << endl;
            cout << "NUMBER OF PERMUTATIONS THAT SCORES " << score << " IS " << permutations.size() << "." << endl;
        } else {
            cout << "THE SCORE OF " << score << " CANNOT BE MADE WITH THREE DARTS." << endl;
        }
        cout << "**********************************************************************" << endl;
    }
    cout << "END OF OUTPUT" << endl;
}
