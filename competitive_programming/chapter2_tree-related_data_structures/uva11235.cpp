#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
private:
    static const int OUT_OF_BOUNDS = -1;
    std::vector<int> tree, input, startpos, frequency;
    int size;

    int left(int p) 
    {
        return p << 1;
    }

    int right(int p) 
    {
        return (p << 1) + 1;
    }

    int build(int p, int l, int r) 
    {
        if (l != r) {
            int p1 = build(left(p), l, (l + r) / 2);
            int p2 = build(right(p), (l + r) / 2 + 1, r);

            return tree[p] = max(tree[left(p)], tree[right(p)]);
        } else {
            return tree[p] = frequency[l];
        }
    }

    int query(int p, int l, int r, int i, int j)
    {
        if (i > r || j < l) {
            return OUT_OF_BOUNDS;
        }
        if (l >= i && r <= j) {
            return tree[p];
        }

        int p1 = query(left(p), l, (l + r) / 2, i, j);
        int p2 = query(right(p), (l + r) / 2 + 1, r, i, j);

        if (p1 == OUT_OF_BOUNDS) return p2;
        if (p2 == OUT_OF_BOUNDS) return p1;

        return max(p1, p2);
    }
public:
    SegmentTree(const std::vector<int> &input, const std::vector<int> &startpos, const std::vector<int> &frequency)
    {
        size = input.size();
        this->input = input;
        this->startpos = startpos;
        this->frequency = frequency;
        tree.assign(4 * size, 0);
        build(1, 0, size - 1);
    }

    int query(int i, int j)
    {
        return this->query(1, 0, size - 1, i, j);
    }

    int freq(int i, int j)
    {
        if (input[i] == input[j]) {
            return j - i + 1;
        }

        int result;
        int freq_start = frequency[i] - i + startpos[i];
        int freq_end = j - startpos[j] + 1;
        result = max(freq_start, freq_end);

        int end_i = startpos[i] + frequency[i];
        int start_j = startpos[j] - 1;

        if (end_i <= start_j) 
            result = max(result, this->query(end_i, start_j));
        return result;
    }
};

int main()
{
    int quantity, queries, i, j, previous, last_start;
    while (cin >> quantity >> queries && quantity && queries) {
        vector<int> input(quantity);
        vector<int> start(quantity);
        vector<int> frequency(quantity);

        last_start = 0;
        for (int i = 0; i < quantity; i++) {
            cin >> input[i];
            if (!i || previous != input[i]) {
                for (int j = last_start; j < i; j++) {
                    frequency[j] = i - last_start;
                }
                last_start = i;
            }
            
            start[i] = last_start;
            previous = input[i];
        }
        for (int j = last_start; j < quantity; j++) {
            frequency[j] = quantity - last_start;
        }

        SegmentTree tree(input, start, frequency);
        while (queries--) {
            cin >> i >> j;
            cout << tree.freq(i - 1, j - 1) << endl;
        } 
    }
}
