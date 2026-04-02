#include <bits/stdc++.h>
using namespace std;

void swapIndex(vector<int> &arr, int i, int j) {
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

int minIndex(vector<int> &arr, int i) {
    int m = i;
    for (int j = i; j < arr.size(); j++) {
        if (arr[m] > arr[j]) m = j;
    }
    return m;
}

void ss(vector<int> &arr, int i) {
    if (i == arr.size()) return;

    int idx = minIndex(arr, i);
    swapIndex(arr, idx, i);

    ss(arr, i + 1);
}

double getTime(vector<int> arr) {
    auto t1 = chrono::high_resolution_clock::now();

    ss(arr, 0);

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

    return 0;
}