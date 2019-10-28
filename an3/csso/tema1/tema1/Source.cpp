#include <Windows.h>
#include <stdio.h>
#include <Strsafe.h>
#include <Pathcch.h>
#include <Shlwapi.h>
#include <fileapi.h>
#define MAX_PATH_LENGTH 1024

LPCSTR pathToDirectoryParent = "C:\\Users\\sergiu\\Desktop";
LPCSTR HKEYPrefix = "Software\\CSSO\\";


void listFiles(LPCSTR);
bool isDirectory(WIN32_FIND_DATA);
void createRegistryForFile(LPCSTR, LPCSTR);
void unifyPaths(LPSTR, LPCSTR, LPCSTR, bool starAtTheEnd = true);
LARGE_INTEGER getFileSize(LPCSTR, LPCSTR);

int main() {
	listFiles("dir");
	return 0;
}

void listFiles(LPCSTR pathSuffix) {
	WIN32_FIND_DATA ffd;
	HANDLE hFile;
	LPSTR currentPath = new char[MAX_PATH_LENGTH];

	unifyPaths(currentPath, pathToDirectoryParent, pathSuffix);
	printf("Currently in: %s\n", currentPath);

	hFile = FindFirstFileA(currentPath, &ffd);
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("Could not acquire handle for %s\n", currentPath);
		return;
	}
	do {
		if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
			continue;
		if (isDirectory(ffd)) {
			LPSTR newPath = new char[MAX_PATH_LENGTH];
			unifyPaths(newPath, pathSuffix, ffd.cFileName, false);

			listFiles((LPCSTR)newPath);
			//PathCchCombine(newPath, 0, NULL, NULL);
			//PathCchCombine((PWSTR)newPath, MAX_PATH_LENGTH, (PCWSTR)currentPath, (PCWSTR)ffd.cFileName);
			//PathCombineA(newPath, currentPath, ffd.cFileName);
			//printf("new path: %s\n", (LPCSTR)newPath);
		}
		else
			createRegistryForFile(pathSuffix, ffd.cFileName);
	} while (FindNextFileA(hFile, &ffd));

	FindClose(hFile);
}

void unifyPaths(LPSTR newPath, LPCSTR path1, LPCSTR path2, bool starAtTheEnd) {
	// copy without the * at the end

	size_t len = strlen(path1);
	if (len > 0) {
		if (path1[len - 1] == '*')
			--len;

		StringCchCopyN(newPath, MAX_PATH_LENGTH, path1, len);
		if (newPath[strlen(newPath) - 1] != '\\')
			StringCchCat(newPath, MAX_PATH_LENGTH, "\\");
	}
	else {
		StringCchCopy(newPath, MAX_PATH_LENGTH, "");
	}

	len = strlen(path2);
	if (path2[len - 1] == '\\')
		--len;
	// append the second string without '\' at the end
	StringCchCatN(newPath, MAX_PATH_LENGTH, path2, len);
	if (starAtTheEnd == true) {
		if (newPath[strlen(newPath) - 1] == '\\')
			StringCchCat(newPath, MAX_PATH_LENGTH, "*");
		else
			StringCchCat(newPath, MAX_PATH_LENGTH, "\\*");
	}
}

void createRegistryForFile(LPCSTR path, LPCSTR fileName) {
	LPSTR filePath = new char[MAX_PATH_LENGTH];
	LPSTR regPath = new char[MAX_PATH_LENGTH];
	unifyPaths(regPath, HKEYPrefix, path);
	if (regPath[strlen(regPath) - 1] == '*')
		regPath[strlen(regPath) - 1] = 0;


	printf("Creating registry %s in %s\n", fileName, regPath);

	HKEY hKey;
	DWORD disposition = 0;
	if (RegCreateKeyEx(
		HKEY_CURRENT_USER,
		regPath,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		NULL,
		&hKey,
		&disposition) != ERROR_SUCCESS) {
		printf("Nu s-a putut creea cheia. Cod eroare: %d\n", GetLastError());
		return;
	}

	LARGE_INTEGER size = getFileSize(path, fileName);
	RegSetValueEx(
		hKey,
		fileName,
		0,
		REG_QWORD,
		(const BYTE*)&size,
		sizeof(LARGE_INTEGER));

	RegCloseKey(hKey);
}

LARGE_INTEGER getFileSize(LPCSTR relativePathToFile, LPCSTR fileName) {
	LARGE_INTEGER fileSize;
	HANDLE hFile;

	LPSTR filePath = new char[MAX_PATH_LENGTH];
	unifyPaths(filePath, pathToDirectoryParent, relativePathToFile, false);
	unifyPaths(filePath, filePath, fileName, false);

	hFile = CreateFile(
		filePath,               // lpFileName
		GENERIC_READ,           // dwDesiredAccess
		0,                      // dwShareMode
		NULL,                   // lpSecurityAttributes
		OPEN_EXISTING,          // dwCreationDisposition
		FILE_ATTRIBUTE_NORMAL,  // dwFlagsAndAttributes
		INVALID_HANDLE_VALUE);  // hTemplateFile
	if (hFile == INVALID_HANDLE_VALUE)
		printf("Cannot open file. Error code: %d", GetLastError());

	GetFileSizeEx(hFile, &fileSize);
	printf("File size for %s is %ld\n", filePath, fileSize);
	return fileSize;
}

bool isDirectory(WIN32_FIND_DATA ffd) {
	return (ffd.dwFileAttributes) & FILE_ATTRIBUTE_DIRECTORY;
}