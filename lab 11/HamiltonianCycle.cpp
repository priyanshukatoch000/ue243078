// Hamiltonian Cycle: Finds cycle visiting each vertex once. Time Complexity: Exponential (backtracking).
#include <bits/stdc++.h>
using namespace std;

void nextValue(int k, vector<vector<int>> &graph, vector<int> &x, int n) {
    while (true) {
        x[k] = (x[k] + 1) % n;

        if (x[k] == 0) return;

        // Check if edge exists
        if (graph[x[k - 1]][x[k]] == 1) {
            int j;
            for (j = 0; j < k; j++) {
                if (x[j] == x[k]) break;
            }

            // If not already included
            if (j == k) {
                // If not last vertex OR last vertex connects to first
                if (k < n - 1 || (k == n - 1 && graph[x[k]][x[0]] == 1)) {
                    return;
                }
            }
        }
    }
}

void hamiltonian(int k, vector<vector<int>> &graph, vector<int> &x, int n) {
    while (true) {
        nextValue(k, graph, x, n);

        if (x[k] == 0) return;

        if (k == n - 1) {
            for (int i = 0; i < n; i++)
                cout << x[i] << " ";
            cout << x[0] << endl; // complete cycle
        } else {
            hamiltonian(k + 1, graph, x, n);
        }
    }
}

int main() {
    int n = 5;

    vector<vector<int>> graph = {
        {0,1,0,1,0},
        {1,0,1,1,1},
        {0,1,0,0,1},
        {1,1,0,0,1},
        {0,1,1,1,0}
    };

    vector<int> x(n, 0);
    x[0] = 0;

    hamiltonian(1, graph, x, n);

    return 0;
}
