#include <bits/stdc++.h>
using namespace std;

int countSol;

void sumOfSubsets(int s, int k, int r, vector<int> &w, vector<int> &x, int n, int W) {
    if (k < n) {
        x[k] = 1;

        if (s + w[k] == W) {
            countSol++;
        }
        else if (k + 1 < n && s + w[k] + w[k + 1] <= W) {
            sumOfSubsets(s + w[k], k + 1, r - w[k], w, x, n, W);
        }

        if (k + 1 < n && s + r - w[k] >= W && s + w[k + 1] <= W) {
            x[k] = 0;
            sumOfSubsets(s, k + 1, r - w[k], w, x, n, W);
        }
    }
}

double timeCalc(vector<int> &w, int W) {
    int n = w.size();
    vector<int> x(n, 0);
    countSol = 0;

    int r = 0;
    for (int val : w) r += val;

    auto t1 = chrono::high_resolution_clock::now();
    sumOfSubsets(0, 0, r, w, x, n, W);
    auto t2 = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(t2 - t1).count();
}

vector<int> generateSet(int n) {
    vector<int> w(n);

    for (int i = 0; i < n; i++) {
        w[i] = rand() % 10 + 1;
    }

    sort(w.begin(), w.end());
    return w;
}

int main() {
    srand(time(0));

    vector<int> sizes = {4, 6, 8, 10, 12, 14};

    for (int n : sizes) {
        double avg = 0;

        // warm-up
        for (int i = 0; i < 3; i++) {
            vector<int> w = generateSet(n);
            timeCalc(w, 20);
        }

        for (int i = 0; i < 5; i++) {
            vector<int> w = generateSet(n);
            avg += timeCalc(w, 20);
        }

        cout << (avg / 5) << ", ";
    }

    return 0;
}