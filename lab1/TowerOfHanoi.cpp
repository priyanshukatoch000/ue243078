// Tower of Hanoi: Moves disks between rods with recursive constraints. Time Complexity: O(2^n).
#include <bits/stdc++.h>
using namespace std;

void TOH(int n, int src, int dest, int ex) {
    if (n == 1) {
        cout << "Move disk from " << src << " to " << dest << endl;
        return;
    }

    TOH(n - 1, src, ex, dest);
    cout << "Move disk from " << src << " to " << dest << endl;
    TOH(n - 1, ex, dest, src);
}

int main() {
    int n;
    cout << "Enter number of Disc = ";
    cin >> n;

    TOH(n, 1, 3, 2);

    return 0;
}
