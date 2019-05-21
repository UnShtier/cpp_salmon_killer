#include "FileSystemHandler.h"



FileSystemHandler::FileSystemHandler()
{
	this->hd = { 0 };
	this->volume[MAX_PATH] = { NULL };
	this->fs = { 0 };
}


FileSystemHandler::FileSystemHandler(HANDLE hd)
{
	this->hd = hd;
	FSFactoryMethod();
}


FileSystemHandler::~FileSystemHandler()
{
	CloseHandle(hd);
}


HANDLE FileSystemHandler::CreateHandle(WCHAR * name) {
	HANDLE hd = CreateFileW(name, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hd == INVALID_HANDLE_VALUE) {
		CloseHandle(hd);
		exit(GetLastError());
	}
	return hd;
}


void FileSystemHandler::FSFactoryMethod()
{
	std::string sName((char*)FileSystemV::ReadOEM_ID(hd));
	if (sName == "NTFS    ")
	{
		this->fs = new NTFS(hd);
	}
	else if (sName == "MSDOS5.0")
	{
		this->fs = new FAT32(hd);
	}
	else if (sName == "EXFAT   ")
	{
		this->fs = new exFAT(hd);
	}
	else
	{
		this->fs = { 0 };
	}
}


void FileSystemHandler::SelectVolumeDialog() {
	DWORD bufferSize = MAX_PATH;
	std::list<char> disksLetters;
	GetLogicalDriveStringsW(bufferSize, (LPWSTR)volume);
	for (CHAR i = 0; volume[i] != 0; i = i + 4)
	{
		std::cout << (char)volume[i] << (char)volume[i + 1] << (char)volume[i + 2] << std::endl;
		WCHAR disk[3] = { volume[i], volume[i + 1], volume[i + 2] };
		WCHAR name[8] = L"\\\\.\\";
		wcsncpy(name + 4, disk, 2);
		HANDLE hd = CreateHandle(name);
		BYTE *OEM = FileSystemV::ReadOEM_ID(hd);
		if (hd != 0)
		{
			std::cout << "File system: " << (char*)OEM << std::endl;
			disksLetters.push_back((char)volume[i]);
			CloseHandle(hd);
		}
	}
	char letter;
	while (true) {
		bool end = false;
		std::cout << "Type letter of required device" << std::endl;
		std::cin >> letter;
		for (char n : disksLetters) {
			if (n == toupper(letter)) {
				end = true;
			}
		}
		if (end) {
			break;
		}
	}
	WCHAR name[8] = { '\\', '\\', '.', '\\', toupper(letter), ':' };
	this->hd = CreateHandle(name);
	FSFactoryMethod();
}


void FileSystemHandler::GetFileSystemInfo()
{
	this->fs->WriteFSData();
}


FSiterator FileSystemHandler::GetIterator()
{
	return FSiterator(this->fs);
}


void FileSystemHandler::DrawByteArray(BYTE *buffer, DWORD size)
{
	for (DWORD i = 0; i < size; i++)
	{
		std::cout << std::hex << (DWORD)buffer[i] << " ";
		if ((i + 1) % 16 == 0)
		{
			std::cout << std::endl;
		}
	}
}


DWORD FileSystemHandler::GetSectorSize()
{
	return fs->GetSectorSize();
}


DWORD FileSystemHandler::GetClusterSize()
{
	return fs->GetSectorPerClusterCount();
}
