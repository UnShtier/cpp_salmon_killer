#include <iostream>
#include "FileSystemHandler.h"

int main()
{
	FileSystemHandler fh = FileSystemHandler();
	fh.SelectVolumeDialog();
	fh.GetFileSystemInfo();
	FSiterator i = fh.GetIterator();
	FSiteratorDecorator di = FSiteratorDecorator(&i);
	di.Next();
	BYTE *result = di.GetCurrent();
	DWORD sz = fh.GetClusterSize()*fh.GetSectorSize();
	FileSystemHandler::DrawByteArray(result, sz);
	system("pause");
}