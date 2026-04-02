#include <bits/stdc++.h>
using namespace std;

void IS(vector<int> &arr) {
    for (int i = 1; i < arr.size(); i++) {
        int t = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > t) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = t;
    }
}

double getTime(vector<int> arr) {
    auto t1 = chrono::high_resolution_clock::now();

    IS(arr);

    auto t2 = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(t2 - t1).count();
}

int main() {
    srand(time(0));

    double avg = 0;
    int n = 22500;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = rand();

    getTime(arr);

    for (int i = 0; i < 1000; i++) {
        avg += getTime(arr);
    }

    cout << "Time taken = " << avg / 1000 << " ms for n = " << n;

    return 0;
}