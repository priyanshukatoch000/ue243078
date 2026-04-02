#include <bits/stdc++.h>
using namespace std;

void swapIndex(vector<int> &arr, int l, int h) {
    int t = arr[l];
    arr[l] = arr[h];
    arr[h] = t;
}

int partition(vector<int> &arr, int s, int e) {
    int m = s + (e - s) / 2;
    int pivot = arr[m];

    int index = s;
    for (int i = s; i <= e; i++) {
        if (arr[i] < pivot) index++;
    }

    swapIndex(arr, m, index);

    int l = s, h = e;

    while (l < index && h > index) {
        while (arr[l] < pivot) l++;
        while (arr[h] > pivot) h--;

        if (l < index && h > index) {
            swapIndex(arr, l, h);
            l++;
            h--;
        }
    }

    return index;
}

void qs(vector<int> &arr, int s, int e) {
    if (s < e) {
        int j = partition(arr, s, e);
        qs(arr, s, j - 1);
        qs(arr, j + 1, e);
    }
}

double getTime(vector<int> arr) {
    auto t1 = chrono::high_resolution_clock::now();

    qs(arr, 0, arr.size() - 1);

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

        sort(arr.begin(), arr.end());

        for (int i = 0; i < 1000; i++) {
            avg += getTime(arr);
        }

        cout << avg / 1000 << ",";
    }

    return 0;
}