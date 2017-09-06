#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    bool consumed;
    char input[1001];
    int len, c = 0;
    vector<stack<char>> stacks;

    while (scanf("%s", input) && strcmp("end", input)) {
        stacks.clear();
        len = strlen(input);

        for (int i = 0; i < len; i++) {
            consumed = false;
            for (int j = 0; j < stacks.size(); j++) {
                if (input[i] <= stacks[j].top()) {
                    stacks[j].push(input[i]);
                    consumed = true;
                    break;
                }
            }

            if (!consumed) {
                stack<char> n;
                n.push(input[i]);
                stacks.push_back(n);
            }
        }

        printf("Case %d: %d\n", ++c, stacks.size());
    }
}
