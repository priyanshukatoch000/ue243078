# Binary Search: Finds an element in sorted data by halving search space.
# Time Complexity: O(log n)


def binary_search(arr, target, start=0, end=None):
    """Return the index of target in sorted arr, or -1 if it is absent."""
    if end is None:
        end = len(arr) - 1

    if end < start:
        return -1

    mid = start + (end - start) // 2
    if arr[mid] == target:
        return mid
    if arr[mid] < target:
        return binary_search(arr, target, mid + 1, end)
    return binary_search(arr, target, start, mid - 1)


def solve():
    arr = [3, 8, 12, 19, 27, 31, 44]
    target = 19
    index = binary_search(arr, target)
    print(f"Array: {arr}")
    print(f"Target {target} found at index: {index}")


if __name__ == "__main__":
    solve()
