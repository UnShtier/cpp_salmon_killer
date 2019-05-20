#pragma once
#include "FileSystemV.h"

class FSiterator
{
protected:
	ULONGLONG currentClusterOffset;
	FileSystemV *fs;
public:
	FSiterator(FileSystemV *fs);
	~FSiterator();
	void First();
	void Next();
	bool IsDone();
	BYTE *GetCurrent();
};

