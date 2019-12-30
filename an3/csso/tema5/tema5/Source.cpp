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
	PSID creatorGroupSID = (PSID) new BYTE[dwSIDSize];
	PSID publicSID = (PSID) new BYTE[dwSIDSize];

	PSECURITY_DESCRIPTOR securityDescriptor = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
	if (!InitializeSecurityDescriptor(securityDescriptor, SECURITY_DESCRIPTOR_REVISION))
		throw "InitializeSecurityDescriptor failed";

	if (!CreateWellKnownSid(WinCreatorGroupSid, NULL, creatorGroupSID, &dwSIDSize)) {
		printf("CreateWellKnownSid1 failed: %d\n", GetLastError());
		return NULL;
	}
	if (!CreateWellKnownSid(WinWorldSid, NULL, publicSID, &dwSIDSize)) {
		printf("CreateWellKnownSid2 failed: %d\n", GetLastError());
		return NULL;
	}


	EXPLICIT_ACCESS explicitAccess[2];
	memset(explicitAccess, 0, sizeof(explicitAccess));

	explicitAccess[0].grfAccessPermissions = KEY_ALL_ACCESS;
	explicitAccess[0].grfAccessMode = SET_ACCESS;
	explicitAccess[0].grfInheritance = NO_INHERITANCE;
	explicitAccess[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	explicitAccess[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	explicitAccess[0].Trustee.ptstrName = (LPTSTR)creatorGroupSID;

	explicitAccess[1].grfAccessPermissions = KEY_READ;
	explicitAccess[1].grfAccessMode = SET_ACCESS;
	explicitAccess[1].grfInheritance = NO_INHERITANCE;
	explicitAccess[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	explicitAccess[1].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	explicitAccess[1].Trustee.ptstrName = (LPTSTR)publicSID;

	PACL pAcl = NULL;
	DWORD result = SetEntriesInAcl(2, explicitAccess, NULL, &pAcl);
	if (result) {
		printf("SetEntriesInAcl failed: %d\n", result);
		return NULL;
	}

	if (!SetSecurityDescriptorDacl(securityDescriptor, TRUE, pAcl, FALSE)) {
		printf("SetSecurityDescriptorDacl failed: %d\n", GetLastError());
		return 0;
	}


	/*if (!SetSecurityDescriptorOwner(securityDescriptor, &creatorGroupSID, FALSE)) {
		printf("SetSecurityDescriptorOwner failed: %d\n", GetLastError());
		return NULL;
	}
	/*
	if (!SetSecurityDescriptorGroup(securityDescriptor, &creatorGroupSID, FALSE)) {
		printf("SetSecurityDescriptorOwner failed: %d\n", GetLastError());
		return NULL;
	}*/

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
		LPCSTR("Software\\CSSO"),
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_WOW64_32KEY && KEY_ALL_ACCESS,
		&securityAttributes,
		&hKey,
		&disposition);
}
