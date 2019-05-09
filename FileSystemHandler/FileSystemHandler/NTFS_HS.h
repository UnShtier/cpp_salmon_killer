#pragma once
#include <windows.h>
#include <iostream>
#pragma pack(push, 1)


typedef struct
{
	BYTE Padding1[3];
	BYTE OEM_ID[8];
	WORD BYTES_PER_SECTOR;
	WORD SECTOR_PER_CLUSTER;
	WORD RESERVED_SECTORS;
	BYTE Padding2[26];
	ULONGLONG TOTAL_SECTORS;
} NTFS_BootRecord;

#pragma pack(pop)

class NTFS_HS
{
private:
	HANDLE FS_HANDLE;
	BYTE OEM_ID[8];
	WORD BYTES_PER_SECTOR;
	WORD SECTOR_PER_CLUSTER;
	WORD RESERVED_SECTORS;
	ULONGLONG TOTAL_SECTORS;
	ULONGLONG TOTAL_CLUSTERS;

public:
	NTFS_HS();
	NTFS_HS(HANDLE FS_HANDLE, BYTE *buffer);
	~NTFS_HS();
	void PrintData();
	ULONGLONG GetSectorsCount();
	DWORD GetSectorSize();
};

