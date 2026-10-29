# Systems Programming & Algorithms

A curated collection of **POSIX systems programming implementations in C** (concurrency primitives, synchronization patterns, and inter-process communication) alongside **classic algorithm implementations in Python**.

---

## Repository Structure

```text
├── concurrency/
│   ├── sleeping_barber_semaphores.c    # Multi-barber Sleeping Barber problem using POSIX semaphores & mutexes
│   ├── thread_barrier_semaphores.c     # Deterministic 3-thread ordering using counting semaphores
│   ├── parallel_fibonacci_pthreads.c   # Multi-threaded Fibonacci sequence generation via pthreads
│   ├── multithreaded_workers.c         # Concurrent worker thread pool pattern
│   ├── mutex_sync.c                    # Critical-section protection with pthread_mutex_t
│   ├── lock_var_sync.c                 # Lock-variable synchronization demonstration
│   ├── turn_var_sync.c                 # Strict alternation (Peterson/turn variable) synchronization
│   └── race_condition_demo.c           # Unsynchronized shared-state race condition benchmark
├── ipc-networking/
│   ├── tcp_socket_server.c             # AF_INET / SOCK_STREAM TCP server for remote array reduction
│   ├── tcp_socket_client.c             # Interactive TCP client for binary payload transmission
│   ├── sysv_shared_memory_ipc.c        # System V shared memory (shmget/shmat/shmctl) across fork()
│   ├── shared_memory_struct.c          # Structured IPC across parent/child processes
│   └── process_fork_tree.c             # Process hierarchy creation and wait() synchronization
├── algorithms/
│   ├── interval_overlap_divide_and_conquer.py  # O(n log n) Divide & Conquer vs O(n²) Brute Force interval overlap
│   └── radix_sort_lsd.py                       # Arbitrary-base Least Significant Digit (LSD) Radix Sort
└── Makefile
```

---

## Key Implementations

### 1. Concurrency & Synchronization (`concurrency/`)
- **Multi-Barber Sleeping Barber (`sleeping_barber_semaphores.c`):** Models bounded waiting-room capacity (`NUM_WAITING_CHAIRS = 5`), multiple concurrent barber threads (`NUM_BARBERS = 3`), and customer arrival threads coordinated without deadlock or starvation using `sem_t` (`customerSem`, `barberSem`) and `pthread_mutex_t`.
- **Ordered Thread Rendezvous (`thread_barrier_semaphores.c`):** Enforces strict round-robin execution order across 3 concurrent `pthread` workers using chained POSIX semaphores.
- **Synchronization Primitives Comparison (`mutex_sync.c`, `lock_var_sync.c`, `turn_var_sync.c`, `race_condition_demo.c`):** Contrasts hardware/OS-backed `pthread_mutex_t` locks against naive lock variables and strict turn-based alternation.

### 2. Inter-Process Communication & Networking (`ipc-networking/`)
- **TCP Client/Server RPC (`tcp_socket_server.c`, `tcp_socket_client.c`):** Implements a bidirectional `SOCK_STREAM` server on port `8080` that performs a handshake, receives variable-length integer arrays over the wire, computes the reduction sum, and returns the result to the client.
- **System V Shared Memory (`sysv_shared_memory_ipc.c`):** Allocates multi-segment shared memory blocks via `ftok`, `shmget`, and `shmat`, exchanges string buffers between child and parent processes across `fork()`, transforms payloads in-place, and cleanly detaches/deallocates segments via `shmdt` and `shmctl(..., IPC_RMID, NULL)`.

### 3. Algorithms (`algorithms/`)
- **Divide & Conquer Maximum Interval Overlap (`interval_overlap_divide_and_conquer.py`):** Pre-sorts intervals in linear time using LSD Radix Sort and computes maximum pairwise interval overlap using Divide & Conquer ($O(n \log n)$) benchmarked against a Brute Force ($O(n^2)$) baseline.
- **Arbitrary-Base LSD Radix Sort (`radix_sort_lsd.py`):** Non-comparative integer sorting using stable counting sort passes from least significant to most significant digit.

---

## Building & Running

### C Programs (Linux / WSL / macOS)

Build all concurrency and IPC targets using `make`:

```bash
make all
```

Run individual binaries:

```bash
# Run the multi-barber synchronization simulation
./bin/sleeping_barber_semaphores

# Run TCP server & client (in two terminals)
./bin/tcp_socket_server
./bin/tcp_socket_client

# Run parallel pthreads Fibonacci generator
./bin/parallel_fibonacci_pthreads 20 50 100
```

Clean build artifacts:

```bash
make clean
```

### Python Algorithms

```bash
python algorithms/radix_sort_lsd.py
python algorithms/interval_overlap_divide_and_conquer.py
```
