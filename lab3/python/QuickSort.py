# Quick Sort: Sorts by partitioning around a pivot recursively.
# Time Complexity: O(n log n) average, O(n^2) worst


def swap(arr, left, right):
    arr[left], arr[right] = arr[right], arr[left]


def partition(arr, start, end):
    mid = start + (end - start) // 2
    pivot = arr[mid]

    index = start
    for i in range(start, end + 1):
        if arr[i] < pivot:
            index += 1

    swap(arr, mid, index)

    left, right = start, end
    while left < index and right > index:
        while arr[left] < pivot:
            left += 1
        while arr[right] > pivot:
            right -= 1

        if left < index and right > index:
            swap(arr, left, right)
            left += 1
            right -= 1

    return index


def quick_sort(arr, start=0, end=None):
    if end is None:
        end = len(arr) - 1

    if start < end:
        pivot_index = partition(arr, start, end)
        quick_sort(arr, start, pivot_index - 1)
        quick_sort(arr, pivot_index + 1, end)


def solve():
    arr = [29, 10, 14, 37, 13, 5, 18]
    print(f"Original array: {arr}")
    quick_sort(arr)
    print(f"Sorted array:   {arr}")


if __name__ == "__main__":
    solve()
