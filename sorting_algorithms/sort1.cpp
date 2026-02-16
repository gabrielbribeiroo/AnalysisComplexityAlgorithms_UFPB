// ============================================================================
// LIBRARIES
// ============================================================================
#include <iostream>  // For input/output operations (cout, endl)
#include <chrono>    // For time measurement (high_resolution_clock, microseconds)
#include <vector>    // For dynamic array support (not currently used)
#include <cstdlib>   // For random number generation (rand, srand)
#include <ctime>     // For time function (time)
#include <cmath>     // For mathematical functions (floor)
#include <climits>   // For constants (INT_MAX)

using namespace std;
using namespace std::chrono;


// ============================================================================
// INSERTION SORT ALGORITHM
// ============================================================================
// Description: Builds the sorted array one element at a time by repeatedly
//              inserting the next element into its correct position.
// Time Complexity: O(n²) worst/average case, O(n) best case
// Space Complexity: O(1) - sorts in place
//
// Parameters:
//   a[] - array to be sorted
//   n   - number of elements in the array
// Returns: pointer to the sorted array
// ============================================================================
int *insertion_sort(int a[], int n) {
    int pivot;  // Current element being inserted into sorted portion
    int i, j;   // Loop indices
    
    // Start from second element (index 1), as first element is trivially sorted
    for (i = 1; i <= n-1; i++) {
        pivot = a[i];  // Store current element to insert
        j = i - 1;     // Start comparing with previous element
        
        // Shift elements greater than pivot one position to the right
        while (j >= 0 && a[j] > pivot) {
            a[j+1] = a[j];  // Move element one position right
            j = j - 1;       // Move to previous element
        }
        
        // Insert pivot at its correct position
        a[j+1] = pivot;
    }
    return a;
}


// ============================================================================
// SELECTION SORT ALGORITHM
// ============================================================================
// Description: Divides array into sorted and unsorted portions. Repeatedly
//              finds the minimum element from unsorted portion and moves it
//              to the end of sorted portion.
// Time Complexity: O(n²) in all cases
// Space Complexity: O(1) - sorts in place
//
// Parameters:
//   a[] - array to be sorted
//   n   - number of elements in the array
// Returns: pointer to the sorted array
// ============================================================================
int *selection_sort(int a[], int n) {
    int i, j;      // Loop indices
    int min_idx;   // Index of minimum element in unsorted portion
    int temp;      // Temporary variable for swapping
        
    // Iterate through array, expanding sorted portion from left
    for (i = 0; i <= n-2; i++) {
        min_idx = i;  // Assume current position has minimum
        
        // Find the minimum element in remaining unsorted array
        for (j = i+1; j <= n-1; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;  // Update index of minimum element
            }
        }
        
        // Swap minimum element with current position (if different)
        if (a[i] != a[min_idx]) {
            temp = a[i];
            a[i] = a[min_idx];
            a[min_idx] = temp;
        }
    }
    return a;
}


// ============================================================================
// MERGE FUNCTION (Helper for Merge Sort)
// ============================================================================
// Description: Merges two sorted subarrays into a single sorted array.
//              Uses sentinel values (INT_MAX) to simplify boundary checks.
//
// Parameters:
//   a[] - array containing both subarrays
//   p   - starting index of first subarray
//   q   - ending index of first subarray
//   r   - ending index of second subarray
// Note: First subarray is a[p..q], second is a[q+1..r]
// ============================================================================
void merge(int *a, int p, int q, int r) {
    // Calculate sizes of the two subarrays
    int n1 = q - p + 1;  // Size of left subarray
    int n2 = r - q;      // Size of right subarray
    
    // Create temporary arrays with extra space for sentinel values
    int L[n1 + 1], R[n2 + 1];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) L[i] = a[p + i];      // Copy left subarray
    for (int j = 0; j < n2; j++) R[j] = a[q + 1 + j];  // Copy right subarray

    // Add sentinel values (infinity) at the end of each array
    // This eliminates the need to check if we've reached the end
    L[n1] = INT_MAX;  // Sentinel for left array
    R[n2] = INT_MAX;  // Sentinel for right array

    // Merge the temporary arrays back into a[p..r]
    int i = 0, j = 0;  // Initial indices for L[] and R[]
    for (int k = p; k <= r; k++) {
        // Compare elements and pick the smaller one
        if (L[i] <= R[j]) {
            a[k] = L[i++];  // Take from left array and increment index
        } 
        else {
            a[k] = R[j++];  // Take from right array and increment index
        }
    }
}


// ============================================================================
// MERGE SORT ALGORITHM
// ============================================================================
// Description: Divide-and-conquer algorithm that recursively divides array
//              into halves, sorts them, and merges them back together.
// Time Complexity: O(n log n) in all cases
// Space Complexity: O(n) - requires temporary arrays for merging
//
// Parameters:
//   a[] - array to be sorted
//   p   - starting index of the portion to sort
//   r   - ending index of the portion to sort
// ============================================================================
void merge_sort(int *a, int p, int r) {
    int q;  // Middle point index
    
    // Base case: if p >= r, array has 0 or 1 element (already sorted)
    if (p < r) {
        // Find the middle point to divide array into two halves
        q = floor((p + r) / 2);
        
        // Recursively sort first half
        merge_sort(a, p, q);
        
        // Recursively sort second half
        merge_sort(a, q+1, r);
        
        // Merge the two sorted halves
        merge(a, p, q, r);
    } 
}


