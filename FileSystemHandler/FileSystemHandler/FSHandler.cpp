#include "FSHandler.h"


FSHandler::FSHandler()
{
	this->hdl = { 0 };
	this->volume[MAX_PATH] = { NULL };
}


FSHandler::~FSHandler()
{
}

HANDLE FSHandler::CreateHandle(WCHAR * name) {
	HANDLE hd = CreateFileW(name, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hd == INVALID_HANDLE_VALUE) {
		CloseHandle(hd);
		exit(GetLastError());
	}
	return hd;
}

BYTE *FSHandler::ReadBytes(HANDLE &hd, ULONGLONG &offset, DWORD &bytes) {
	LARGE_INTEGER oft;
	BYTE *buf = new BYTE[bytes];
	oft.QuadPart = offset;
	this->lastOffset = SetFilePointer(hd, oft.LowPart, &oft.HighPart, FILE_BEGIN);
	if (this->lastOffset != oft.LowPart) {
		this->error = GetLastError();
		CloseHandle(hd);
		exit(this->error);
	}
	bool readResult = ReadFile(hd, buf, bytes, &this->lastReturnBytesCount, NULL);
	if (!readResult || this->lastReturnBytesCount != bytes) {
		this->error = GetLastError();
		CloseHandle(hd);
		exit(this->error);
	}
	return buf;
}

DWORD FSHandler::GetSectorSize(HANDLE hd) {

	bool result = DeviceIoControl(hd, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0, &dg, sizeof(dg), &lastReturnBytesCount, NULL);
	if (result) {
		return dg.BytesPerSector;
	}
	return 0;
}

int FSHandler::RecogniseFileSystem(BYTE *buffer) {
	BootRecord *br = (BootRecord*)buffer;
	std::string sName((char*)br->OEM_ID);
	if (sName == "NTFS    ")
	{
		return NTFS;
	}
	else
	{
		return Unknown;
	}
}


void FSHandler::GetVolumesInfo() {
	DWORD bufferSize = MAX_PATH;
	std::list<char> disksLetters;
	GetLogicalDriveStringsW(bufferSize, (LPWSTR)volume);
	for (CHAR i = 0; volume[i] != 0; i = i + 4)
	{
		std::cout << (char)volume[i] << (char)volume[i+1] << (char)volume[i+2] << std::endl;
		WCHAR disk[3] = { volume[i], volume[i + 1], volume[i + 2] };
		WCHAR name[8] = L"\\\\.\\"; 
		wcsncpy(name + 4, disk, 2);
		HANDLE hd = CreateHandle(name);
		DWORD sz = GetSectorSize(hd);
		ULONGLONG st = 0;
		BYTE *buffer = ReadBytes(hd, st, sz);
		if (RecogniseFileSystem(buffer) != Unknown)
		{
			NTFS_HS fs = NTFS_HS(hd, buffer);
			fs.PrintData();	
			disksLetters.push_back((char)volume[i]);
		}
		else {
			std::cout << "File system is not recognisable" << std::endl;
		}
	}
	char letter;
	while(true) {
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

	WCHAR name[8] = { '\\', '\\', '.', '\\', toupper(letter), ':'};
	HANDLE hd = CreateHandle(name);
	DWORD sz = GetSectorSize(hd);
	ULONGLONG st = 0;
	BYTE *buffer = ReadBytes(hd, st, sz);
	this->firstSector = buffer;
	this->hdl = hd;
	this->fileSystemType = RecogniseFileSystem(buffer);
}

BYTE* FSHandler::ReadBytes(ULONGLONG &offset, DWORD &bytes) {
	LARGE_INTEGER oft;
	BYTE *buf = new BYTE[bytes];
	oft.QuadPart = offset;
	this->lastOffset = SetFilePointer(this->hdl, oft.LowPart, &oft.HighPart, FILE_BEGIN);
	if (this->lastOffset != oft.LowPart) {
		this->error = GetLastError();
		exit(this->error);
	}
	bool readResult = ReadFile(this->hdl, buf, bytes, &this->lastReturnBytesCount, NULL);
	if (!readResult || this->lastReturnBytesCount != bytes) {
		this->error = GetLastError();
		exit(this->error);
	}
	return buf;
}

ULONGLONG FSHandler::GetSectorsCount() {
	switch (this->fileSystemType)
	{
	case NTFS:
		NTFS_HS fs = NTFS_HS(this->hdl, this->firstSector);
		return fs.GetSectorsCount();
	}
}


DWORD FSHandler::GetLastReturnBytesCount() {
	return this->lastReturnBytesCount;
};

DWORD FSHandler::GetSectorSize() {
	switch (this->fileSystemType)
	{
	case NTFS:
		NTFS_HS fs = NTFS_HS(this->hdl, this->firstSector);
		return fs.GetSectorSize();
	}
}