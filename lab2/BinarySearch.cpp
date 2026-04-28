// Binary Search: Finds an element in sorted data by halving search space. Time Complexity: O(log n).
#include <bits/stdc++.h>
using namespace std;

int BS(vector<int> &arr, int t, int s, int e) {
    if (e < s) return -1;

    int m = s + (e - s) / 2;

    if (arr[m] == t) return m;
    else if (arr[m] < t) return BS(arr, t, m + 1, e);
    else return BS(arr, t, s, m - 1);
}

double getTime(vector<int> arr, int t) {
    auto t1 = chrono::high_resolution_clock::now();

    BS(arr, t, 0, arr.size() - 1);

    auto t2 = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(t2 - t1).count();
}

int main() {
    srand(time(0));

    vector<int> values = {10,100,1000,10000,100000,1000000,10000000};

    for (int n : values) {
        double avg = 0;
        vector<int> arr(n);

        for (int i = 0; i < n; i++) arr[i] = rand();

        sort(arr.begin(), arr.end());

        for (int i = 0; i < 1000; i++) {
            avg += getTime(arr, rand());
        }

        cout << avg / 1000 << ",";
    }

    return 0;
}
