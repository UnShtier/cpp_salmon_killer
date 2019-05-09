#include <iostream>
#include <windows.h>
#include "NTFS_HS.h"
#include <list>
#pragma once
#pragma pack(push, 1)
#define NTFS 1
#define Unknown 0

typedef struct
{
	BYTE Padding1[3];
	BYTE OEM_ID[8];
} BootRecord;

class FSHandler
{
private:
	HANDLE hdl;
	BYTE *firstSector;
	int fileSystemType;
	WCHAR volume[MAX_PATH];
	DWORD error;
	DWORD lastOffset;
	DWORD lastReturnBytesCount;
	DISK_GEOMETRY dg;


public:
	FSHandler();
	~FSHandler();
	void GetVolumesInfo();
	HANDLE CreateHandle(WCHAR *volumeName);
	BYTE* ReadBytes(HANDLE &hd, ULONGLONG &offset, DWORD &bytes);
	BYTE* ReadBytes(ULONGLONG &offset, DWORD &bytes);
	DWORD GetSectorSize(HANDLE hd);
	int RecogniseFileSystem(BYTE *buffer);
	ULONGLONG GetSectorsCount();
	DWORD GetLastReturnBytesCount();
	DWORD GetSectorSize();
};

