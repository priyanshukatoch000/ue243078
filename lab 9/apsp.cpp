#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000;

void floydWarshall(vector<vector<int>> &cost, vector<vector<int>> &A, int n) {
  
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = cost[i][j];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                }
            }
        }
    }
}

double timeCalc(vector<vector<int>> &graph) {
    int n = graph.size();
    vector<vector<int>> A(n, vector<int>(n));

    auto t1 = chrono::high_resolution_clock::now();
    floydWarshall(graph, A, n);
    auto t2 = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(t2 - t1).count();
}

vector<vector<int>> generateGraph(int n) {
    vector<vector<int>> g(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) g[i][j] = 0;
            else {
                double prob = (double)rand() / RAND_MAX;
                if (prob < 0.4)
                    g[i][j] = rand() % 50 + 1;
                else
                    g[i][j] = INF;
            }
        }
    }
    return g;
}

int main() {
    srand(time(0));

    vector<int> sizes = {5, 10, 20, 50, 100};

    for (int n : sizes) {
        double avg = 0;
        vector<vector<int>> graph = generateGraph(n);

        for (int i = 0; i < 5; i++) {
            avg += timeCalc(graph);
        }

        cout << (avg / 5) << ", ";
    }

    return 0;
}