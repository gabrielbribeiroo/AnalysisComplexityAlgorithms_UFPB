# Analysis and Complexity of Algorithms - UFPB

[![Language](https://img.shields.io/badge/Language-C++-blue.svg)](https://isocpp.org/)
[![University](https://img.shields.io/badge/University-UFPB-green.svg)](https://www.ufpb.br/)

This repository contains the implementation, testing, and performance analysis of various algorithms studied in the **Analysis and Design of Algorithms** course at the Federal University of Paraíba (UFPB).

The objective of this project is to explore fundamental concepts of algorithm complexity through empirical analysis and theoretical comparisons.

---

## 🗂️ Project Structure

The project is organized into subdirectories by algorithmic topic, each containing its own implementation and detailed analysis.

### 1. [Sorting Algorithms](./sorting_algorithms/)
Implementations and comparisons of 4 fundamental sorting algorithms across various input scenarios:
- **Algorithms**: Insertion Sort, Selection Sort, Quick Sort, and Merge Sort.
- **Scenarios**: Random values, already sorted, reverse sorted, and frequent repetitions.
- **Analysis**: Focuses on comparing $O(n^2)$ vs. $O(n \log n)$ behaviors in practice.

### 2. [Knapsack Problem](./knapsack_problem/)
A detailed study of the **0-1 Knapsack Problem** (Part of APS3), comparing heuristic and optimal approaches:
- **Algorithms**: Greedy Algorithm (V/W ratio), Recursive Brute Force, and Dynamic Programming (Bottom-Up).
- **Scale**: Performance testing from $n=20$ up to $n=500,000$.
- **Key Insight**: Demonstrates $O(2^n)$ vs. $O(n \times Q)$ complexity and the optimality of different approaches.

---

## 🔧 Prerequisites

- **C++ Compiler** with C++14 support (e.g., g++ 6.3.0 or higher).
- **Windows**, Linux, or macOS environment.

## 🚀 General Setup

To run any module, navigate to its directory and follow the compilation instructions in its specific `README.md`.

For example, to test the knapsack problem:
```bash
cd knapsack_problem
g++ -o knapsack.exe knapsack.cpp -std=c++14
.\knapsack.exe
```

---

## 🎓 Learning Objectives

1. **Theoretical vs. Practical Complexity**: Understanding how asymptotic notation translates to real-world execution times.
2. **Algorithm Selection**: Identifying the right algorithm for a specific problem and data size.
3. **Optimality vs. Heuristics**: Recognizing trade-offs between guaranteed optimal results and computational speed.
4. **Hardware Influence**: Evaluating how environment and resource limitations (memory/CPU) affect algorithm feasibility.

---

## 👨‍🎓 Author

**Gabriel**  
Computer Science - Period 5  
Federal University of Paraíba (UFPB)

---

**Period**: 2025.2  
**Institution**: UFPB - Federal University of Paraíba
