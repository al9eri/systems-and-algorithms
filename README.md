# systems-and-algorithms

[![CI](https://github.com/al9eri/systems-and-algorithms/actions/workflows/ci.yml/badge.svg)](https://github.com/al9eri/systems-and-algorithms/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

C11 systems programming implementations (POSIX threads, counting semaphores, mutexes, System V shared memory, and `AF_INET` TCP sockets) alongside divide-and-conquer and sorting benchmarks in Python.

## What's inside

- **`concurrency/`**: Multi-barber Sleeping Barber (`sleeping_barber_semaphores.c`), deterministic 3-thread barrier (`thread_barrier_semaphores.c`), parallel Fibonacci (`parallel_fibonacci_pthreads.c`), worker pools, plus comparisons of `pthread_mutex_t`, lock variables, strict turn alternation, and unsynchronized race conditions.
- **`ipc-networking/`**: Bidirectional TCP socket RPC server/client (`tcp_socket_server.c`, `tcp_socket_client.c` on port `8080` reducing integer arrays over the wire), System V shared-memory IPC (`sysv_shared_memory_ipc.c` using `ftok`/`shmget`/`shmat`/`shmctl` across `fork()`), structured shared memory, and process fork trees.
- **`algorithms/`**: Arbitrary-base LSD Radix Sort (`radix_sort_lsd.py`) and $O(n \log n)$ divide-and-conquer maximum interval overlap (`interval_overlap_divide_and_conquer.py`) benchmarked against $O(n^2)$ brute force.

## Build & run

### C targets (Linux / WSL / macOS)

```bash
make all

./bin/sleeping_barber_semaphores
./bin/parallel_fibonacci_pthreads 20 50 100

# In two terminals:
./bin/tcp_socket_server
./bin/tcp_socket_client

make clean
```

### Python algorithms

```bash
python algorithms/radix_sort_lsd.py
python algorithms/interval_overlap_divide_and_conquer.py
```
