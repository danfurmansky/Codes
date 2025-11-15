#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define EXE_FILENAME "C:\\Users\\danfu\\source\\repos\\test\\x64\\Debug\\test.exe"
#define PROCESS_ARG "4"

int main() {
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CHAR exe_filename[] = EXE_FILENAME;
	CHAR process_arg[] = PROCESS_ARG;
	INT size = strlen(exe_filename) + strlen(process_arg) + 2;
	PCHAR param = (PCHAR)malloc(size * sizeof(CHAR));
	sprintf_s(param, size, "%s %s", exe_filename, process_arg);

	BOOL ok = CreateProcessA(
		NULL,	//ApplicationName
		param, // Command line
		NULL, // Process handle not inheritable
		NULL, // Thread handle not inheritable
		FALSE, // Set handle inheritance to FALSE
		0, // No creation flags
		NULL, // Use parent's environment block
		NULL, // Use parent's starting directory
		&si, // Pointer to STARTUPINFO structure
		&pi // Pointer to PROCESS_INFORMATION structure
	);
		
	if (!ok) {
		printf("Failed to start process. Error = %lu\n", GetLastError());
		free(param);
		return 1;
	}

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	free(param);
	return 0;
}