#include <bits/stdc++.h>
using namespace std;

int bs(vector<int> &arr, int target, int s, int e) {
    if (s > e) return -1;

    int m = s + (e - s) / 3;

    if (arr[m] == target) return m;
    else if (arr[m] < target) return bs(arr, target, m + 1, e);
    else return bs(arr, target, s, m - 1);
}

int main() {
    vector<int> arr = {1,2,3,4,5,6,7,8,9};

    cout << bs(arr, 3, 0, arr.size() - 1);

    return 0;
}