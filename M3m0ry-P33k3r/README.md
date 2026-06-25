# M3m0ry P33k3r: Native C Live PE Parser

A low-level memory forensics and diagnostic utility written in native C. This tool programmatically attaches to an active target process (`Notepad.exe`), navigates its virtual address space, parses its live Portable Executable (PE) headers, isolates the Original Entry Point (OEP), and dumps raw memory instruction bytes.

---

## Architectural Overview
Unlike static PE parsers that analyze files on disk via raw offsets, `M3m0ry P33k3r` operates entirely within runtime memory. It maps process spaces and translates Relative Virtual Addresses (RVAs) into absolute virtual addresses to read data directly from executing memory blocks.



---

## Repository Layout
- `/src`: Contains the primary implementation logic (`main.c`) and Modular header files for system process table enumeration (`findProcess.h`).
- `/bin`: Pre-compiled production execution profile (`M3m0ryP33k3r.exe`).

---

## Compilation and Deployment

### Prerequisites
- Windows Operating System (x64 architecture target)
- MSVC compiler (Visual Studio) or GCC (MinGW)

### Building from Source (GCC)
To compile the modular structure via the command line, execute:
```bash
gcc src/main.c -I include -o bin/M3m0ryP33k3r.exe
```

### Execution
<img width="1786" height="742" alt="output" src="https://github.com/user-attachments/assets/a96463e9-9eb1-4d95-a134-834b7ad7a113" />


