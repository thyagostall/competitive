#include <cstdio>
#include <bitset>

#define N 32

using namespace std;

int main()
{
    int n, count;
    while (scanf("%d", &n) && n) {
        bitset<N> even, odd, source(n);
        count = 0;
        for (int i = 0; i < source.size(); i++) {
            if (source.test(i)) count++;
            if (count % 2) {
                odd[i] = source[i];
            } else {
                even[i] = source[i];
            }
        } 

        printf("%lu %lu\n", odd.to_ulong(), even.to_ulong());
    }
}
