#include "FAT32.h"




FAT32::FAT32(HANDLE hd)
{
	this->FS_HANDLE = hd;
	DWORD sectorsCount = 1;
	ULONGLONG offsetSector = 0;
	BYTE *buffer = GetSectorBytes(sectorsCount, offsetSector);
	FAT32_BootRecord *NBR = (FAT32_BootRecord*)buffer;
	memcpy(this->OEM_ID, NBR->OEM_ID, sizeof(this->OEM_ID));
	this->BYTES_PER_SECTOR = NBR->BYTES_PER_SECTOR;
	this->SECTOR_PER_CLUSTER = NBR->SECTOR_PER_CLUSTER;
	this->NUMBER_OF_FATS = NBR->NUMBER_OF_FATS;
	this->ROOT_ENTRIES = NBR->ROOT_ENTRIES;
	this->RESERVED_SECTORS = NBR->RESERVED_SECTORS;
	if (NBR->SMALL_SECTORS_COUNT != 0)
	{
		this->TOTAL_SECTORS = NBR->SMALL_SECTORS_COUNT;
	}
	else
	{
		this->TOTAL_SECTORS = NBR->BIG_SECTORS_COUNT;
	}
	this->TOTAL_CLUSTERS = this->TOTAL_SECTORS / this->SECTOR_PER_CLUSTER;
}


void FAT32::WriteFSData()
{
	std::cout << "OEM_ID: " << OEM_ID << std::endl;
	std::cout << "Bytes per sector: " << BYTES_PER_SECTOR << std::endl;
	std::cout << "Sectors per cluster: " << SECTOR_PER_CLUSTER << std::endl;
	std::cout << "Reserved sectors: " << RESERVED_SECTORS << std::endl;
	std::cout << "Number of file allocation tables: " << NUMBER_OF_FATS << std::endl;
	std::cout << "Max number of file name entries in /: " << ROOT_ENTRIES << std::endl;
	std::cout << "Total sectors: " << TOTAL_SECTORS << std::endl;
	std::cout << "Total volume: " << TOTAL_SECTORS / 2 / 1024 << std::endl;
}
