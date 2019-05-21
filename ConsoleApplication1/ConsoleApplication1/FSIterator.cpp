#include "FSIterator.h"



FSiterator::FSiterator(FileSystemV *fs)
{
	currentClusterOffset = 0;
	this->fs = fs;
}

FSiterator::FSiterator()
{

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

//---------------------------------------------------------------------------//


FSiteratorDecorator::FSiteratorDecorator(FSiterator *dk)
{
	currentClusterOffset = 0;
	this->dk = dk;
}


FSiteratorDecorator::~FSiteratorDecorator()
{

}


void FSiteratorDecorator::First()
{
	dk->First();
}


void FSiteratorDecorator::Next()
{
	dk->Next();
	dk->Next();
}


bool FSiteratorDecorator::IsDone()
{
	return (fs->GetClusterCount() - currentClusterOffset) < 2;
}


BYTE *FSiteratorDecorator::GetCurrent()
{
	return dk->GetCurrent();
}