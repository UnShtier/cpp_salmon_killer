#include "FileSystemV.h"



FileSystemV::FileSystemV(HANDLE hd)
{
	FS_HANDLE = hd;
	BYTE OEM_ID[8] = { 0 };
	WORD BYTES_PER_SECTOR = 0;
	WORD SECTOR_PER_CLUSTER = 0;
	WORD RESERVED_SECTORS = 0;
	ULONGLONG TOTAL_SECTORS = 0;
	ULONGLONG TOTAL_CLUSTERS = 0;
}

FileSystemV::FileSystemV()
{
	FS_HANDLE = 0;
	BYTE OEM_ID[8] = { 0 };
	WORD BYTES_PER_SECTOR = 0;
	WORD SECTOR_PER_CLUSTER = 0;
	WORD RESERVED_SECTORS = 0;
	ULONGLONG TOTAL_SECTORS = 0;
	ULONGLONG TOTAL_CLUSTERS = 0;
}

FileSystemV::~FileSystemV()
{
	CloseHandle(FS_HANDLE);
}


ULONGLONG FileSystemV::GetSectorsCount()
{
	return TOTAL_SECTORS;
}


DWORD FileSystemV::GetSectorSize()
{
	return BYTES_PER_SECTOR;
}


ULONGLONG FileSystemV::GetClusterCount()
{
	return TOTAL_CLUSTERS;
}


DWORD FileSystemV::GetSectorPerClusterCount()
{
	return SECTOR_PER_CLUSTER;
}


BYTE *FileSystemV::GetOEM_ID()
{
	return OEM_ID;
}


BYTE *FileSystemV::GetSectorBytes(DWORD &sectorsCount, ULONGLONG &offsetSector)
{
	LARGE_INTEGER oft;
	DWORD multiplyer = 0;
	if (BYTES_PER_SECTOR % 512 != 0 or BYTES_PER_SECTOR == 0)
	{ 
		multiplyer = 512;
	}
	else
	{
		multiplyer = BYTES_PER_SECTOR;
	}
	oft.QuadPart = offsetSector * multiplyer;
	DWORD bytes = sectorsCount * multiplyer;
	BYTE *buf = new BYTE[bytes];
	DWORD lastOffset = 0;
	DWORD error = 0;
	lastOffset = SetFilePointer(FS_HANDLE, oft.LowPart, &oft.HighPart, FILE_BEGIN);
	if (lastOffset != oft.LowPart) {
		error = GetLastError();
		exit(error);
	}
	DWORD returnedBytesCount = 0;
	bool readResult = ReadFile(FS_HANDLE, buf, bytes, &returnedBytesCount, NULL);
	if (!readResult || returnedBytesCount != bytes) {
		error = GetLastError();
		exit(error);
	}
	return buf;
}


BYTE *FileSystemV::ReadOEM_ID(HANDLE hd)
{
	LARGE_INTEGER oft;
	oft.QuadPart = 0;
	BYTE *buf = new BYTE[512];
	DWORD lastOffset = 0;
	DWORD error = 0;
	lastOffset = SetFilePointer(hd, oft.LowPart, &oft.HighPart, FILE_BEGIN);
	if (lastOffset != oft.LowPart) {
		error = GetLastError();
		exit(error);
	}
	DWORD returnedBytesCount = 0;
	bool readResult = ReadFile(hd, buf, 512, &returnedBytesCount, NULL);
	if (!readResult || returnedBytesCount != 512) {
		error = GetLastError();
		exit(error);
	}
	OEM_record *rc = (OEM_record*)buf;
	return rc->OEM_ID;
}


BYTE *FileSystemV::GetClusterBytes(DWORD clusterCount, ULONGLONG clusterOffset)
{
	DWORD sc = clusterCount * SECTOR_PER_CLUSTER;
	ULONGLONG os = clusterOffset * SECTOR_PER_CLUSTER;
	return GetSectorBytes(sc, os);
}
