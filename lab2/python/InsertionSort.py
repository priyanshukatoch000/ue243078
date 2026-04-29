# Insertion Sort: Builds a sorted array one element at a time.
# Time Complexity: O(n^2) average/worst, O(n) best


def insertion_sort(arr):
    """Sort the list in place using insertion sort."""
    for i in range(1, len(arr)):
        temp = arr[i]
        j = i - 1

        while j >= 0 and arr[j] > temp:
            arr[j + 1] = arr[j]
            j -= 1

        arr[j + 1] = temp


def solve():
    arr = [9, 4, 7, 1, 3, 6]
    print(f"Original array: {arr}")
    insertion_sort(arr)
    print(f"Sorted array:   {arr}")


if __name__ == "__main__":
    solve()
