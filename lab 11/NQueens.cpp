#include <bits/stdc++.h>
using namespace std;

int solutions;

bool isSafe(int k, int i, vector<int> &x) {
    for (int j = 0; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k)) {
            return false;
        }
    }
    return true;
}

void solve(int k, vector<int> &x, int n) {
    if (k == n) {
        solutions++;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (isSafe(k, i, x)) {
            x[k] = i;
            solve(k + 1, x, n);
        }
    }
}

double timeCalc(int n) {
    vector<int> x(n, 0);
    solutions = 0;

    auto t1 = chrono::high_resolution_clock::now();
    solve(0, x, n);
    auto t2 = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(t2 - t1).count();
}

int main() {
    vector<int> sizes = {4, 5, 6, 7, 8, 9, 10};

    for (int n : sizes) {
        double avg = 0;

        for (int i = 0; i < 5; i++) {
            avg += timeCalc(n);
        }

        cout << (avg / 5) << ",";
    }

    return 0;
}