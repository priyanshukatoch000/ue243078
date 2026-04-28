// Kruskal's Algorithm: Builds minimum spanning tree via sorted edges and DSU. Time Complexity: O(E log E).
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

vector<int> parent;

int findP(int x) {
    if (parent[x] < 0) return x;
    return parent[x] = findP(parent[x]);
}

void unite(int x, int y) {
    int px = findP(x);
    int py = findP(y);

    if (px == py) return;

    if (parent[px] < parent[py]) {
        parent[px] += parent[py];
        parent[py] = px;
    } else {
        parent[py] += parent[px];
        parent[px] = py;
    }
}

int kruskal(int n, vector<Edge> &edges) {
    sort(edges.begin(), edges.end(), [](Edge &a, Edge &b) {
        return a.w < b.w;
    });

    parent.assign(n, -1);

    int mincost = 0, count = 0;

    for (auto &e : edges) {
        int u = e.u, v = e.v;

        if (findP(u) != findP(v)) {
            unite(u, v);
            mincost += e.w;
            count++;

            cout << u << " - " << v << endl;

            if (count == n - 1) break;
        }
    }

    if (count != n - 1) {
        cout << "No Spanning Tree";
        return -1;
    }

    return mincost;
}

int main() {
    int n = 5;

    vector<Edge> edges = {
        {0,1,2},
        {0,3,6},
        {1,2,3},
        {1,3,8},
        {1,4,5},
        {2,4,7},
        {3,4,9}
    };

    int cost = kruskal(n, edges);

    cout << "MST Cost: " << cost;

    return 0;
}
