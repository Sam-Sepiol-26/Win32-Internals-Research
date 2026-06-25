# C0mp1l3_T1m3st4mp_3xtr4ct0r

A runtime analysis tool that attaches to a live, active process in memory, traverses its running NT header structures, and isolates the compiler TimeDateStamp field directly from RAM to audit binary metadata dynamically.

---

## Architectural Overview

Rather than inspecting Portable Executable files on disk, C0mp1l3_T1m3st4mp_3xtr4ct0r targets a live process and navigates its in-memory PE structures. It resolves the NT headers within the executing image and reads the compiler TimeDateStamp field directly from runtime memory, demonstrating metadata extraction from an active process rather than a static binary.


---

## Repository Layout
- `/src`: Contains the primary implementation logic (`main.c`).
- `/bin`: Pre-compiled production execution profile (`C0mp1l3_T1m3st4mp_3xtr4ct0r.exe`).

---

## Compilation and Deployment

### Prerequisites
- Windows Operating System (x64 architecture target)
- MSVC compiler (Visual Studio) or GCC (MinGW)

### Building from Source (GCC)
To compile the modular structure via the command line, execute:
```bash
gcc src/main.c -I include -o bin/C0mp1l3_T1m3st4mp_3xtr4ct0r.exe
```

### Execution
<img width="1447" height="485" alt="output" src="https://github.com/user-attachments/assets/a569bf6d-0377-4c7c-b0a6-0cb5d1359c25" />


### Verification (DOS Stub)
<img width="1801" height="682" alt="dosStub" src="https://github.com/user-attachments/assets/e728ff97-5366-44c1-a0d9-e94fd83fff80" />