// ============================================================================
// PARTITION FUNCTION (Helper for Quick Sort - Hoare's Scheme)
// ============================================================================
// Description: Partitions array around a pivot element (first element).
//              Elements smaller than pivot go to left, larger go to right.
//              Uses Hoare's partitioning scheme with two-pointer approach.
//
// Parameters:
//   a[] - array to be partitioned
//   l   - left boundary (start index)
//   r   - right boundary (end index)
// Returns: index of partition point
// ============================================================================
int partition(int *a, int l, int r) {
    int pivot, i, j;
    
    pivot = a[l];  // Choose first element as pivot
    i = l - 1;     // Initialize left pointer (will increment before use)
    j = r + 1;     // Initialize right pointer (will decrement before use)
    
    // Infinite loop - will return when pointers cross
    while (1) {
        // Move left pointer right until finding element >= pivot
        do {
            i++;
        } while (a[i] < pivot);
        
        // Move right pointer left until finding element <= pivot
        do {
            j--;
        } while (a[j] > pivot);
        
        // If pointers have crossed, partition is complete
        if (i >= j) {
            return j;  // Return partition index
        }

        // Swap elements at i and j to put them on correct sides
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}


// ============================================================================
// QUICK SORT ALGORITHM
// ============================================================================
// Description: Divide-and-conquer algorithm that picks a pivot element and
//              partitions array around it, then recursively sorts partitions.
// Time Complexity: O(n log n) average, O(n²) worst case
// Space Complexity: O(log n) average - recursive call stack
//
// Parameters:
//   a[] - array to be sorted
//   l   - left boundary (start index)
//   r   - right boundary (end index)
// ============================================================================
void quick_sort(int *a, int l, int r) {
    int q;  // Partition index
    
    // Base case: if l >= r, array has 0 or 1 element (already sorted)
    if (l < r) {
        // Partition array and get partition index
        q = partition(a, l, r);
        
        // Recursively sort elements before partition
        quick_sort(a, l, q);
        
        // Recursively sort elements after partition
        quick_sort(a, q+1, r);
    } 
}


// ============================================================================
// UTILITY FUNCTION: Print Array
// ============================================================================
// Description: Prints all elements of an array separated by spaces.
//
// Parameters:
//   A[] - array to print
//   n   - number of elements in the array
// ============================================================================
void printArray(int A[], int n) {
    for(int i = 0; i < n; i++) cout << A[i] << " ";
    cout << endl;
}


// ============================================================================
// UTILITY FUNCTION: Copy Array
// ============================================================================
// Description: Creates a copy of an array to preserve original data for
//              multiple tests with different algorithms.
//
// Parameters:
//   source[] - source array to copy from
//   dest[]   - destination array to copy to
//   n        - number of elements to copy
// ============================================================================
void copyArray(int source[], int dest[], int n) {
    for(int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}


// ============================================================================
// UTILITY FUNCTION: Test Sorting Algorithm
// ============================================================================
// Description: Tests a sorting algorithm and measures its execution time.
//              Displays the algorithm name, test scenario, and time taken.
//
// Parameters:
//   A[]           - array to be sorted
//   n             - number of elements in the array
//   algoName      - name of the algorithm being tested
//   scenarioName  - name of the test scenario
//   algoType      - algorithm type (1=Insertion, 2=Selection, 3=Quick, 4=Merge)
// ============================================================================
void testAlgorithm(int A[], int n, string algoName, string scenarioName, int algoType) {
    // Create a copy of the array to preserve original
    int testArray[n];
    copyArray(A, testArray, n);
    
    // Display test information
    cout << "\n" << algoName << " - " << scenarioName << endl;
    cout << "Array size: " << n << " elements" << endl;
    
    // Start time measurement
    auto start = high_resolution_clock::now();
    
    // Execute the appropriate sorting algorithm
    switch(algoType) {
        case 1:  // Insertion Sort
            insertion_sort(testArray, n);
            break;
        case 2:  // Selection Sort
            selection_sort(testArray, n);
            break;
        case 3:  // Quick Sort
            quick_sort(testArray, 0, n-1);
            break;
        case 4:  // Merge Sort
            merge_sort(testArray, 0, n-1);
            break;
    }
    
    // End time measurement
    auto end = high_resolution_clock::now();
    
    // Calculate elapsed time in microseconds
    auto duration = duration_cast<microseconds>(end - start);
    
    // Display execution time
    cout << "Execution time: " << duration.count() << " microseconds" << endl;
}


// ============================================================================
// MAIN FUNCTION - Comprehensive Testing and Performance Measurement
// ============================================================================
int main() {
    // Test configuration - you can modify these sizes for different experiments
    int sizes[] = {100, 500, 1000, 5000, 10000};  // Different array sizes to test
    int numSizes = 5;
    
    // For demonstration, we'll use n = 1000
    // You can loop through all sizes in the array above for comprehensive testing
    int n = 1000;
    
    cout << "============================================================================" << endl;
    cout << "SORTING ALGORITHMS PERFORMANCE COMPARISON" << endl;
    cout << "============================================================================" << endl;
    cout << "Testing 4 algorithms on 4 different scenarios" << endl;
    cout << "Array size: " << n << " elements" << endl;
    cout << "============================================================================" << endl;
    
    // ========================================================================
    // SCENARIO 1: Random Values with Uniform Distribution
    // ========================================================================
    cout << "\n\n========== SCENARIO 1: RANDOM VALUES (UNIFORM DISTRIBUTION) ==========" << endl;
    
    int randomArray[n];
    srand(time(0));  // Seed random number generator
    for(int i = 0; i < n; i++) {
        randomArray[i] = rand() % 10000;  // Random values between 0 and 9999
    }
    
    testAlgorithm(randomArray, n, "Insertion Sort", "Random Values", 1);
    testAlgorithm(randomArray, n, "Selection Sort", "Random Values", 2);
    testAlgorithm(randomArray, n, "Quick Sort", "Random Values", 3);
    testAlgorithm(randomArray, n, "Merge Sort", "Random Values", 4);
    
    
    // ========================================================================
    // SCENARIO 2: Few Unique Values (High Repetition)
    // ========================================================================
    cout << "\n\n========== SCENARIO 2: FEW UNIQUE VALUES (HIGH REPETITION) ==========" << endl;
    
    int fewUniqueArray[n];
    int uniqueValues[] = {10, 20, 30, 40, 50};  // Only 5 unique values
    for(int i = 0; i < n; i++) {
        fewUniqueArray[i] = uniqueValues[rand() % 5];  // Randomly pick from 5 values
    }
    
    testAlgorithm(fewUniqueArray, n, "Insertion Sort", "Few Unique Values", 1);
    testAlgorithm(fewUniqueArray, n, "Selection Sort", "Few Unique Values", 2);
    testAlgorithm(fewUniqueArray, n, "Quick Sort", "Few Unique Values", 3);
    testAlgorithm(fewUniqueArray, n, "Merge Sort", "Few Unique Values", 4);
    
    
    // ========================================================================
    // SCENARIO 3: Already Sorted (Non-decreasing Order)
    // ========================================================================
    cout << "\n\n========== SCENARIO 3: ALREADY SORTED (BEST CASE) ==========" << endl;
    
    int sortedArray[n];
    for(int i = 0; i < n; i++) {
        sortedArray[i] = i + 1;  // Creates sequence: 1, 2, 3, ..., n
    }
    
    testAlgorithm(sortedArray, n, "Insertion Sort", "Already Sorted", 1);
    testAlgorithm(sortedArray, n, "Selection Sort", "Already Sorted", 2);
    testAlgorithm(sortedArray, n, "Quick Sort", "Already Sorted", 3);
    testAlgorithm(sortedArray, n, "Merge Sort", "Already Sorted", 4);
    
    
    // ========================================================================
    // SCENARIO 4: Reverse Sorted (Worst Case)
    // ========================================================================
    cout << "\n\n========== SCENARIO 4: REVERSE SORTED (WORST CASE) ==========" << endl;
    
    int reversedArray[n];
    for(int i = 0; i < n; i++) {
        reversedArray[i] = n - i;  // Creates sequence: n, n-1, n-2, ..., 1
    }
    
    testAlgorithm(reversedArray, n, "Insertion Sort", "Reverse Sorted", 1);
    testAlgorithm(reversedArray, n, "Selection Sort", "Reverse Sorted", 2);
    testAlgorithm(reversedArray, n, "Quick Sort", "Reverse Sorted", 3);
    testAlgorithm(reversedArray, n, "Merge Sort", "Reverse Sorted", 4);
    
    
    // ========================================================================
    // Summary
    // ========================================================================
    cout << "\n\n============================================================================" << endl;
    cout << "TESTING COMPLETE" << endl;
    cout << "============================================================================" << endl;
    cout << "All 4 algorithms tested on 4 different scenarios." << endl;
    cout << "Compare the execution times above to analyze algorithm efficiency." << endl;
    cout << "\nKey Observations to Look For:" << endl;
    cout << "- Insertion Sort: Fast on sorted data, slow on reversed data" << endl;
    cout << "- Selection Sort: Consistent O(n²) performance in all cases" << endl;
    cout << "- Quick Sort: Fast on random data, may be slow on sorted/reversed" << endl;
    cout << "- Merge Sort: Consistent O(n log n) performance in all cases" << endl;
    cout << "============================================================================" << endl;
    
    return 0;
}