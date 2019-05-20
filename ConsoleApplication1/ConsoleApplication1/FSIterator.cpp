#include "FSIterator.h"



FSiterator::FSiterator(FileSystemV *fs)
{
	currentClusterOffset = 0;
	this->fs = fs;
}


FSiterator::~FSiterator()
{

}


void FSiterator::First()
{
	currentClusterOffset = 0;
}


void FSiterator::Next()
{
	currentClusterOffset++;
}


bool FSiterator::IsDone()
{
	return fs->GetClusterCount() >= currentClusterOffset;
}


BYTE *FSiterator::GetCurrent()
{
	return fs->GetClusterBytes(1, currentClusterOffset);
}