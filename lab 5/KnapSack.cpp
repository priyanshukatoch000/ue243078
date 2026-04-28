// 0/1 Knapsack: Maximizes value under capacity using dynamic programming. Time Complexity: O(nW).
#include <bits/stdc++.h>
using namespace std;

double knapSack(vector<vector<int>> &m, int mw) {
    sort(m.begin(), m.end(), [](vector<int> &a, vector<int> &b) {
        return (double)b[0] / b[1] > (double)a[0] / a[1];
    });

    double total = 0.0;

    for (auto &item : m) {
        int value = item[0];
        int weight = item[1];

        if (mw >= weight) {
            total += value;
            mw -= weight;
        } else {
            total += ((double)value / weight) * mw;
            break;
        }
    }

    return total;
}

int main() {
    vector<vector<int>> M = {
        {60, 6},
        {50, 4},
        {20, 10},
        {40, 10},
        {50, 25}
    };

    double p = knapSack(M, 100);

    cout << p;

    return 0;
}
