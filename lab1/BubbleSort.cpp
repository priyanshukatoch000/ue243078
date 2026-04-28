// Bubble Sort: Sorts elements by repeatedly swapping adjacent out-of-order pairs. Time Complexity: O(n^2) average/worst, O(n) best.
#include <bits/stdc++.h>
using namespace std;

void swapIndex(vector<int> &a, int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void bb(vector<int> &a, int i) {
    if (i >= a.size()) return;

    for (int j = 1; j < a.size() - i + 1; j++) {
        if (a[j - 1] > a[j]) swapIndex(a, j, j - 1);
    }

    bb(a, i + 1);
}

double getTime(vector<int> a) {
    auto t1 = chrono::high_resolution_clock::now();

    bb(a, 1);

    auto t2 = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(t2 - t1).count();
}

int main() {
    srand(time(0));

    vector<int> values = {10,100,1000,2000,5000,10000,12500,15000,17500,20000,22500};

    for (int n : values) {
        double avg = 0;
        vector<int> arr(n);

        for (int i = 0; i < n; i++) arr[i] = rand();

        sort(arr.begin(), arr.end());

        for (int i = 0; i < 1000; i++) {
            avg += getTime(arr);
        }

        cout << avg / 1000 << ",";
    }
}
