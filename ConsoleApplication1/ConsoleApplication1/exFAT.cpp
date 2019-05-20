#include "exFAT.h"



exFAT::exFAT(HANDLE hd)
{
	this->FS_HANDLE = hd;
	DWORD sectorsCount = 1;
	ULONGLONG offsetSector = 0;
	BYTE *buffer = GetSectorBytes(sectorsCount, offsetSector);
	exFAT_BootRecord *NBR = (exFAT_BootRecord*)buffer;
	memcpy(this->OEM_ID, NBR->OEM_ID, sizeof(this->OEM_ID));
	this->BYTES_PER_SECTOR = 2;
	this->PARTITION_OFFSET = NBR->PARTITION_OFFSET;
	this->FAT_OFFSET = NBR->FAT_OFFSET;
	this->FAT_LENGTH = NBR->FAT_LENGTH;
	for (int i = 0; i < NBR->BYTES_PER_SECTOR_POWER; i++)
	{
		this->BYTES_PER_SECTOR = this->BYTES_PER_SECTOR * this->BYTES_PER_SECTOR;
	}
	this->SECTOR_PER_CLUSTER = 2;
	for (int i = 0; i < NBR->SECTORS_PER_CLUSTER_POWER; i++)
	{
		this->SECTOR_PER_CLUSTER = this->SECTOR_PER_CLUSTER * this->SECTOR_PER_CLUSTER;
	}
	this->RESERVED_SECTORS = 0;
	this->TOTAL_SECTORS = NBR->SECTORS_COUNT;
	this->TOTAL_CLUSTERS = this->TOTAL_SECTORS / this->SECTOR_PER_CLUSTER;
}



void exFAT::WriteFSData()
{
	std::cout << "OEM_ID: " << OEM_ID << std::endl;
	std::cout << "Bytes per sector: " << BYTES_PER_SECTOR << std::endl;
	std::cout << "Sectors per cluster: " << SECTOR_PER_CLUSTER << std::endl;
	std::cout << "Reserved sectors: " << RESERVED_SECTORS << std::endl;
	std::cout << "Partition offset: " << PARTITION_OFFSET << std::endl;
	std::cout << "FAT offset: " << FAT_OFFSET << std::endl;
	std::cout << "Length of FAT: " << FAT_LENGTH << std::endl;
	std::cout << "Total sectors: " << TOTAL_SECTORS << std::endl;
	std::cout << "Total volume: " << TOTAL_SECTORS / 2 / 1024 << std::endl;
}