# CPU Performance Analyzer

## Overview

The **CPU Performance Analyzer** is a low-level systems project designed to **intentionally create, measure, and distinguish different performance bottlenecks** in a Linux environment.

Instead of guessing why a program is slow, this project demonstrates a **measurement-driven approach** using Linux performance counters (`perf`) to classify bottlenecks into:

- CPU (compute-bound)
- Memory (memory-bound)
- Threading & scheduling (contention / oversubscription)

The project serves both as:
- a **learning tool** for systems performance analysis, and
- a **practical demonstration** of how real-world performance engineers reason about bottlenecks.

---

## Why This Project?

In real systems, performance issues are rarely obvious.  
Optimizing the wrong component often gives **zero improvement**.

This project answers a fundamental question:

> **Given an unknown program, how do we *prove* what its bottleneck is?**

The answer is:
> By correlating **theory + hardware counters + observed behavior**.

---

## Project Structure

```text
cpu-bottleneck-analyzer/
│
├── src/
│   ├── main.cpp                 # Entry point and CLI dispatcher
│   ├── bottlenecks.h            # Common interface for all bottlenecks
│   ├── cpu_bottleneck.cpp       # CPU-bound workload
│   ├── memory_bottleneck.cpp    # Memory-bound workload
│   └── thread_bottleneck.cpp    # Multithreading & scheduling workload
│
├── analyzer                     # Compiled binary
├── .gitignore
└── README.md
```


Each bottleneck is implemented **independently**, allowing isolated testing and clean comparison using identical measurement tools.

---

## Environment Setup

This project relies on **Linux performance counters** and low-level OS scheduling behavior.  
It is designed to run on **Linux only** (native or VM).

---

### Operating System
- Ubuntu 20.04+ (recommended)
- Any modern Linux distro with `perf` support

> macOS / Windows are **not supported** because Linux `perf` requires kernel-level access.

---

### Required Tools

Install the following packages:

```bash
sudo apt update
sudo apt install -y \
    build-essential \
    linux-tools-common \
    linux-tools-$(uname -r) \
    perf
```
 Verify installation:
```bash
g++ --version
perf --version
```
---

## Build Instructions

 Compile the analyzer:
```bash
g++ src/main.cpp \
   src/cpu_bottleneck.cpp \
   src/memory_bottleneck.cpp \
   src/thread_bottleneck.cpp \
   -O2 -g -pthread -o analyzer
   ```
---
## Running the Analyzer

 **CPU-bound workload:**

```bash
./analyzer cpu
perf stat ./analyzer cpu
```


 **Memory-bound workload:**

```bash
./analyzer memory
perf stat ./analyzer memory
```

 **Threading & scheduling workload:**

```bash
./analyzer thread
perf stat ./analyzer thread
```
---

## Linux Profiling & Bottleneck Interpretation

This section demonstrates how **real-world Linux performance profiling** is done using
measured data instead of assumptions.

We use `perf stat` to correlate:
- wall-clock time
- user vs kernel execution
- scheduling behavior
- memory activity

---

## Understanding Time Breakdown

Linux execution time is split into:

- **User time** (`user`):  
  Time spent executing application code in user space.

- **System time** (`sys`):  
  Time spent executing kernel code (syscalls, memory management, scheduling).

- **Elapsed time** (`time elapsed`):  
  Real wall-clock time as observed by the user.

Key rule:
- If `user ≫ sys` → compute-bound
- If `sys` is significant → kernel / memory / syscall heavy
- If elapsed time ≪ total user time → parallel execution

---

## CPU Bottleneck Analysis

### Command Used
```bash
perf stat ./analyzer cpu
```
**Observed Metrics**
- CPUs utilized: ~0.99
- Context switches: very low
- CPU migrations: 0
- Page faults: low
- User time ≈ elapsed time
- System time ≈ 0

**Interpretation**
- Single thread fully occupies one CPU core
- Minimal kernel involvement
- No scheduling contention
- No memory pressure
  
**Conclusion**
- Compute-bound workload
- CPU execution units are the limiting factor.

## Memory Bottleneck Analysis
### Command Used
```bash
perf stat ./analyzer memory
```
**Observed Metrics**

- CPUs utilized: ~1.0
- Page faults: extremely high
- System time > user time
- Context switches: low

**Interpretation**
- Frequent memory accesses miss cache
- Kernel frequently handles page faults
- CPU often stalls waiting for memory

**Conclusion**
- Memory-bound workload
- Memory subsystem (cache / RAM) is the bottleneck, not compute.

## Threading & Scheduling Bottleneck Analysis
### Command Used
```bash
perf stat ./analyzer thread
```
**Observed Metrics**
- CPUs utilized: > 3.0
- Context switches: very high
- CPU migrations observed
- User time ≫ elapsed time

**Interpretation**
- Multiple threads running concurrently
- Oversubscription of CPU cores
- Scheduler frequently context-switches threads
- Threads migrate between cores

**Conclusion**
- Scheduling / contention bottleneck
- The Linux scheduler overhead dominates execution time.

---
## Metric → Bottleneck Mapping

| Metric            | Indicates                     |
|-------------------|-------------------------------|
| CPU utilization   | CPU-bound                     |
| Page faults       | Memory pressure               |
| Context switches  | Thread contention             |
| CPU migrations    | Scheduler overhead            |
| System time       | Kernel / memory activity      |

--- 
## Key Insight

Performance bottlenecks are identified by correlating theory with hardware counters, not by guessing.

### Measure → classify → optimize.







