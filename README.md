CS509_ASSIGNMENTS/
├── wrapper.c                   # Master interactive terminal wrapper
├── wrapper.exe                 # Compiled master interactive executable
├── README.md                   # Project documentation
│
├── ASSIGNMENT_1/
│   ├── include/
│   │   ├── csr.h               # CSR graph representation interface
│   │   └── gemm.h              # GEMM matrix multiplication interface
│   ├── src/
│   │   ├── csr.c               # CSR conversion implementation
│   │   ├── gemm.c              # GEMM algorithms (simple & blocked)
│   │   └── driver.c            # Assignment 1 driver program
│   ├── tests/
│   │   ├── csr/                # Test input matrices for CSR
│   │   └── gemm/               # Test matrices for GEMM
│   └── driver.exe              # Assignment 1 executable
│
├── ASSIGNMENT_2/
│   ├── include/
│   │   ├── bellman_ford.h      # Bellman-Ford algorithm interface
│   │   └── floyd_warshall.h    # Floyd-Warshall algorithm interface
│   ├── src/
│   │   ├── bellman_ford.c      # Bellman-Ford implementation
│   │   ├── floyd_warshall.c    # Floyd-Warshall implementation
│   │   └── driver_a2.c         # Assignment 2 driver program
│   ├── tests/
│   │   ├── bellman_ford/       # Weighted adjacency list input files
│   │   └── floyd_warshall/     # Dense V x V matrix input files
│   └── driver.exe              # Assignment 2 executable
│
└── ASSIGNMENT_3/
    ├── include/
    │   └── mst.h               # Minimum Spanning Tree (Kruskal & Prim) interface
    ├── src/
    │   ├── kruskal.c           # Kruskal's MST implementation (DSU-based)
    │   ├── prim.c              # Prim's MST implementation
    │   └── driver_a3.c         # Assignment 3 driver program
    ├── tests/
    │   └── mst/                # Weighted undirected CSR adjacency-list benchmarks
    ├── Makefile                # Assignment 3 compilation script
    └── driver.exe              # Assignment 3 executable






    ##commands
    # 1. Terminate any running wrapper instance
Stop-Process -Name "wrapper" -Force -ErrorAction SilentlyContinue

# 2. Compile the master wrapper
gcc wrapper.c -o wrapper.exe

# 3. Launch Master Wrapper
.\wrapper.exe