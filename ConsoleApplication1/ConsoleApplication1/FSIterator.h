#pragma once
#include "FileSystemV.h"

class FSiterator
{
protected:
	ULONGLONG currentClusterOffset;
	FileSystemV *fs;
public:
	FSiterator(FileSystemV *fs);
	FSiterator();
	~FSiterator();
	void First();
	void Next();
	bool IsDone();
	BYTE *GetCurrent();
};

//---------------------------------------------------------------------------//

class FSiteratorDecorator : public FSiterator
{
protected:
	FSiterator *dk;
public:
	FSiteratorDecorator(FSiterator *dk);
	~FSiteratorDecorator();
	void First();
	void Next();
	bool IsDone();
	BYTE *GetCurrent();
};


