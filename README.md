# Philosophers

A multithreaded solution to the classic dining philosophers problem in C, using threads and mutexes to prevent deadlock and data races.

![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)
![pthreads](https://img.shields.io/badge/pthreads-FCC624?logo=linux&logoColor=black)
![42 Barcelona](https://img.shields.io/badge/42-Barcelona-000000?logo=42&logoColor=white)

## About

Philosophers is a concurrency exercise from the 42 Common Core. A group of philosophers sit around a table alternating between eating, sleeping and thinking, sharing a limited set of forks. The program spins up one thread per philosopher plus a monitor thread, and coordinates access to the shared forks with mutexes so that no philosopher starves and no data race occurs. It demonstrates thread lifecycle management, mutex-based synchronization and precise timing without busy-waiting getting out of hand.

## What it does

- Creates one `pthread` per philosopher, each running an eat / sleep / think routine.
- Protects each fork with its own mutex, plus dedicated locks for writing, death state and meal tracking.
- Runs a separate monitor thread that detects when a philosopher dies or when every philosopher has eaten enough.
- Timestamps and prints every state change (taking a fork, eating, sleeping, thinking, dying) in a synchronized, non-interleaved way.
- Validates arguments strictly (positive integers, up to 300 philosophers) before starting the simulation.
- Compiled with AddressSanitizer to catch memory and threading issues.

## Build & run

```bash
# Build (from the philo directory)
cd philo
make

# Run: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo 5 800 200 200

# Optional: stop once every philosopher has eaten 3 times
./philo 5 800 200 200 3

# Clean up
make clean    # remove object files
make fclean   # remove objects and the binary
make re       # rebuild from scratch
```

All times are given in milliseconds.

## Concepts

C, POSIX threads (pthreads), mutexes, thread synchronization, deadlock and data-race avoidance, precise timing, memory management, AddressSanitizer.

_42 Barcelona · Common Core project._
