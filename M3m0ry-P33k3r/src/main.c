#include "findProcess.h"
#include <stdio.h>
#include <windows.h>
#include <inttypes.h>
#include <stdint.h>


int display(int pid) {
	printf("\n---M3m0ry P33k3r---");
	printf("\n[+]Target Process Name: Notepad.exe...");
	printf("\n[+]Finding the PID of the target process...");
	pid = processChecker();
	return pid;
}

int main() {
	IMAGE_NT_HEADERS64 ntHeaders;
	IMAGE_DOS_HEADER dosHeader;
	MODULEENTRY32 mod32;
	DWORD rva;
	DWORD_PTR entryPoint;
	mod32.dwSize = sizeof(MODULEENTRY32);
	int pid = 0;
	int Ppid = display(pid);
	BYTE buffer[256];
	if (Ppid == 1) {
		printf("\n[!]Target Process not running. Run process first...");
	}
	else {
		printf("\n[+]PID found: %lu", Ppid);
	}
	HANDLE hProcess = OpenProcess(PROCESS_VM_READ,FALSE,Ppid);

	HANDLE moduleList = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, Ppid);

	if (Module32First(moduleList, &mod32)) {
		printf("\n[+]Found module Base Address: 0x%p", mod32.modBaseAddr);
	}

	//printf("The address of entry point: 0x%X", entryPoint);
	
	if (hProcess == NULL)
	{
		printf("\n[!]OpenProcess failed: %lu\n", GetLastError());
		return 1;
	}
	//printf("\nPointer size: %zu\n", sizeof(void*)); We know my system is x64 cause pointer size is 8

	if(!ReadProcessMemory(hProcess, mod32.modBaseAddr, &dosHeader, sizeof(dosHeader), NULL)) {
		printf("\nReadProcessMemory failed: %lu", GetLastError());
	}
	if (dosHeader.e_magic == IMAGE_DOS_SIGNATURE) {
		printf("\n[+]Finding DOS Header...");
		printf("\n[+]DOS Header Found...");
		printf("\n[+]Verifying Magic Bytes...");
		printf("\n[+]E Magic: 0x%X", dosHeader.e_magic);
	}

	DWORD_PTR ntHeaderAddress = (DWORD_PTR)mod32.modBaseAddr + dosHeader.e_lfanew;

	printf("\n[+]Finding NT Header Address...");
	printf("\n[+]NT Header Address found: 0x%p", (void *)ntHeaderAddress);

	if (ntHeaders.Signature = IMAGE_NT_SIGNATURE) {
		printf("\n[+]Verifying NT Signature...");
		printf("\n[+]Valid PE Header found...");
	}
	if (ReadProcessMemory(hProcess, ntHeaderAddress, &ntHeaders, sizeof(ntHeaders), NULL)) {
		rva = ntHeaders.OptionalHeader.AddressOfEntryPoint;
		entryPoint = (DWORD_PTR)mod32.modBaseAddr + rva;
		printf("\n[+]Finding the entry point of the target process [PID: %lu]", Ppid);
		printf("\n[+]Entry Point found: 0x%p", (void *)entryPoint);
	}
	else
	{
		printf("\nReadProcessMemory NT failed: %lu", GetLastError());
	}

	if (ReadProcessMemory(hProcess, (LPCVOID)entryPoint, &buffer, sizeof(buffer), NULL)) {
		printf("\n[+]Read contents of the target process from 0x%p\n", (void*)entryPoint);
		for (int i = 0; i < sizeof(buffer); i++) {
			printf(" %02X", buffer[i]);
		}
	}
	return 0;
}