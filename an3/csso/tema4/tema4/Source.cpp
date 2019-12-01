#include <Windows.h>
#pragma comment(lib, "Wininet")
#include <WinInet.h>
#include <stdio.h>

void getInstructions(HINTERNET);
HINTERNET initialise();


int main() {
	HANDLE hInternetOpen = initialise();
	if (hInternetOpen == NULL) {
		printf("hInternetOpen could not be created: %d\n", GetLastError());
		return -1;
	}
	getInstructions(hInternetOpen);

	InternetCloseHandle(hInternetOpen);
	return 0;
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
	
	hHTTPRequest = HttpOpenRequest(hInternetConnect, "GET", "~sergiu.iacob", "1.1", "www.google.com", NULL, NULL, NULL);
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
	catch (...){
		printf("Exception!");
		return;
	}

	char buffer[1024 * 1024];
	DWORD totalRead = 0;
	/*if (InternetReadFile(hHTTPRequest, buffer, DWORD(1024), &totalRead) == false) {
		printf("Could not read file: %d\n", GetLastError());
		return;
	}

	printf("Am citit: %s\n", buffer);

	*/
	InternetCloseHandle(hHTTPRequest);
	InternetCloseHandle(hInternetConnect);

}