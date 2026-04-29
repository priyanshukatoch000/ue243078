# Merge Sort: Divides array, sorts halves, and merges them.
# Time Complexity: O(n log n)


def merge(arr, start, mid, end):
    i, j = start, mid
    merged = []

    while i < mid and j < end:
        if arr[i] < arr[j]:
            merged.append(arr[i])
            i += 1
        else:
            merged.append(arr[j])
            j += 1

    while i < mid:
        merged.append(arr[i])
        i += 1

    while j < end:
        merged.append(arr[j])
        j += 1

    for offset, value in enumerate(merged):
        arr[start + offset] = value


def merge_sort(arr, start=0, end=None):
    if end is None:
        end = len(arr)

    if end - start <= 1:
        return

    mid = start + (end - start) // 2
    merge_sort(arr, start, mid)
    merge_sort(arr, mid, end)
    merge(arr, start, mid, end)


def solve():
    arr = [38, 27, 43, 3, 9, 82, 10]
    print(f"Original array: {arr}")
    merge_sort(arr)
    print(f"Sorted array:   {arr}")


if __name__ == "__main__":
    solve()
