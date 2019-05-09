#include "NTFS_HS.h"

NTFS_HS::NTFS_HS()
{
	FS_HANDLE = 0;
	OEM_ID[8] = { 0 };
	BYTES_PER_SECTOR = 0;
	SECTOR_PER_CLUSTER = 0;
	RESERVED_SECTORS = 0;
	TOTAL_SECTORS = 0;
	TOTAL_CLUSTERS = 0;
}

NTFS_HS::NTFS_HS(HANDLE FS_HANDLE, BYTE *buffer)
{
	this->FS_HANDLE = FS_HANDLE;
	NTFS_BootRecord *NBR = (NTFS_BootRecord*)buffer;
	memcpy(this->OEM_ID, NBR->OEM_ID, sizeof(this->OEM_ID));
	this->BYTES_PER_SECTOR = NBR->BYTES_PER_SECTOR;
	this->SECTOR_PER_CLUSTER = NBR->SECTOR_PER_CLUSTER;
	this->RESERVED_SECTORS = NBR->RESERVED_SECTORS;
	this->TOTAL_SECTORS = NBR->TOTAL_SECTORS;
	this->TOTAL_CLUSTERS = this->TOTAL_SECTORS / this->SECTOR_PER_CLUSTER;
}


NTFS_HS::~NTFS_HS()
{
	//CloseHandle(FS_HANDLE);
}

void NTFS_HS::PrintData() {
	std::cout << "OEM_ID: " << OEM_ID << std::endl;
	std::cout << "Bytes per sector: " << BYTES_PER_SECTOR << std::endl;
	std::cout << "Sectors per cluster: " << SECTOR_PER_CLUSTER << std::endl;
	std::cout << "Reserved sectors: " << RESERVED_SECTORS << std::endl;
	std::cout << "Total sectors: " << TOTAL_SECTORS << std::endl;
	std::cout << "Total volume: " << TOTAL_SECTORS / 2 / 1024 << std::endl;
}

ULONGLONG NTFS_HS::GetSectorsCount() {
	return this->TOTAL_SECTORS;
}

DWORD NTFS_HS::GetSectorSize() {
	return this->BYTES_PER_SECTOR;
}