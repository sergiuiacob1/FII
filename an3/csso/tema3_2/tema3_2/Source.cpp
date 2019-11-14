#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <string>

using namespace std;

HANDLE getMappedFileHandle();
void checkNumbers(HANDLE);
int readNumber(HANDLE, unsigned char*, int);
double readHalf(unsigned char*, int);

int main() {
	HANDLE handle = getMappedFileHandle();
	if (handle == NULL) {
		printf("Handle could not be acquired: %d", GetLastError());
		return -1;
	}
	checkNumbers(handle);
	CloseHandle(handle);
	printf("P2 - Finished\n");
	return 0;
}

void checkNumbers(HANDLE hFile) {
	int howMany, number, pid;
	double half;

	printf("P2 - Accesing the mapped file\n");
	unsigned char* pData = (unsigned char*)MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pData == NULL) {
		printf("P2 - Cannot get pointer to file mapping. Error code: %d", GetLastError());
		CloseHandle(hFile);
		return;
	}

	printf("P2 - Opening write event...\n");
	HANDLE hEvent = OpenEvent(EVENT_MODIFY_STATE, false, "access_mapped_file");
	HANDLE hCheckEvent = OpenEvent(EVENT_MODIFY_STATE, false, "check_event");

	pid = readNumber(hEvent, pData, 0);
	printf("P2 - The first process has PID %d --- Attaching to its console...\n", pid);
	if (FreeConsole() == false) {
		printf("P2 - Freeing current console failed: %d\n", GetLastError());
		return;
	}
	printf("P2 - Successfully freed current console\n");
	if (AttachConsole(pid) == 0) {
		printf("P2 - Attaching to console failed: %d\n", GetLastError());
		return;
	}
	printf("P2 - Successfully attached to P1 console!\n");

	howMany = readNumber(hEvent, pData, 1);
	for (int i = 2; i <= howMany + 1; ++i) {
		number = readNumber(hEvent, pData, i);
		half = readHalf(pData, i);

		printf("P2 - Checking %d and %lf\n", number, half);
		if (half * 2 == (double)number)
			printf("P2 - TRUE\n");
		else
			printf("P2 - FALSE\n");
		//Sleep(500);
		SetEvent(hCheckEvent);
	}
}

int readNumber(HANDLE hEvent, unsigned char* pData, int index) {
	WaitForSingleObject(hEvent, LONG_MAX);
	int* ptr = (int*)(pData + 2 * index * sizeof(int));
	int number = *ptr;
	return number;
}

double readHalf(unsigned char* pData, int index) {
	double* ptr = (double*)(pData + 2 * (index + 1) * sizeof(double));
	double half = *ptr;
	return half;
}

HANDLE getMappedFileHandle() {
	return OpenFileMapping(PAGE_READONLY, false, "mapped_file");
}