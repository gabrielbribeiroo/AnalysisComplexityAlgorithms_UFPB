# Analysis and Complexity of Algorithms - UFPB

[![Language](https://img.shields.io/badge/Language-C++-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/C++-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B11)
[![University](https://img.shields.io/badge/University-UFPB-green.svg)](https://www.ufpb.br/)

Repository for the **Analysis and Design of Algorithms** course at the Federal University of Paraíba (UFPB), Period 5 - 2025.2.

## 📋 Overview

This repository contains implementations and performance analysis of fundamental algorithms studied in the Analysis and Design of Algorithms course. The focus is on understanding algorithm complexity, comparing different approaches, and analyzing performance under various scenarios.

## 🗂️ Project Structure

```
AnalysisComplexityAlgorithms_UFPB/
├── sorting_algorithms/
│   ├── sort1.cpp          # Main implementation with all sorting algorithms
│   ├── sort1.exe          # Compiled executable
│   └── output.txt         # Sample test results
└── README.md              # This file
```

## 🔧 Implemented Algorithms

### Sorting Algorithms

The project currently implements and compares **4 fundamental sorting algorithms**:

| Algorithm | Time Complexity (Best) | Time Complexity (Average) | Time Complexity (Worst) | Space Complexity |
|-----------|------------------------|---------------------------|-------------------------|------------------|
| **Insertion Sort** | O(n) | O(n²) | O(n²) | O(1) |
| **Selection Sort** | O(n²) | O(n²) | O(n²) | O(1) |
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | O(log n) |
| **Merge Sort** | O(n log n) | O(n log n) | O(n log n) | O(n) |

#### Implementation Details

- **Insertion Sort**: Builds sorted array one element at a time
- **Selection Sort**: Repeatedly finds minimum element and places it at the beginning
- **Quick Sort**: Uses Hoare's partitioning scheme for divide-and-conquer
- **Merge Sort**: Recursively divides and merges sorted subarrays

## 🧪 Testing Framework

The implementation includes a comprehensive testing framework that evaluates all algorithms across **4 different scenarios**:

### Test Scenarios

1. **Random Values (Uniform Distribution)**
   - Random integers between 0-9999
   - Tests average-case performance

2. **Few Unique Values (High Repetition)**
   - Only 5 unique values with high repetition
   - Tests performance with many duplicates

3. **Already Sorted (Best Case)**
   - Ascending sequence: 1, 2, 3, ..., n
   - Tests best-case performance

4. **Reverse Sorted (Worst Case)**
   - Descending sequence: n, n-1, n-2, ..., 1
   - Tests worst-case performance

### Performance Measurement

Each test measures execution time in **microseconds** using C++ `<chrono>` library for high-precision timing.

## 🚀 Getting Started

### Prerequisites

- **C++ Compiler** with C++11 support (g++, clang++, MSVC)
- **Windows**, Linux, or macOS

### Compilation

```bash
# Navigate to sorting_algorithms directory
cd sorting_algorithms

# Compile with g++
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

### Sample Output

```
============================================================================
SORTING ALGORITHMS PERFORMANCE COMPARISON
============================================================================
Testing 4 algorithms on 4 different scenarios
Array size: 1000 elements
============================================================================


========== SCENARIO 1: RANDOM VALUES (UNIFORM DISTRIBUTION) ==========

Insertion Sort - Random Values
Array size: 1000 elements
Execution time: 2543 microseconds

Selection Sort - Random Values
Array size: 1000 elements
Execution time: 1876 microseconds

Quick Sort - Random Values
Array size: 1000 elements
Execution time: 156 microseconds

Merge Sort - Random Values
Array size: 1000 elements
Execution time: 234 microseconds

...
```

## 📊 Customizing Tests

### Changing Array Size

Modify the `n` variable in `main()`:

```cpp
int n = 1000;  // Change to desired size (e.g., 5000, 10000)
```

### Testing Multiple Sizes

Uncomment and use the `sizes[]` array for comprehensive testing:

```cpp
int sizes[] = {100, 500, 1000, 5000, 10000};
// Add loop to iterate through all sizes
```

## 📚 Key Observations

Based on the testing framework, you should observe:

- **Insertion Sort**: 
  - ⚡ Very fast on already sorted data
  - 🐌 Very slow on reverse sorted data
  
- **Selection Sort**: 
  - 📊 Consistent O(n²) performance regardless of input
  
- **Quick Sort**: 
  - ⚡ Fast on random data
  - ⚠️ May degrade to O(n²) on sorted/reversed data (depends on pivot selection)
  
- **Merge Sort**: 
  - ✅ Consistent O(n log n) performance across all scenarios
  - 💾 Requires additional memory for merging

## 🎓 Learning Objectives

This project helps understand:

1. **Algorithm Complexity Analysis**: Theoretical vs. practical performance
2. **Best/Average/Worst Case Scenarios**: How input affects performance
3. **Trade-offs**: Time complexity vs. space complexity
4. **Empirical Analysis**: Measuring and comparing real execution times
5. **Algorithm Selection**: Choosing the right algorithm for specific scenarios

## 📝 Code Documentation

All code is fully documented in English with:
- Detailed function descriptions
- Parameter explanations
- Complexity analysis
- Inline comments explaining logic

## 🤝 Contributing

This is an academic project for the Analysis and Design of Algorithms course at UFPB. Suggestions and improvements are welcome!

## 📄 License

This project is developed for educational purposes as part of the Computer Science curriculum at UFPB.

## 👨‍🎓 Author

**Gabriel**  
Computer Science - Period 5  
Federal University of Paraíba (UFPB)  
2025.2

---

**Course**: Analysis and Design of Algorithms  
**Institution**: UFPB - Federal University of Paraíba  
**Period**: 2025.2
