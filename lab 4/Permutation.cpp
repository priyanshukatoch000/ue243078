#include <bits/stdc++.h>
using namespace std;

void swapChar(int i, int j, vector<char> &arr) {
    char t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

void perm(vector<char> &arr, int i) {
    if (i == arr.size()) {
        for (char c : arr) cout << c;
        cout << endl;
        return;
    }

    for (int j = i; j < arr.size(); j++) {
        swapChar(i, j, arr);
        perm(arr, i + 1);
        swapChar(i, j, arr);
    }
}

int main() {
    vector<char> str = {'a','b','c','d'};

    perm(str, 0);

    return 0;
}