#include <stdio.h>
#include <windows.h>
#include <TlHelp32.h>

int main() {
	printf("\nWelcome to my Process Enumerator...\n");
	printf("\n-----------------------------------------------------------------\n");

	PROCESSENTRY32 pe32;
	HANDLE listProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(listProcess, &pe32)) {
		do {
			printf("\nPID: %lu\t-\tProcess Name: %ls", pe32.th32ProcessID, pe32.szExeFile);
		} while(Process32Next(listProcess,&pe32));
	}
	printf("\n-----------------------------------------------------------------\n");
	CloseHandle(listProcess);

	return 0;
}