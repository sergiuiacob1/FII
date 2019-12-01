#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#pragma comment(lib, "Wininet")
#include <WinInet.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

char buffer[1024 * 1024];
vector<string> instructions;

void getInstructions(HINTERNET);
HINTERNET initialise();
void parseInstructions();
void executeInstructions(HINTERNET);
void executePUTInstruction(HINTERNET, string);
void executeRUNInstruction(HINTERNET, string);

int main() {
	HINTERNET hInternetOpen = initialise();
	if (hInternetOpen == NULL) {
		printf("hInternetOpen could not be created: %d\n", GetLastError());
		return -1;
	}
	getInstructions(hInternetOpen);
	parseInstructions();
	executeInstructions(hInternetOpen);

	InternetCloseHandle(hInternetOpen);
	return 0;
}

void executeInstructions(HINTERNET hInternetOpen) {
	HINTERNET hInternetConnect = InternetConnect(hInternetOpen, instructions[1].c_str(), INTERNET_DEFAULT_FTP_PORT, instructions[2].c_str(), instructions[3].c_str(), INTERNET_SERVICE_FTP, 0, 0);
	if (hInternetConnect == NULL) {
		cout << "Could not create hInternetConnect for FTP server: " << GetLastError() << "\n";
		return;
	}


	int no = stoi(instructions[0]);
	for (int i = 4; i < 4 + no; ++i) {
		if (instructions[i].find("PUT") == 0)
			executePUTInstruction(hInternetConnect, instructions[i]);
		else
			executeRUNInstruction(hInternetConnect, instructions[i]);
	}
}

void executePUTInstruction(HINTERNET hInternetConnect, string instruction) {
	char path[256], fileName[256], errorBuffer[1024];
	DWORD no, read;
	strcpy(path, instruction.substr(strlen("PUT ")).c_str());
	strcpy(fileName, instruction.substr(instruction.rfind("\\") + 1).c_str());

	cout << "Uploading " << path << " to FTP server as " << fileName << "\n";

	if (FtpPutFile(hInternetConnect, path, fileName, INTERNET_FLAG_TRANSFER_BINARY, NULL) == false) {
		printf("Could not upload file to FTP server: %d\n", GetLastError());

		if (GetLastError() == 12003) {
			InternetGetLastResponseInfo(&no, errorBuffer, &read);
			cout << errorBuffer << "\n";
			return;
		}
	}
}

void executeRUNInstruction(HINTERNET hInternetConnect, string instruction) {
	char fileName[256], currentDirectory[256], fullPath[512], errorBuffer[1024];
	DWORD no, read;
	strcpy(fileName, instruction.substr(strlen("RUN ")).c_str());
	// descarc fisierul local
	if (FtpGetFile(hInternetConnect, fileName, fileName, false, NULL, FTP_TRANSFER_TYPE_BINARY, NULL) == false) {
		cout << "Could not download " << fileName << ": " << GetLastError() << "\n";

		if (GetLastError() == 12003) {
			InternetGetLastResponseInfo(&no, errorBuffer, &read);
			cout << errorBuffer << "\n";
			return;
		}
		return;
	}

	if (GetCurrentDirectory(strlen(fullPath), fullPath) == 0) {
		cout << "GetCurrentDirectory failed: " << GetLastError() << "\n";
		return;
	}
	strcat(fullPath, "\\");
	strcat(fullPath, fileName);


	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);

	if (!CreateProcess(fullPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		cout << "CreateProcess failed: " << GetLastError() << "\n";
		return;
	}

}

HINTERNET initialise() {
	return InternetOpen("internet_open", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
}

void getInstructions(HINTERNET hInternetOpen) {
	HINTERNET hInternetConnect, hHTTPRequest;
	//hInternetConnect = InternetOpenUrl(hInternetOpen, "http://students.info.uaic.ro", NULL, NULL, NULL, NULL);
	hInternetConnect = InternetConnect(hInternetOpen, "students.info.uaic.ro", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);
	if (hInternetConnect == NULL) {
		printf("hInternetConnect could not be created: %d\n", GetLastError());
		return;
	}

	hHTTPRequest = HttpOpenRequest(hInternetConnect, "GET", "~sergiu.iacob/instructions.txt", "1.1", "www.google.com", NULL, NULL, NULL);
	if (hHTTPRequest == NULL) {
		printf("hHTTPRequest could not be created: %d\n", GetLastError());
		return;
	}

	try {
		if (HttpSendRequest(hHTTPRequest, NULL, NULL, NULL, NULL) == false) {
			printf("Could not send HTTP Request: %d\n", GetLastError());
			return;
		}
	}
	catch (...) {
		printf("Exception on HttpSendRequest");
		return;
	}

	DWORD totalRead = 0;
	if (InternetReadFile(hHTTPRequest, buffer, DWORD(1024), &totalRead) == false) {
		printf("Could not read file: %d\n", GetLastError());
		return;
	}

	InternetCloseHandle(hHTTPRequest);
	InternetCloseHandle(hInternetConnect);
}

void parseInstructions() {
	string str = buffer;

	instructions.clear();

	std::size_t current, previous = 0;
	current = str.find("\n");
	while (current != std::string::npos) {
		instructions.push_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find("\n", previous);
	}
	instructions.push_back(str.substr(previous, current - previous));
}