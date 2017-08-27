#include <cstdio>
#include <list>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    int coach, train_size, current;
    vector<int> result, expected;
    
    while (scanf("%d", &train_size) && train_size) {
        stack<int> entrance;

        while (scanf("%d", &coach) && coach) {
            result.clear();
            expected.clear();
            stack<int> station;
            
            expected.push_back(coach);
            for (int i = 1; i < train_size; i++) {
                scanf("%d", &coach); 
                expected.push_back(coach);
            }
        
            for (int i = train_size; i > 0; i--) {
                entrance.push(i);
            }
        
            current = 0;
            while (true) {
                if (!station.empty() && expected[current] == station.top()) {
                    result.push_back(station.top());
                    station.pop();
                    current++;
                } else if (!entrance.empty() && expected[current] == entrance.top()) {
                    result.push_back(entrance.top());
                    entrance.pop();
                    current++;
                } else if (entrance.empty()) {
                    break;
                } else {
                    station.push(entrance.top());
                    entrance.pop();
                }
            }

            if (result == expected) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
        printf("\n");
    }
}
