#include <bits/stdc++.h>
using namespace std;

string HR(int i, vector<int> &arr) {
    if (i == arr.size() - 1) return to_string(arr[i]);
    return to_string(arr[i]) + " + x(" + HR(i + 1, arr) + ")";
}

int main() {
    vector<int> arr = {1,2,3,4,5};

    cout << HR(0, arr);

    return 0;
}