// Power x^n: Computes x raised to n using fast exponentiation. Time Complexity: O(log n).
#include <bits/stdc++.h>
using namespace std;

int powerRec(int x, int n) {
    if (n == 0) return 1;
    if (n < 0) return powerRec(1 / x, -n);

    int half = powerRec(x, n / 2);

    if (n % 2 == 0) return half * half;
    else return half * half * x;
}

int powerRec2(int x, int n) {
    if (n == 0) return 1;
    if (n < 0) return powerRec(1 / x, -n);

    return x * powerRec2(x, n - 1);
}

int main() {
    cout << powerRec(4, 5) << endl;
    cout << powerRec2(4, 5);

    return 0;
}
