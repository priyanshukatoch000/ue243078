// Shortest Path Solver: Computes shortest path data for graph input. Time Complexity: Typically O(V^3).
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> m, s;

void matrixChainOrder(vector<int> &p) {
    int n = p.size() - 1;

    m.assign(n + 1, vector<int>(n + 1, 0));
    s.assign(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void printOptimalParens(int i, int j) {
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        printOptimalParens(i, s[i][j]);
        printOptimalParens(s[i][j] + 1, j);
        cout << ")";
    }
}

double timeCalc(vector<int> &p) {
    auto t1 = chrono::high_resolution_clock::now();
    matrixChainOrder(p);
    auto t2 = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(t2 - t1).count();
}

vector<int> generateDimensions(int n) {
    vector<int> p(n + 1);

    for (int i = 0; i <= n; i++) {
        p[i] = rand() % 50 + 1; // avoid 0
    }

    return p;
}

int main() {
    srand(time(0));

    vector<int> sizes = {5, 10, 15, 20, 25, 30, 35, 40};

    for (int n : sizes) {
        double avg = 0;

        for (int i = 0; i < 10; i++) {
            vector<int> p = generateDimensions(n);
            avg += timeCalc(p);
        }

        cout << (avg / 10) << ", ";
    }

    return 0;
}
