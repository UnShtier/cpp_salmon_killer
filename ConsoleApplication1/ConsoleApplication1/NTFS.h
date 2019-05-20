#pragma once
#include "FileSystemV.h"
#pragma pack(push, 1)

typedef struct
{
	BYTE Padding1[3];
	BYTE OEM_ID[8];
	WORD BYTES_PER_SECTOR;
	BYTE SECTOR_PER_CLUSTER;
	WORD RESERVED_SECTORS;
	BYTE Padding2[24];
	ULONGLONG TOTAL_SECTORS;
} NTFS_BootRecord;

class NTFS :
	public FileSystemV
{
public:
	NTFS(HANDLE hd);
	void WriteFSData();
};

