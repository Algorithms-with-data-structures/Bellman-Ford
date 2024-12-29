# Bellman-Ford Algorithm Implementation

## Overview
This repository contains a C++ implementation of the Bellman-Ford algorithm for finding the shortest paths from a source vertex to all other vertices in a weighted graph. The Bellman-Ford algorithm is particularly useful for graphs with negative edge weights, as it can detect negative-weight cycles in the graph.

### Theory
The Bellman-Ford algorithm works by iteratively relaxing all edges in the graph. It repeats this process for `(V - 1)` iterations, where `V` is the number of vertices in the graph. After these iterations, the algorithm checks for negative-weight cycles by verifying if any edge can still be relaxed. If an edge can still be relaxed, it means the graph contains a negative-weight cycle.

#### Key Features:
- Handles graphs with negative edge weights.
- Detects negative-weight cycles.
- Runs in **O(V \* E)** time, where `V` is the number of vertices and `E` is the number of edges.

### Applications:
- Network routing protocols (e.g., RIP protocol).
- Solving shortest path problems in transportation and logistics.
- Arbitrage detection in financial systems.

---

## Input Files
The program can read graph data from a file. Two sample files are provided:

### `graph1.txt`:
```
4
0 7 12 17
2 0 6 7
3 10 0 9
5 7 5 0
```

### `graphBig.txt`:
```
12
0 7 37 34 13 48 50 26 45 4 19 30
36 0 2 21 16 3 17 2 5 9 34 49
14 14 0 44 10 29 22 2 6 23 50 46
22 6 5 0 4 11 15 8 43 31 9 19
17 14 27 28 0 22 20 5 21 38 46 25
38 33 34 41 49 0 33 27 32 16 8 5
19 15 45 37 34 28 0 2 25 20 26 17
40 28 36 18 45 23 27 0 28 2 1 15
17 48 37 5 4 34 36 12 0 18 33 39
26 6 49 11 26 10 11 21 41 0 34 9
26 11 25 6 36 43 25 13 47 41 0 18
17 18 36 45 14 24 43 21 28 16 8 0
```

- The first line specifies the number of vertices.
- The remaining lines specify the adjacency matrix where each value represents the edge weight between vertices.

---

## Features

### Menu Options:
1. **Read graph from file:** Load a graph from a file (e.g., `graph1.txt` or `graphBig.txt`).
2. **Generate random graph:** Create a random graph with a user-specified number of nodes.
3. **Run algorithm:** Execute the Bellman-Ford algorithm to find the shortest path from a specified starting node.
4. **Display shortest path:** Display the shortest path and its cost to a specified destination node.
5. **Exit:** Exit the program.

### Error Handling:
- Validates file existence and format.
- Ensures start and destination nodes are within bounds.
- Detects and reports negative-weight cycles.

---

## How to Run

### Prerequisites:
- A C++ compiler supporting C++11 or later.
- Basic knowledge of terminal or command-line operations.

### Compilation:
Use the following command to compile the program:
```bash
g++ -o bellman_ford bellman_ford.cpp
```

### Running the Program:
After compiling, execute the program using:
```bash
./bellman_ford
```

### Example Workflow:
1. Choose option `1` to read a graph from `graph1.txt`.
2. Choose option `3` and enter a starting node (e.g., `0`).
3. Choose option `4` and enter a destination node (e.g., `3`).

---

## Sample Output

### Example 1:
Input file: `graph1.txt`

**Menu Option 3:**
```
Enter the starting node: 0
Execution time of Bellman-Ford algorithm: 10μs.
```

**Menu Option 4:**
```
Enter the destination node: 3
Path: 0 1 3
Path cost: 14
```

### Example 2:
Input file: `graphBig.txt`

**Menu Option 3:**
```
Enter the starting node: 5
Execution time of Bellman-Ford algorithm: 180μs.
```

**Menu Option 4:**
```
Enter the destination node: 9
Path: 5 6 9
Path cost: 43
```

---

## Notes
- For large graphs, the execution time increases due to the algorithm’s complexity.
- The program assumes no self-loops or duplicate edges in the graph.
