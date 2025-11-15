#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

struct Mystruct {
	int num1;
	int num2;
};

DWORD WINAPI bla(LPVOID lparam) {
	struct Mystruct* nums = (struct Mystruct*)lparam;
	int sum = nums->num1 + nums->num2;
	for (int i = 0; i < sum; i++) {
		printf("bla\n");
	}
	Sleep(20000);
	return 1;
}

int main()
{
	struct Mystruct* Newstruct = (struct Mystruct*)malloc(sizeof(struct Mystruct));
	Newstruct->num1 = 6;
	Newstruct->num2 = 4;

	LPVOID PNewstruct = Newstruct;   // same as: void* ptr = my_struct;
	
	HANDLE hThread = CreateThread(
		NULL,			//default security attributes
		0,				//default stack size
		bla,			//thread function
		PNewstruct,		//thread param
		0,				//default creation flags
		NULL			//return thread identifier

	);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	free(Newstruct);
	return 0;
}