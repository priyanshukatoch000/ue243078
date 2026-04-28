#include <bits/stdc++.h>
using namespace std;

const int INF = 10000000;
vector<set<int>> s;

void findStage(vector<vector<int>> &g) {
    s.clear();
    int n = g.size();
    vector<bool> visited(n, false);

    set<int> t;
    t.insert(0);
    visited[0] = true;
    s.push_back(t);

    int i = 0;

    while (i < s.size()) {
        set<int> st;
        for (int e : s[i]) {
            for (int j = 0; j < n; j++) {
                if (g[e][j] != 0 && g[e][j] != INF && !visited[j]) {
                    st.insert(j);
                    visited[j] = true;
                }
            }
        }
        if (!st.empty()) s.push_back(st);
        i++;
    }

    cout << "Number of stages = " << s.size() << endl;
}

int main() {
    int n, m;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m;

    vector<vector<int>> g(n, vector<int>(n));

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) g[i][j] = 0;
            else g[i][j] = INF;
        }
    }


    int k = 0;
    while (k < m) {
        cout << "Edge " << (k + 1) << " (from to weight): ";
        int u, v, w;
        cin >> u >> v >> w;

        if (u < 1 || u > n || v < 1 || v > n) {
            cout << "Vertex numbers must be between 1 and " << n << ". Try again." << endl;
            continue;
        }

        g[u - 1][v - 1] = w;
        k++;
    }

    findStage(g);

    for (auto &st : s) {
        cout << "{ ";
        for (int x : st) cout << x << " ";
        cout << "}" << endl;
    }

    return 0;
}