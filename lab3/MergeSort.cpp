// Merge Sort: Divides array, sorts halves, and merges them. Time Complexity: O(n log n).
#include <bits/stdc++.h>
using namespace std;

void mergeS(vector<int> &arr, int s, int m, int e) {
    int i = s, j = m, k = 0;
    vector<int> mix(e - s);

    while (i < m && j < e) {
        if (arr[i] < arr[j]) mix[k++] = arr[i++];
        else mix[k++] = arr[j++];
    }

    while (i < m) mix[k++] = arr[i++];
    while (j < e) mix[k++] = arr[j++];

    for (int l = 0; l < mix.size(); l++) {
        arr[s + l] = mix[l];
    }
}

void ms(vector<int> &arr, int s, int e) {
    if (e - s <= 1) return;

    int m = s + (e - s) / 2;

    ms(arr, s, m);
    ms(arr, m, e);

    mergeS(arr, s, m, e);
}

double getTime(vector<int> arr) {
    auto t1 = chrono::high_resolution_clock::now();

    ms(arr, 0, arr.size());

    auto t2 = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(t2 - t1).count();
}

int main() {
    srand(time(0));

    vector<int> values = {10,100,1000,5000,10000,15000,20000,25000,30000,35000,40000,45000,50000};

    for (int n : values) {
        double avg = 0;
        vector<int> arr(n);

        for (int i = 0; i < n; i++) arr[i] = rand();

        for (int i = 0; i < 1000; i++) {
            avg += getTime(arr);
        }

        cout << avg / 1000 << ",";
    }

    return 0;
}
