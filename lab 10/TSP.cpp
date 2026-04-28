// Traveling Salesman Problem: Finds minimum Hamiltonian tour cost. Time Complexity: Exponential / O(n^2*2^n) for DP.
#include <bits/stdc++.h>
using namespace std;

class TSP {
public:

    // 🔹 BACKTRACKING APPROACH
    class Backtracking {
    public:
        int DFS(vector<bool> &vis, vector<vector<int>> &cost, int curr, int count) {
            int n = cost.size();

            if (count == n)
                return cost[curr][0];

            int mn = INT_MAX;

            for (int i = 1; i < n; i++) {
                if (!vis[i]) {
                    vis[i] = true;
                    mn = min(mn, cost[curr][i] + DFS(vis, cost, i, count + 1));
                    vis[i] = false;
                }
            }
            return mn;
        }

        int tsp(vector<vector<int>> &cost) {
            int n = cost.size();
            vector<bool> vis(n, false);
            vis[0] = true;
            return DFS(vis, cost, 0, 1);
        }
    };

    // 🔹 DP (BITMASKING APPROACH)
    class DP {
    public:
        static const int INF = INT_MAX;

        int tsp(int n, vector<vector<int>> &cost) {
            int VISITED_ALL = 1 << n;

            vector<vector<int>> dp(VISITED_ALL, vector<int>(n, INF));

            dp[1][0] = 0; // start from city 0

            for (int mask = 1; mask < VISITED_ALL; mask++) {
                for (int u = 0; u < n; u++) {

                    if (!(mask & (1 << u))) continue;

                    for (int v = 0; v < n; v++) {

                        if (mask & (1 << v)) continue;

                        int newMask = mask | (1 << v);

                        dp[newMask][v] = min(
                            dp[newMask][v],
                            dp[mask][u] + cost[u][v]
                        );
                    }
                }
            }

            int ans = INF;

            for (int i = 0; i < n; i++) {
                ans = min(ans, dp[VISITED_ALL - 1][i] + cost[i][0]);
            }

            return ans;
        }
    };
};

int main() {
    int n = 4;

    vector<vector<int>> cost = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    TSP::Backtracking bt;
    TSP::DP dp;

    cout << "Backtracking Cost: " << bt.tsp(cost) << endl;
    cout << "DP Cost: " << dp.tsp(n, cost) << endl;

    return 0;
}
