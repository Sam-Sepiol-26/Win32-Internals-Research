# Win32-Internals-Research

A collection of low-level Windows research tools and custom Portable Executable (PE) parsers built in native C using the Win32 API to study OS internals, process manipulation, and reverse engineering mechanics.

This repository serves as a practical, hands-on laboratory for exploring the boundaries between user-mode execution, memory management, and the underlying structures of the Windows operating system.

---

| Date | Project-Name | Core concepts | Description |
|------|-------------|------------------|-------------|
| 06-19-2026 | The Active Process Enumerator | Process snapshots, process tracking, system enumeration | A custom process discovery tool that bypasses high-level wrappers to map the live environment. |
| 06-21-2026 | M3m0ry_P33k3r (Remote PE Parser) | Virtual memory space mapping, DOS/NT header parsing, Address of Entry Point (AoEP) calculation, Hex dumping live assembly. | An advanced memory scanner that targets an active process, dynamically parses its remote headers in RAM, and extracts executable machine code instructions straight from the entry point. |
| 06-25-2026 | C0mp1l3_T1m3st4mp_3xtr4ct0r | File alignment vs. Section alignment, Epoch time conversion, PE static analysis.| A runtime analysis tool that attaches to a live, active process in memory, traverses its running NT header structures, and isolates the compiler `TimeDateStamp` field directly from RAM to audit binary metadata dynamically. |

---


---

## Disclaimer
This project is developed strictly for educational purposes, OS internals research, and malware analysis triage training. All tools are designed to be run in isolated, controlled research environments.
