// Duplicate Detection: Detects duplicate elements in a list/array. Time Complexity: O(n) with hashing.
#include <bits/stdc++.h>
using namespace std;

int dup(vector<int> &arr) {
    int d = -1;
    int index = arr.size();

    for (int i = 0; i < index; i++) {
        for (int j = i + 1; j < index; j++) {
            if (arr[i] == arr[j]) {
                d = arr[i];
                index = j;
                break;
            }
        }
    }
    return d;
}

int dup2(vector<int> &arr) {
    int d = -1;
    int n = arr.size() / 2;

    for (int i = 0; i < n; i++) {
        int t = arr[n - i];
        for (int j = 0; j < n - i; j++) {
            if (t == arr[j]) {
                d = t;
                break;
            }
        }
    }
    return d;
}

int main() {
    vector<int> arr = {1,2,3,1,3,1,3,4,4};

    cout << dup(arr) << endl;
    cout << dup2(arr);

    return 0;
}
