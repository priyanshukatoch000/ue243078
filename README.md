# ue243078
Practical-1: Power of a Number
Aim

To implement and compare two recursive techniques for calculating a number raised to the power n.

Theory

The optimized recursive approach computes the result by splitting the exponent into halves, which significantly reduces the number of recursive calls.

The simple recursive approach finds the result by repeatedly multiplying the base until the exponent reaches zero.

Time Complexity

Optimized recursive method: O(log n)

Simple recursive method: O(n)

Space Complexity

Optimized recursive method: O(log n)

Simple recursive method: O(n)

What the Code Does

This program computes the power of a number using two different recursive strategies.

The powerRec(x, n) function follows a divide-and-conquer approach.
If the exponent is zero, it returns 1.
If the exponent is negative, it converts it to a positive value.

The function recursively calculates x^(n/2) and stores the result.
If the exponent is even, the result is multiplied by itself.
If the exponent is odd, the result is multiplied by x once more.

This method is efficient and performs well even for large values of n.

The powerRec2(x, n) function uses a straightforward recursive approach.
It multiplies x with the result of the function called with n − 1.
This continues until the exponent becomes zero.

Although this method is simpler to understand, it is slower for larger inputs.

Conclusion

Both methods correctly compute the power of a number.
The optimized recursive approach is faster due to fewer recursive calls.

Practical-2: Tower of Hanoi
Aim

To implement the Tower of Hanoi problem using recursion and display the sequence of moves required to transfer all disks from the source rod to the destination rod.

Theory

The Tower of Hanoi is a classic problem where disks are moved from one rod to another using an auxiliary rod, following certain rules:

Only one disk can be moved at a time.
A larger disk cannot be placed on top of a smaller disk.
All disks must be transferred from the source rod to the destination rod.

The solution is obtained using recursion by breaking the problem into smaller subproblems.

Time Complexity

The total number of moves required is (2ⁿ − 1).
Time complexity is O(2ⁿ).

Space Complexity

The recursive call stack can grow up to depth n.
Space complexity is O(n).

What the Code Does

This program accepts the number of disks as input and prints the steps needed to solve the Tower of Hanoi problem.

The TOH(n, src, dest, ex) function works recursively:

If the number of disks is less than or equal to zero, the function stops.
If there is only one disk, it is moved directly from the source rod to the destination rod.
For more than one disk, the function first moves n−1 disks from the source rod to the extra rod.
Then it moves the largest disk to the destination rod.
Finally, it moves the n−1 disks from the extra rod to the destination rod.

The main method reads the input and starts the recursive process.

Conclusion

The program effectively demonstrates recursion through the Tower of Hanoi problem.
It shows how a complex task can be solved by dividing it into simpler recursive steps.

Practical-3: Permutations of a String
Aim

To generate and display all possible permutations of a given string using recursion.

Theory

A permutation is a unique arrangement of the characters of a string.
This problem is efficiently solved using recursion combined with backtracking.

The idea is to fix one character at a time and recursively generate permutations for the remaining characters.
After each recursive call, backtracking restores the original order so that new permutations can be formed.

Time Complexity

A string of length n has n! permutations.
Time complexity is O(n!).

Space Complexity

The maximum depth of recursion is n.
Space complexity is O(n) (excluding output storage).

What the Code Does

This program prints all permutations of a character array.

The perm(char[] str, int i) function works recursively.
When the index i equals the length of the array, the current arrangement is printed.

If i is less than the length, the function loops from index i to the end.
During each iteration, characters at positions i and j are swapped.
The function then calls itself for the next index.

After returning from recursion, the characters are swapped back to their original positions.
This backtracking step ensures that all possible permutations are generated.

The swapChar function swaps two characters, and the main method initiates the process.

Conclusion

The program correctly generates all permutations of a string.
It clearly illustrates the use of recursion along with backtracking.

Practical-4: Velocity Reduction Using Recursion
Aim

To calculate the number of steps required for a velocity value to fall below a given limit using recursion.

Theory

This program uses recursion to repeatedly reduce velocity until it becomes less than 1.
In each step, the velocity is decreased by a fixed percentage of its current value.

A counter is maintained to track the number of recursive calls needed to reach the stopping condition.

Time Complexity

The velocity is reduced until it becomes less than 1.
Time complexity is O(k), where k is the number of reductions.

Space Complexity

The recursive stack grows according to the number of steps.
Space complexity is O(k).

What the Code Does

This program calculates how many reductions are required for velocity to drop below 1.

The tips(double v, int t) function works recursively.
If v is greater than or equal to 1, the counter t is incremented.
The velocity is reduced by 42.5%, and the function is called again.

When the velocity becomes less than 1, the function returns the total count.

The main method starts with an initial velocity of 40 and prints the number of steps.

Conclusion

