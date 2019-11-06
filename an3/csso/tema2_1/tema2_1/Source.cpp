#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <string>

using namespace std;

struct InfoProces {
	DWORD pid;
	DWORD ppid;
	char  exeName[256];
};

struct ProcessList {
	int         count;
	InfoProces  procese[2048];
};

HANDLE createMappedFile();
void writeProcesses(HANDLE);

int main() {
	HANDLE handle = createMappedFile();
	if (handle == NULL) {
		printf("Something went wrong");
		return -1;
	}
	writeProcesses(handle);
	getchar();
	return 0;
}

void writeProcesses(HANDLE handle) {
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	DWORD numberOfProcesses = 0;
	int offset = sizeof(numberOfProcesses);
	struct ProcessList processList;
	processList.count = 0;


	printf("Accesing the mapped file\n");
	unsigned char* pData = (unsigned char*)MapViewOfFile(handle, FILE_MAP_WRITE, 0, 0, 0);

	// get processes
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		printf("CreateToolhelp32Snapshot failed.err = %d \n", GetLastError());
		return;
	}
	//initializez dwSize cu dimensiunea structurii.
	pe32.dwSize = sizeof(PROCESSENTRY32);
	//obtin informatii despre primul proces
	if (!Process32First(hProcessSnap, &pe32)) {
		printf("Process32First failed. err = %d \n", GetLastError());
		CloseHandle(hProcessSnap);
		return;
	}
	do {
		//afisez pid-ul si executabilul
		printf("<%d><%d><%s>\n", pe32.th32ParentProcessID, pe32.th32ProcessID, pe32.szExeFile);
		processList.procese[processList.count].ppid = pe32.th32ParentProcessID;
		processList.procese[processList.count].pid = pe32.th32ProcessID;
		strcpy(processList.procese[processList.count].exeName, pe32.szExeFile);
		++processList.count;
		// <pid><ppid><exe name>
		/*memcpy(pData + offset, &pe32.th32ParentProcessID, sizeof(pe32.th32ParentProcessID));
		offset += sizeof(pe32.th32ParentProcessID);
		++numberOfProcesses;

		memcpy(pData + offset, &pe32.th32ProcessID, sizeof(pe32.th32ProcessID));
		offset += sizeof(pe32.th32ProcessID);

		memcpy(pData + offset, &pe32.szExeFile, sizeof(pe32.szExeFile));
		offset += sizeof(pe32.szExeFile);
		memcpy(pData + offset, "\n", sizeof("\n"));
		offset += sizeof("\n");
		*/
	} while (Process32Next(hProcessSnap, &pe32)); //trec la urmatorul proces

	// scriu la inceput cate procese au fost in total
	printf("In total sunt %d procese\n", processList.count);
	memcpy(pData, &processList, sizeof(processList));
	//memcpy(pData, &numberOfProcesses, sizeof(numberOfProcesses));

	//inched handle-ul catre snapshot 
	CloseHandle(hProcessSnap);
}

HANDLE createMappedFile() {
	HANDLE handle = CreateFileMapping(NULL, NULL, PAGE_READWRITE, 0, 1024 * 1024, "processes");
	printf("Created a mapped file\n");
	return handle;
}