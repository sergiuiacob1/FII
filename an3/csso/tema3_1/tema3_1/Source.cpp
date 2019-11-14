#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>

using namespace std;

HANDLE createMappedFile();
void generateNumbers(HANDLE);
void writeToMappedFile(unsigned char *, HANDLE, int, int);
void waitForCheck(HANDLE);

int main() {
	srand((unsigned int)time(NULL));
	HANDLE handle = createMappedFile();
	if (handle == NULL) {
		printf("P1 - Something went wrong");
		return -1;
	}
	generateNumbers(handle);
	CloseHandle(handle);
	printf("P1 - Finished\n");
	getchar();
	return 0;
}

void generateNumbers(HANDLE handle) {
	printf("P1 - Accesing the mapped file\n");
	unsigned char* pData = (unsigned char*)MapViewOfFile(handle, FILE_MAP_WRITE, 0, 0, 0);

	int howMany = rand() % 300 + 100;
	int i, randomNumber;
	float half;

	// creez evenimentul pentru scriere in MappedFile
	printf("P1 - Creating handle for event\n");
	HANDLE hEvent = CreateEvent(NULL, true, FALSE, "access_mapped_file");
	HANDLE hCheckEvent = CreateEvent(NULL, true, FALSE, "check_event");

	// scriu care e PID-ul acestui proces ca sa ma pot atasa la consola
	writeToMappedFile(pData, hEvent, (int)GetCurrentProcessId(), 0);

	// scriu in mapped file cate numere am
	howMany = 5;
	printf("P1 - I have a total of %d numbers\n", howMany);
	writeToMappedFile(pData, hEvent, howMany, 1);

	for (int i = 2; i <= howMany + 1; ++i) {
		randomNumber = rand() % 1000;
		half = randomNumber * 1.0f / 2;
		writeToMappedFile(pData, hEvent, randomNumber, i);
		waitForCheck(hCheckEvent);
	}

	CloseHandle(hEvent);
	CloseHandle(hCheckEvent);
}

void waitForCheck(HANDLE hCheckEvent) {
	WaitForSingleObject(hCheckEvent, LONG_MAX);
}

void writeToMappedFile(unsigned char * pData, HANDLE hEvent, int number, int index) {
	double half = number * 1.0f / 2;
	// scriu dadadadadadaaaaaaaaaaaa
	printf("P1 - Writing %d and %lf to MappedFile\n", number, half);
	memcpy(pData + 2 * index * (sizeof(number)), &number, sizeof(number));
	memcpy(pData + 2 * (index + 1) * sizeof(half), &half, sizeof(half));
	// semnalizez ca am un eveniment nou, am scris un nou numar
	SetEvent(hEvent);

}

HANDLE createMappedFile() {
	HANDLE handle = CreateFileMapping(NULL, NULL, PAGE_READWRITE, 0, 1024 * 1024, "mapped_file");
	printf("P1 - Created a mapped file\n");
	return handle;
}