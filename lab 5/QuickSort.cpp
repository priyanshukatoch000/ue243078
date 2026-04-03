#include <bits/stdc++.h>
using namespace std;

void swapIndex(vector<float> &arr, int l, int h) {
    float t = arr[l];
    arr[l] = arr[h];
    arr[h] = t;
}

int partition(vector<float> &arr, int s, int e) {
    int m = s + (e - s) / 2;
    float pivot = arr[m];

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

void qs(vector<float> &arr, int s, int e) {
    if (s < e) {
        int j = partition(arr, s, e);
        qs(arr, s, j - 1);
        qs(arr, j + 1, e);
    }
}