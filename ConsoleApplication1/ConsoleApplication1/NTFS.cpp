#include "NTFS.h"




NTFS::NTFS(HANDLE hd)
{
	this->FS_HANDLE = hd;
	DWORD sectorsCount = 1;
	ULONGLONG offsetSector = 0;
	BYTE *buffer = GetSectorBytes(sectorsCount, offsetSector);
	NTFS_BootRecord *NBR = (NTFS_BootRecord*)buffer;
	memcpy(this->OEM_ID, NBR->OEM_ID, sizeof(this->OEM_ID));
	this->BYTES_PER_SECTOR = NBR->BYTES_PER_SECTOR;
	this->SECTOR_PER_CLUSTER = NBR->SECTOR_PER_CLUSTER;
	this->RESERVED_SECTORS = NBR->RESERVED_SECTORS;
	this->TOTAL_SECTORS = NBR->TOTAL_SECTORS;
	this->TOTAL_CLUSTERS = this->TOTAL_SECTORS / this->SECTOR_PER_CLUSTER;
}


void NTFS::WriteFSData() {
	std::cout << "OEM_ID: " << OEM_ID << std::endl;
	std::cout << "Bytes per sector: " << BYTES_PER_SECTOR << std::endl;
	std::cout << "Sectors per cluster: " << SECTOR_PER_CLUSTER << std::endl;
	std::cout << "Reserved sectors: " << RESERVED_SECTORS << std::endl;
	std::cout << "Total sectors: " << TOTAL_SECTORS << std::endl;
	std::cout << "Total volume: " << TOTAL_SECTORS / 2 / 1024 << std::endl;
}
