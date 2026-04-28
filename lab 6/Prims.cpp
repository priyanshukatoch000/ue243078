// Prim's Algorithm: Builds minimum spanning tree by greedy expansion. Time Complexity: O((V+E) log V) with heap.
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000;

int prims(vector<vector<int>> &cost, int n) {
    vector<int> near(n);
    vector<vector<int>> t(n - 1, vector<int>(2));
    int mincost = 0;

    int mn = INF, k = 0, l = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (cost[i][j] < mn) {
                mn = cost[i][j];
                +
                k = i;
                l = j;
            }
        }
    }
""
    t[0][0] = k;
    t[0][1] = l;
    mincost = cost[k][l];

    for (int i = 0; i < n; i++) {
        if (cost[i][l] < cost[i][k]) near[i] = l;
        else near[i] = k;
    }

    near[k] = near[l] = 0;

    for (int i = 1; i < n - 1; i++) {
        int minVal = INF, j = -1;

        for (int v = 0; v < n; v++) {
            if (near[v] != 0 && cost[v][near[v]] < minVal) {
                minVal = cost[v][near[v]];
                j = v;
            }
        }

        if (j == -1) {
            cout << "Graph is disconnected";
            return -1;
        }

        t[i][0] = j;
        t[i][1] = near[j];
        mincost += cost[j][near[j]];

        near[j] = 0;

        for (int v = 0; v < n; v++) {
            if (near[v] != 0 && cost[v][near[v]] > cost[v][j]) {
                near[v] = j;
            }
        }
    }

    cout << "Edges in MST:" << endl;
    for (int i = 0; i < n - 1; i++) {
        cout << t[i][0] << " - " << t[i][1] << endl;
    }

    return mincost;
}

int main() {
    vector<vector<int>> g = {
        {INF, 2, INF, 6, INF},
        {2, INF, 3, 8, 5},
        {INF, 3, INF, INF, 7},
        {6, 8, INF, INF, 9},
        {INF, 5, 7, 9, INF}
    };

    int cost = prims(g, g.size());

    cout << "MST Cost: " << cost;

    return 0;
}
