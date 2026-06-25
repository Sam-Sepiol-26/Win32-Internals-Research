# The Active Process Enumerator

A custom process discovery tool that bypasses high-level wrappers to map the live environment.

---

## Architectural Overview

Unlike graphical task management utilities that abstract process information, `The Active Process Enumerator` interfaces directly with native Windows APIs to capture a live snapshot of the system's active processes. It iterates through each process entry, extracts the Process Identifier (PID) and executable name, and presents a real-time view of the currently executing processes.


---

## Repository Layout
- `/src`: Contains the primary implementation logic (`main.c`).
- `/bin`: Pre-compiled production execution profile (`The Active Process Enumerator.exe`).

---

## Compilation and Deployment

### Prerequisites
- Windows Operating System (x64 architecture target)
- MSVC compiler (Visual Studio) or GCC (MinGW)

### Building from Source (GCC)
To compile the modular structure via the command line, execute:
```bash
gcc src/main.c -I include -o bin/The Active Process Enumerator.exe
```

### Execution:
<img width="875" height="850" alt="output" src="https://github.com/user-attachments/assets/efcb31ff-a8a9-48c4-8e11-e313db92642c" />



