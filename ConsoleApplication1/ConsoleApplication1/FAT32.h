#pragma once
#include "FileSystemV.h"
#pragma pack(push, 1)


typedef struct {
	BYTE Padding1[3];
	BYTE OEM_ID[8];
	WORD BYTES_PER_SECTOR;
	BYTE SECTOR_PER_CLUSTER;
	WORD RESERVED_SECTORS;
	BYTE NUMBER_OF_FATS;
	WORD ROOT_ENTRIES;
	WORD SMALL_SECTORS_COUNT;
	BYTE Padding2[11];
	DWORD BIG_SECTORS_COUNT;
} FAT32_BootRecord;


class FAT32 :
	public FileSystemV
{
private:
	BYTE NUMBER_OF_FATS;
	WORD ROOT_ENTRIES;
public:
	FAT32(HANDLE hd);
	void WriteFSData();
};