The program demonstrates how recursion can be used to repeatedly apply an operation until a condition is satisfied.
It also highlights the use of a counter to track recursive depth.

Practical-5: Horner’s Rule Using Recursion
Aim

To represent a polynomial expression using Horner’s Rule through recursion.

Theory

Horner’s Rule is an efficient method of representing and evaluating polynomials by minimizing the number of multiplications.
The polynomial is written in a nested form instead of an expanded form.

Recursion is used to construct this nested expression step by step from the coefficient array.

Time Complexity

Each coefficient is processed once.
Time complexity is O(n).

Space Complexity

The recursion depth depends on the number of coefficients.
Space complexity is O(n).

What the Code Does

This program builds a polynomial expression using Horner’s Rule.

The HR(int i, int[] arr) function works recursively.
If i reaches the last index, the function returns that coefficient as a string.

Otherwise, it returns the current coefficient followed by a nested expression involving x, and calls itself for the next index.

The main method initializes the coefficient array and prints the final expression.

Conclusion

The program successfully represents a polynomial using Horner’s Rule with the help of recursion.

Practical-6: Finding Duplicate in a Consecutive Array
Aim

To identify a duplicate element in an array of consecutive numbers using a comparison-based approach.

Theory

In a consecutive array, each element is expected to match its index value.
Any mismatch indicates the presence of a duplicate element.

The program compares each element with its index to detect the duplicate.

Time Complexity

The array is scanned once.
Time complexity is O(n).

Space Complexity

No additional data structures are used.
Space complexity is O(1).

What the Code Does

This program finds a duplicate value in an array of consecutive numbers.

The findDup(int[] nums) function iterates through the array.
At each index, it compares the stored value with the index using the XOR operator.

If a mismatch is found, that value is returned as the duplicate.
If no mismatch exists, the function returns −1.

The main method demonstrates this using a sample array.

Conclusion

The program correctly identifies the duplicate element.
It shows how a simple linear scan can efficiently detect errors in ordered data.

Practical-7: Selection Sort Using Recursion
Aim

To sort an array in ascending order using selection sort implemented recursively.

Theory

Selection sort works by repeatedly selecting the smallest element from the unsorted portion of the array and placing it at the correct position.

In this implementation, recursion replaces iterative loops to move through the array.

Time Complexity

Selection sort performs the same number of comparisons in all cases.
Time complexity is O(n²).

Space Complexity

The array is sorted in place.
Recursive depth can reach n.
Space complexity is O(n).

What the Code Does

This program performs selection sort using recursion.

The ss(int[] arr, int i) function stops when i reaches the array length.

For each recursive step:
The minIndex function finds the smallest element in the remaining array.
The swapIndex function swaps it with the element at index i.
The function then calls itself for the next index.

A helper method measures execution time, while the main method sorts and prints a sample array.

Conclusion

The program demonstrates recursive selection sort effectively.
It shows how basic sorting algorithms can be implemented recursively.

Practical-8: Bubble Sort Using Recursion
Aim

To sort an array using recursive bubble sort and measure execution time.

Theory

Bubble sort repeatedly compares adjacent elements and swaps them if they are out of order.
After each pass, the largest element moves to its correct position at the end.

Recursion replaces nested loops to perform multiple passes.

Time Complexity

Best case: O(n)
Average case: O(n²)
Worst case: O(n²)

Space Complexity

The array is sorted in place.
Recursive stack depth can reach n.
Space complexity is O(n).

What the Code Does

This program performs bubble sort recursively and calculates execution time.

The bb(int[] arr, int i) function performs one pass per recursive call.
Adjacent elements are compared and swapped as needed.
After one pass, the function calls itself for the next iteration.

The time(int[] arr) function measures sorting time using System.nanoTime().

The main method generates a random array, runs the algorithm multiple times, and prints the average execution time.

Conclusion

The program effectively demonstrates recursive bubble sort.
It also shows how execution time can be measured and analyzed.

Practical-9: Linear Search Using Recursion
Aim

To search for an element in an array using recursive linear search and measure execution time.

Theory

Linear search checks each element sequentially until the target is found or the array ends.

Here, recursion is used instead of iteration to traverse the array.

Time Complexity

Best case: O(1)
Average case: O(n)
Worst case: O(n)

Space Complexity

Recursive calls can grow up to n.
Space complexity is O(n).

What the Code Does

This program searches for a target element using recursion and measures execution time.

The LS(int[] arr, int target, int i) function checks one element per recursive call.
If the end of the array is reached, it returns −1.
If the element matches the target, it returns the index.
Otherwise, it continues with the next index.

The time(int[] arr, int target) function measures execution time.

The main method generates a random array, performs multiple searches, and prints the average time.

Conclusion

The program successfully demonstrates recursive linear search.
It also shows how search time increases with input size.
