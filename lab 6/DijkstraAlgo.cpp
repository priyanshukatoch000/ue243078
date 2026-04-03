#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000;

struct Pair {
    int node, dist;
};

void dijkstra(int s, vector<vector<int>> &g, vector<int> &d, int n) {
    vector<bool> vis(n, false);

    for (int i = 0; i < n; i++) d[i] = INF;

    d[s] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (vis[u]) continue;
        vis[u] = true;

        for (int j = 0; j < n; j++) {
            if (!vis[j] && g[u][j] != INF) {
                if (d[j] > d[u] + g[u][j]) {
                    d[j] = d[u] + g[u][j];
                    pq.push({d[j], j});
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> g = {
        {0,50,45,10,INF,INF},
        {INF,0,10,15,INF,INF},
        {INF,INF,0,INF,30,INF},
        {20,INF,INF,0,15,INF},
        {INF,20,35,INF,0,INF},
        {INF,INF,INF,INF,3,0}
    };

    vector<int> d(g.size());

    dijkstra(0, g, d, g.size());

    for (int x : d) cout << x << " ";

    return 0;
}