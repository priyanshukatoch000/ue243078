#include <bits/stdc++.h>
using namespace std;

struct Pair {
    int first, second;
};

void swapVal(vector<int> &arr, int l, int h) {
    int t = arr[l];
    arr[l] = arr[h];
    arr[h] = t;
}

void qsi(vector<int> &arr) {
    stack<Pair> s;
    s.push({0, (int)arr.size()});

    while (!s.empty()) {
        Pair p = s.top();
        s.pop();

        int i = p.first;
        int j = p.second;

        if (i >= j) continue;

        int pivot = arr[i];

        do {
            do { i++; } while (i < arr.size() && arr[i] < pivot);
            do { j--; } while (j >= 0 && arr[j] > pivot);

            if (i < j) swapVal(arr, i, j);
            else swapVal(arr, p.first, j);

        } while (i < j);

        if (j - p.first + 1 > p.second - (j + 1)) {
            s.push({p.first, j});
            s.push({j + 1, p.second});
        } else {
            s.push({j + 1, p.second});
            s.push({p.first, j - 1});
        }
    }
}

int main() {
    vector<int> arr(100000);

    for (int i = 0; i < arr.size(); i++) arr[i] = i;

    qsi(arr);

    for (int x : arr) cout << x << " ";

    return 0;
}