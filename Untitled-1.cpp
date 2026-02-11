#include<iostream>
#include<chrono>
#include<cstdlib>
#include<algorithm>


using namespace std;
using namespace std::chrono;

int bsearch(int arr[], int low, int high, int tg) {
    if (low > high) {
        return -1;
    }

    int middle = low + (high - low) / 2;

    if (arr[middle] == tg) {
        return middle;
    } else if (arr[middle] < tg) {
        return bsearch(arr, middle + 1, high, tg);
    } else {
        return bsearch(arr, low, middle - 1, tg);
    }
}

int avgtime(int n) {
    long long total_diff = 0;
    int arr[10000];

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 1000;
        }

        sort(arr, arr + n);   // required for binary search
        int tg = rand() % 1000;

        auto x = high_resolution_clock::now();
        bsearch(arr, 0, n - 1, tg);
        auto y = high_resolution_clock::now();

        total_diff += duration_cast<nanoseconds>(y - x).count();
    }

    return total_diff / 100;
}

int main() {
    for (int i = 1000; i < 10000; i += 1000) {
        int time = avgtime(i);
        cout << "for " << i << " elements the time is " 
             << time << " ns" << endl;
    }
    return 0;
}
