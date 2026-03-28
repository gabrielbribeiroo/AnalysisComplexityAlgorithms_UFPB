# Sorting Algorithms - Analysis and Complexity

This subdirectory contains the implementation and performance analysis of fundamental sorting algorithms as part of the **Analysis and Design of Algorithms** course at UFPB.

## 🗂️ Directory Structure

```
sorting_algorithms/
├── sort1.cpp          # Main implementation with all sorting algorithms
├── sort1.exe          # Compiled executable (Windows)
└── output.txt         # Sample test results
```

## 🔧 Implemented Algorithms

The project currently implements and compares **4 fundamental sorting algorithms**:

| Algorithm | Time Complexity (Best) | Time Complexity (Average) | Time Complexity (Worst) | Space Complexity |
|-----------|------------------------|---------------------------|-------------------------|------------------|
| **Insertion Sort** | O(n) | O(n²) | O(n²) | O(1) |
| **Selection Sort** | O(n²) | O(n²) | O(n²) | O(1) |
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | O(log n) |
| **Merge Sort** | O(n log n) | O(n log n) | O(n log n) | O(n) |

### Implementation Details

- **Insertion Sort**: Builds sorted array one element at a time.
- **Selection Sort**: Repeatedly finds minimum element and places it at the beginning.
- **Quick Sort**: Uses Hoare's partitioning scheme for divide-and-conquer.
- **Merge Sort**: Recursively divides and merges sorted subarrays.

## 🧪 Testing Framework

The implementation includes a comprehensive testing framework that evaluates all algorithms across **4 different scenarios**:

1. **Random Values (Uniform Distribution)**: Random integers between 0-9999.
2. **Few Unique Values (High Repetition)**: Only 5 unique values with high repetition.
3. **Already Sorted (Best Case)**: Ascending sequence.
4. **Reverse Sorted (Worst Case)**: Descending sequence.

### Performance Measurement

Each test measures execution time in **microseconds** using C++ `<chrono>` library for high-precision timing.

## 🚀 Getting Started

### Compilation

```bash
# Compile with g++ (C++11 or higher)
g++ -o sort1.exe sort1.cpp -std=c++11

# On Linux/macOS
g++ -o sort1 sort1.cpp -std=c++11
```

### Running Tests

```bash
# Windows
.\sort1.exe

# Linux/macOS
./sort1
```

## 📊 Key Observations

Based on the testing framework:
- **Insertion Sort**: Very fast on already sorted data, but extremely slow on reverse sorted data.
- **Selection Sort**: Consistent O(n²) performance regardless of input.
- **Quick Sort**: Fast on random data but may degrade depending on pivot selection.
- **Merge Sort**: Consistent O(n log n) performance across all scenarios, but requires O(n) additional memory.

---
**Author**: Gabriel
**Course**: Analysis and Design of Algorithms - UFPB (2025.2)
