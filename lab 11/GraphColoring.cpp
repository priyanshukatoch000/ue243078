// Graph Coloring: Assigns valid colors to graph vertices. Time Complexity: Exponential (backtracking).
#include <bits/stdc++.h>
using namespace std;

bool isSafe(int v, int c, vector<vector<int>> &graph, vector<int> &color, int n) {
    for (int i = 0; i < n; i++) {
        if (graph[v][i] == 1 && color[i] == c)
            return false;
    }
    return true;
}

void solve(int v, vector<vector<int>> &graph, vector<int> &color, int n, int m) {
    if (v == n) {
        for (int i = 0; i < n; i++)
            cout << color[i] << " ";
        cout << endl;
        return;
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c, graph, color, n)) {
            color[v] = c;
            solve(v + 1, graph, color, n, m);
            color[v] = 0; // backtrack
        }
    }
}

int main() {
    int n = 4;
    int m = 3;

    vector<vector<int>> graph = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    vector<int> color(n, 0);

    solve(0, graph, color, n, m);

    return 0;
}
