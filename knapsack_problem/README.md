# 0-1 Knapsack Problem - Analysis and Complexity (APS3)

This subdirectory contains the implementation and analysis of three fundamental algorithms for the **0-1 Knapsack Problem** as part of the **APS3 (Atividade Prática Supervisionada 3)** for the Analysis and Design of Algorithms course at UFPB.

## 📋 Problem Overview

Given $n$ items, each with a weight $w_i$ and a value $v_i$, and a knapsack with capacity $Q$, the goal is to choose a subset of items that maximize the total value without exceeding the capacity.

## 🗂️ Directory Structure

```
knapsack_problem/
├── knapsack.cpp      # Main implementation of all 3 algorithms
└── output.txt        # Detailed report for video presentation and results
```

## 🔧 Implemented Algorithms

The project compares **3 fundamental approaches**:

| Algorithm | Time Complexity | Space Complexity | Guaranteed Optimal? |
|-----------|-----------------|------------------|-------------------|
| **Greedy Algorithm** | $O(n \log n)$ | $O(1)$ | No (Heuristic) |
| **Recursive Brute Force** | $O(2^n)$ | $O(n)$ | Yes |
| **Dynamic Programming** | $O(n \times Q)$ | $O(n \times Q)$ | Yes |

### Implementation Details

1. **Greedy Algorithm**: Sorts items by the ratio $v_i / w_i$ and picks items until the capacity is reached.
2. **Recursive Brute Force**: Explores all $2^n$ combinations of items. Efficient in memory but only feasible for very small $n$.
3. **Dynamic Programming (Bottom-Up)**: Uses a 2D table to build the optimal solution from subproblems. It's pseudo-polynomial and highly efficient for reasonable capacities.

## 🧪 Testing Framework

The algorithms were tested across 9 different scenarios as specified in the course (from $n=20$ up to $n=500,000$).

### Key Insights

- **Brute Force Viability**: For instances with $n \ge 100$, the brute force algorithm becomes computationally prohibitive due to its $O(2^n)$ complexity. For $n=100$, it's estimated that it would take billions of years even on state-of-the-art hardware.
- **Greedy Accuracy**: The greedy approach is extremely fast but was found to be sub-optimal in some cases (e.g., in instances with $n=500, Q=100$), producing results within $0.1-1\%$ of the optimal value.
- **Dynamic Programming Performance**: It remains the most reliable method for optimal solutions with large $n$, scaling well as long as $n \times Q$ stays within memory limits (~400 MB for $n=500,000$ and $Q=100$).

## 🚀 Getting Started

### Compilation

```bash
# Compile with g++ (C++14 or higher)
g++ -o knapsack.exe knapsack.cpp -std=c++14
```

### Running Tests

```bash
# Windows
.\knapsack.exe

# The output includes a detailed presentation of results and complexity comparisons.
```

---
**Author**: Gabriel
**Course**: Analysis and Design of Algorithms - UFPB (2025.2)
