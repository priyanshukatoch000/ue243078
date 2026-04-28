// Velocity Computation: Computes velocity from input values. Time Complexity: O(1).
#include <bits/stdc++.h>
using namespace std;

int tips(double v, int t) {
    if (v >= 1) {
        t++;
        v = v - (0.425 * v);
        return tips(v, t);
    }
    return t;
}

int main() {
    cout << tips(40, 0);
    return 0;
}
