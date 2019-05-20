#pragma once
#include "FileSystemV.h"
#include <iterator>
#include <list>
#include "exFAT.h"
#include "NTFS.h"
#include "FAT32.h"
#include "FSIterator.h"

class FileSystemHandler
{
private:
	HANDLE hd;
	WCHAR volume[MAX_PATH];
	FileSystemV *fs;
	void FSFactoryMethod();


public:
	FileSystemHandler();
	FileSystemHandler(HANDLE hd);
	~FileSystemHandler();
	static HANDLE CreateHandle(WCHAR *volumeName);
	void SelectVolumeDialog();
	void GetFileSystemInfo();
	FSiterator GetIterator();
	static void DrawByteArray(BYTE *buffer, DWORD size);
	DWORD GetSectorSize();
	DWORD GetClusterSize();
};

