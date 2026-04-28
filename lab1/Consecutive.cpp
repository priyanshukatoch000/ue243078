// Consecutive Element Check: Checks whether array elements form a consecutive sequence. Time Complexity: O(n log n) with sorting.
#include <bits/stdc++.h>
using namespace std;

int findMis(vector<int> &nums) {
    int prev = nums[0];

    for (int i = 1; i < nums.size(); i++) {
        if ((prev & 1) == (nums[i] & 1)) {
            if ((prev & 1) == 0) {
                return prev | 1;
            } else {
                return nums[i] & ~1;
            }
        }
        prev = nums[i];
    }

    return -1;
}

int main() {
    vector<int> nums = {0,1,2,3,4,5,7};

    int mis = findMis(nums);

    cout << "The duplicate number is: " << mis;

    return 0;
}
