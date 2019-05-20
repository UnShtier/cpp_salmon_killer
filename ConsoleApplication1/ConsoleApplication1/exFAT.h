#pragma once
#include "FileSystemV.h"
#pragma pack(push, 1)

typedef struct {
	BYTE Padding1[3];
	BYTE OEM_ID[8];
	BYTE Padding2[53];
	ULONGLONG PARTITION_OFFSET;
	ULONGLONG SECTORS_COUNT;
	DWORD FAT_OFFSET;
	DWORD FAT_LENGTH;
	BYTE Padding3[128];
	WORD BYTES_PER_SECTOR_POWER;
	WORD SECTORS_PER_CLUSTER_POWER;

} exFAT_BootRecord;

class exFAT :
	public FileSystemV
{
private:
	ULONGLONG PARTITION_OFFSET;
	DWORD FAT_OFFSET;
	DWORD FAT_LENGTH;
public:
	exFAT(HANDLE hd);
	void WriteFSData();
};

