#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI printer(LPVOID number) {
	int* Loacal_Serial_number = (int*)number;

	for (int i = 0; i < 1000; i++) {
		printf("Thread %d, var = %d\n", *Loacal_Serial_number, i);
	}
	return 0;
}


int main() {
	int Serial_number[4] = {1, 2, 3, 4};
	HANDLE hThreads[4];

	for (int i = 0; i < 4; i++) {
		LPVOID Pcurrent_Serial_number = &Serial_number[i];

		hThreads[i] = CreateThread(
			NULL,
			0, 
			printer,
			Pcurrent_Serial_number,
			0,
			NULL
		);
	}

	WaitForMultipleObjects(4, hThreads, TRUE, INFINITE);
	for (int j = 0; j < 4; j++) {
		CloseHandle(hThreads[j]);
	}
	return 0;
}
