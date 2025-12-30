# CPU Bottleneck Analyzer

## Overview

The **CPU Bottleneck Analyzer** is a low-level systems project designed to **intentionally create, measure, and distinguish different performance bottlenecks** in a Linux environment.

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
## Observations & Inference

**CPU Bottleneck**
- ~1.0 CPU utilized
- Very low context switches
- Very low page faults
  
**Inference:** Compute-bound workload

**Memory Bottleneck**
- High page faults
- Higher system time
  
**Inference:** Memory-bound workload

**Thread Bottleneck**
- CPU utilization > 1.0
- High context switches
- CPU migrations observed
  
**Inference:** Scheduling / contention bottleneck

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







