#include <stdio.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <winnt.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER_SIZE 1024

int main() {
	DWORD PID = 0;
	uintptr_t baseAddr;
	BYTE buffer[MAX_BUFFER_SIZE];
	size_t BytesRead;

	HANDLE snapshotProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS , 0);
	
	MODULEENTRY32 me32;
	PROCESSENTRY32 pe32;
	me32.dwSize = sizeof(MODULEENTRY32);
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(snapshotProcess, &pe32)) {
		do {
			if (wcscmp(pe32.szExeFile, L"Notepad.exe") == 0) {
				PID = pe32.th32ProcessID;
				printf("\n[+]Notepad: PID: %lu", PID);
			}
		} while (Process32Next(snapshotProcess, &pe32));
	}
	else {
		printf("\nProcess not running...%lu", GetLastError());
	}

	HANDLE snapshotModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, PID);

	if (Module32First(snapshotModule, &me32)) {

		do {
			if (wcscmp(me32.szModule, L"Notepad.exe") == 0) {
				baseAddr = me32.modBaseAddr;
				//wprintf(L"\nBase Address: 0x%p\n", (BYTE *)baseAddr);
				printf("\n[+]Base Address found...");
			}
		} while (Module32Next(snapshotModule, &me32));
	}
	else {
		printf("\nProcess not running...%lu", GetLastError());
	}

	HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, PID);

	if (ReadProcessMemory(hProcess, baseAddr, buffer, MAX_BUFFER_SIZE, NULL)) {
		printf("\n---\nFirst 124 Bytes:");
		for (int i = 0; i < 124; i++) {
			printf(" %02X", buffer[i]);
		}
		printf("\n---");
	}
	else {
		printf("\nRead process threw a tantrum....%lu", GetLastError());
	}

	PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)buffer;

	if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE) {
		printf("\n[+]Magic Bytes %X verified...", dosHeader->e_magic);
	}

	printf("\n[+]Offset to NT Headers: 0x%X", dosHeader->e_lfanew);

	IMAGE_NT_HEADERS ntHeader;
	uintptr_t rva = (uintptr_t)baseAddr + dosHeader->e_lfanew;
	printf("\n[+]baseAddr     = %p", (void*)baseAddr);
	printf("\n[+]rva          = %p", (void*)rva);

	if (ReadProcessMemory(hProcess, (LPCVOID)rva, &ntHeader, sizeof(ntHeader), &BytesRead)) {
		printf("\n[+]NT Header:   = 0x%08X", ntHeader.Signature);
	}

	IMAGE_FILE_HEADER fHeader = ntHeader.FileHeader;

	time_t timeStamp = fHeader.TimeDateStamp;
	char* compilationTime = ctime(&timeStamp);

	printf("\n-----------------------------------------");
	printf("\nCompiler Timestamp: %s", compilationTime);
	printf("\n-----------------------------------------");

	return 0;
}