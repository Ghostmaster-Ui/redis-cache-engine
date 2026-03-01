# Redis-Style Caching Engine

A high-speed distributed in-memory caching system built from scratch in C++17.

## Performance
- **117,000+ ops/sec** sustained across 50 concurrent clients
- **<2ms** retrieval latency
- **Zero data corruption** under heavy concurrent load

## Architecture

### Core Systems
- **In-memory store** — custom hash map with lock-striping for thread-safe concurrent reads/writes
- **LRU eviction** — doubly-linked list + hash map, O(1) eviction under memory pressure
- **Consistent hashing** — virtual node ring distributes keys across 4 nodes, minimizes rebalancing
- **Custom binary protocol** — length-prefixed frames over TCP, faster than text-based RESP

### Project Structure

src/
├── core/
│   ├── cache_store      # Thread-safe key-value store
│   ├── eviction_policy  # LRU eviction logic
│   └── consistent_hash  # Hash ring for node distribution
├── network/
│   ├── server           # TCP server with detached client threads
│   ├── protocol         # Binary wire protocol encoder/decoder
│   └── connection_pool  # Client connection management
└── distributed/
├── node_manager     # Node registry
└── replication      # Data sync across nodes
## Build & Run

```bash
mkdir build && cd build
cmake ..
make
./cache_server
```

## Benchmark

```bash
# With server running on port 6379
c++ -std=c++17 -O2 -pthread benchmarks/throughput_test.cpp -o bench
./bench
```

## Tech Stack
- C++17
- POSIX sockets (TCP)
- std::thread, std::mutex, std::atomic
- CMake
