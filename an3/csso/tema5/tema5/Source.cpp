#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <aclapi.h>
#include <tchar.h>
#include <iostream>
#include <sddl.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

SECURITY_ATTRIBUTES createSecurityAttributes(PSECURITY_DESCRIPTOR);
PSECURITY_DESCRIPTOR createSecurityDescriptor();
DWORD createRegExKey(SECURITY_ATTRIBUTES&);

HKEY hKey;
const char* regPath = "Software\\CSSO\\Tema5";

int main()
{
	PSECURITY_DESCRIPTOR securityDescriptor;
	SECURITY_ATTRIBUTES securityAttributes;

	try {
		securityDescriptor = createSecurityDescriptor();
		if (securityDescriptor == NULL)
			return -1;
		securityAttributes = createSecurityAttributes(securityDescriptor);
	}
	catch (char* error) {
		printf("%s: %d\n", error, GetLastError());
		return -2;
	}

	DWORD regExResult = createRegExKey(securityAttributes);
	if (regExResult != 0) {
		printf("Failed to create RegEx key: %d\n", regExResult);
		return -3;
	}
	return 0;
}

SECURITY_ATTRIBUTES createSecurityAttributes(PSECURITY_DESCRIPTOR pSecurityDescriptor) {
	SECURITY_ATTRIBUTES sAttr;
	sAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	sAttr.lpSecurityDescriptor = pSecurityDescriptor;
	sAttr.bInheritHandle = FALSE;
	return sAttr;
}


PSECURITY_DESCRIPTOR createSecurityDescriptor() {
	// setez ownerul, care trebuie sa fie current user
	// vad cine e current user
	//char currentUserName[256];
	//DWORD currentUserNameLength = sizeof(currentUserName);
	//BYTE sidbuf[SECURITY_MAX_SID_SIZE];
	//PSID currentUserSid = (PSID) new BYTE[SECURITY_MAX_SID_SIZE];
	//DWORD dwSidSize = SECURITY_MAX_SID_SIZE;
	//LPSTR* currentUserSidString = new LPSTR[512];
	//SID_NAME_USE snu;
	//DWORD domainSize = 0;
	//PSID psid;
	//memset(currentUserSid, 0, dwSidSize);

	DWORD dwSIDSize = SECURITY_MAX_SID_SIZE;
	PSID adminSID = (PSID) new BYTE[dwSIDSize];
	PSID publicSID = (PSID) new BYTE[dwSIDSize];

	PSECURITY_DESCRIPTOR securityDescriptor = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
	if (!InitializeSecurityDescriptor(securityDescriptor, SECURITY_DESCRIPTOR_REVISION))
		throw "InitializeSecurityDescriptor failed";

	if (!CreateWellKnownSid(WinBuiltinAdministratorsSid, NULL, adminSID, &dwSIDSize)) {
		printf("CreateWellKnownSid1 failed: %d\n", GetLastError());
		return NULL;
	}
	if (!CreateWellKnownSid(WinWorldSid, NULL, publicSID, &dwSIDSize)) {
		printf("CreateWellKnownSid2 failed: %d\n", GetLastError());
		return NULL;
	}

	/*if (!SetSecurityDescriptorOwner(securityDescriptor, &adminSID, FALSE)) {
		printf("SetSecurityDescriptorOwner failed: %d\n", GetLastError());
		return NULL;
	}

	if (!SetSecurityDescriptorGroup(securityDescriptor, &publicSID, FALSE)) {
		printf("SetSecurityDescriptorOwner failed: %d\n", GetLastError());
		return NULL;
	}*/


	EXPLICIT_ACCESS ea[2];
	memset(ea, 0, sizeof(ea));

	ea[0].grfAccessPermissions = KEY_ALL_ACCESS;
	ea[0].grfAccessMode = SET_ACCESS;
	ea[0].grfInheritance = NO_INHERITANCE;
	ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea[0].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
	ea[0].Trustee.ptstrName = (LPTSTR)adminSID;

	ea[1].grfAccessPermissions = KEY_READ;
	ea[1].grfAccessMode = SET_ACCESS;
	ea[1].grfInheritance = NO_INHERITANCE;
	ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea[1].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea[1].Trustee.ptstrName = (LPTSTR)publicSID;

	PACL pAcl = NULL;
	DWORD result = SetEntriesInAcl(2, ea, NULL, &pAcl);
	if (result != ERROR_SUCCESS) {
		printf("SetEntriesInAcl failed: %d\n", result);
		return NULL;
	}

	//SET DACL
	if (!SetSecurityDescriptorDacl(securityDescriptor, TRUE, pAcl, FALSE)) {
		printf("SetSecurityDescriptorDacl failed: %d\n", GetLastError());
		return 0;
	}


	/*if (!GetUserName(currentUserName, &currentUserNameLength)) {
		printf("GetUserName failed: %d\n", GetLastError());
		return NULL;
	}
	printf("Current user name is: %s\n", currentUserName);

	if (!LookupAccountNameW(NULL, LPCWSTR(currentUserName), &currentUserSid, &dwSidSize, NULL, &domainSize, &snu)) {
		printf("LookupAccountName failed: %d\n", GetLastError());
		return NULL;
	}
	if (!ConvertSidToStringSid(&currentUserSid, currentUserSidString)) {
		printf("ConvertSidToStringSid failed: %d\n", GetLastError());
		return NULL;
	}
	cout << "Current user SID is: " << currentUserSidString << '\n';

	SID_IDENTIFIER_AUTHORITY creator = SECURITY_CREATOR_SID_AUTHORITY;
	PSID ownerPSID;
	if (!AllocateAndInitializeSid(&creator, 1, 0, 0, 0, 0, 0, 0, 0, 0, &ownerPSID)) {
		printf("AllocateAndInitializeSid failed: %d\n", GetLastError());
		return NULL;
	}

	if (!SetSecurityDescriptorOwner(securityDescriptor, &psid, FALSE)) {
		printf("SetSecurityDescriptorOwner failed: %d\n", GetLastError());
		return NULL;
	}*/

	return securityDescriptor;
}

DWORD createRegExKey(SECURITY_ATTRIBUTES& securityAttributes) {
	DWORD disposition = 0;
	return RegCreateKeyEx(
		HKEY_CURRENT_USER,
		regPath,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_READ,
		&securityAttributes,
		&hKey,
		&disposition);
}
