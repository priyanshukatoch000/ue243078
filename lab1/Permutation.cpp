#include <bits/stdc++.h>
using namespace std;

void swapChar(int i, int j, vector<char> &str) {
    char t = str[i];
    str[i] = str[j];
    str[j] = t;
}

void perm(vector<char> &str, int i) {
    if (i == str.size()) {
        for (char c : str) cout << c;
        cout << endl;
        return;
    }

    for (int j = i; j < str.size(); j++) {
        swapChar(i, j, str);
        perm(str, i + 1);
        swapChar(i, j, str);
    }
}

int main() {
    vector<char> str = {'a','b','c','d'};

    perm(str, 0);

    return 0;
}