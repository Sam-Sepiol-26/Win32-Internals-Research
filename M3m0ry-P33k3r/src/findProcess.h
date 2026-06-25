#include <stdio.h>
#include <windows.h>
#include <TlHelp32.h>
#include <string.h>
#include <wchar.h>

int processChecker() {
	
	PROCESSENTRY32 pe32;
	HANDLE listProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);
	
	BOOL processRunning = FALSE;

	if (Process32First(listProcess, &pe32) != NULL) {
		do {
			if (wcscmp(pe32.szExeFile, L"Notepad.exe") == 0) {
				//printf("\n[+]PID found: %lu", pe32.th32ProcessID);
				processRunning = TRUE;
				return pe32.th32ProcessID;
				break;
			}
		} while (Process32Next(listProcess, &pe32));
		/*if(!processRunning) {
			printf("\n[!]Target Process not running. Run process first...");
		}*/
	}
	
	CloseHandle(listProcess);
}
