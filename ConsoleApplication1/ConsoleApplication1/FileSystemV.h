#pragma once
#include <windows.h>
#include <iostream>
#pragma pack(push, 1)

typedef struct
{
	BYTE Padding1[3];
	BYTE OEM_ID[8];
} OEM_record;

class FileSystemV
{
protected:
	HANDLE FS_HANDLE;
	BYTE OEM_ID[8];
	WORD BYTES_PER_SECTOR;
	WORD SECTOR_PER_CLUSTER;
	WORD RESERVED_SECTORS;
	ULONGLONG TOTAL_SECTORS;
	ULONGLONG TOTAL_CLUSTERS;
public:
	FileSystemV();
	FileSystemV(HANDLE hd);
	~FileSystemV();
	virtual void WriteFSData() = 0;
	ULONGLONG GetSectorsCount();
	ULONGLONG GetClusterCount();
	DWORD GetSectorPerClusterCount();
	DWORD GetSectorSize();
	BYTE *GetOEM_ID();
	static BYTE *ReadOEM_ID(HANDLE hd);
	BYTE *GetSectorBytes(DWORD &sectorsCount, ULONGLONG &offsetSector);
	BYTE *GetClusterBytes(DWORD clusterCount, ULONGLONG clusterOffset);
};

