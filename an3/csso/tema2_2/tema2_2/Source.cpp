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


bool processWasDisplayed[2048];
int countDisplayed;

HANDLE getMappedFileHandle();
ProcessList* listProcesses(HANDLE);
bool setPrivilleges();
void listInfoForProcess(ProcessList*, char*);
void killProcessTree(ProcessList*, int);

void displayProcess(const ProcessList* pData, int position, int tabCount) {
	for (int i = 0; i < tabCount; ++i)
		printf("    ");
	printf("%s %d\n", pData->procese[position].exeName, pData->procese[position].pid);
	processWasDisplayed[position] = true;
	++countDisplayed;

	for (int i = 0; i < pData->count; ++i) {
		if (processWasDisplayed[i] == true)
			continue;
		if (pData->procese[i].ppid == pData->procese[position].pid)
			displayProcess(pData, i, tabCount + 1);
	}
}

int main() {
	if (setPrivilleges() == false) {
		printf("Error\n");
		return -1;
	}

	HANDLE handle = getMappedFileHandle();
	if (handle == NULL) {
		printf("Handle could not be acquired: %d", GetLastError());
		return -1;
	}
	ProcessList* pData = listProcesses(handle);

	printf("\n\n");
	int option = 0, processID;
	char processName[256];
	while (1) {
		printf("Introdu optiunea (0 iesi): ");
		scanf("%d", &option);
		if (option == 0)
			break;

		if (option == 1)
		{
			printf("Introdu numele procesului: ");
			scanf("%s", processName);
			listInfoForProcess(pData, processName);
		}

		if (option == 2) {
			printf("Introdu PID-ul procesului: ");
			scanf("%d", &processID);
			killProcessTree(pData, processID);
		}
	}

	getchar();
	return 0;
}

void listInfoForProcess(ProcessList* pData, char* processName) {
	int children = 0, processID = -1;
	for (int i = 0; i < pData->count; ++i)
		if (strcmp(pData->procese[i].exeName, processName) == 0) {
			processID = pData->procese[i].pid;

			children = 0;
			for (int i = 0; i < pData->count; ++i)
				if (pData->procese[i].ppid == processID)
					++children;
			printf("ID-ul procesului este %d si are %d copii\n", processID, children);

		}
}

void killProcessTree(ProcessList* pData, int pID) {
	int children[2048], st = 0, dr = 0, currentPID;
	children[0] = pID;
	while (st <= dr) {
		currentPID = children[st++];
		for (int i = 0; i < pData->count; ++i)
			if (pData->procese[i].ppid == currentPID && pData->procese[i].pid != currentPID)
				children[++dr] = pData->procese[i].pid;
	}

	printf("Killing process tree for PID %d\n", pID);
	for (int i = 0; i <= dr; ++i) {
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, children[i]);
		if (handle == INVALID_HANDLE_VALUE) {
			printf("Handle error: %d\n", GetLastError());
			continue;
		}
		TerminateProcess(handle, 0);
	}
}

bool setPrivilleges() {
	HANDLE pToken = NULL;
	LUID lpLuid;
	TOKEN_PRIVILEGES tp;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &pToken) == false) {
		printf("Could not open process token\n");
		return false;
	}

	// identific id-ul pentru privilegiul SE_DEBUG_NAME
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &lpLuid)) {
		printf("LookupPrivilegeValueW failed: %d\n", GetLastError());
		CloseHandle(pToken);
		return false;
	}
	printf("Codul privilegiului este %d\n", lpLuid);

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = lpLuid;

	if (!AdjustTokenPrivileges(
		pToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		(PTOKEN_PRIVILEGES)NULL,
		(PDWORD)NULL)
		)
	{
		printf("LAdjustTokenPrivileges() failed, error %d\n", GetLastError());
		CloseHandle(pToken);
		return false;
	}

	CloseHandle(pToken);
	return true;
}

ProcessList* listProcesses(HANDLE handle) {
	int numberOfProcesses, parentProcessID, processID;
	char exeName[256];

	printf("Accesing the mapped file\n");
	ProcessList* pData = (ProcessList*)MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pData == NULL) {
		printf("Cannot get pointer to file mapping. Error code: %d", GetLastError());
		CloseHandle(handle);
		return NULL;
	}

	printf("In total sunt %d\n", pData->count);
	int treeCount = 0, root;
	bool done;
	while (countDisplayed < pData->count) {
		// Caut urmatoarea radacina
		for (int i = 0; i < pData->count; ++i)
			if (processWasDisplayed[i] == false) {
				root = i;
				break;
			}
		done = false;
		while (!done) {
			done = true;
			// vad daca root are vreun parinte
			for (int i = 0; i < pData->count; ++i)
				if (pData->procese[i].pid == pData->procese[root].ppid && i != root) {
					root = i;
					done = false;
				}
		}
		printf("Arbore nr %d cu parintele cu PID: %d\n", ++treeCount, pData->procese[root].pid);
		displayProcess(pData, root, 0);
	}

	CloseHandle(handle);
	return pData;
	/*numberOfProcesses = printf("%d\n", ((int*)pData)[0]);
	pData += sizeof(DWORD);
	PROCESSENTRY32 pe32;
	for (int i = 0; i < numberOfProcesses; ++i) {
		pe32 = *pData;
		pData += sizeof
			continue;
		parentProcessID = *((int*)pData);
		pData += sizeof(DWORD);

		processID = *((int*)pData);
		pData += sizeof(DWORD);

		exeName[0] = NULL;
		int j = 0;
		while (*pData != '\n') {
			exeName[j] = *pData;
			++pData;
			++j;
		}
		exeName[j] = NULL;

		printf("<%d><%d><%s>\n", parentProcessID, processID, exeName);
	}*/
}

HANDLE getMappedFileHandle() {
	return OpenFileMapping(PAGE_READONLY, false, "processes");
}