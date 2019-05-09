// FileSystemHandler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "FSHandler.h"

int main()
{
	FSHandler fh;
	fh.GetVolumesInfo();
	ULONGLONG scCnt = fh.GetSectorsCount();
	std::cout << std::endl;
	ULONGLONG firstSector = 0;
	DWORD sectorsCount = 0;
	while (true) {
		std::cout << "Type number of firts sector to read" << std::endl;
		std::cin >> firstSector;
		if (firstSector >= 0 && firstSector < scCnt)
		{
			break;
		}
	}
	while (true) {
		std::cout << "Type number of sectors to read" << std::endl;
		std::cin >> sectorsCount;
		if (sectorsCount >= 0 && (scCnt - sectorsCount) > 0)
		{
			break;
		}
	}
	sectorsCount = sectorsCount * fh.GetSectorSize();
	firstSector = firstSector * fh.GetSectorSize();
	BYTE *result = fh.ReadBytes(firstSector,sectorsCount);
	DWORD limit = fh.GetLastReturnBytesCount();
	for (DWORD i = 0; i < fh.GetLastReturnBytesCount(); i++)
	{
		std::cout << std::hex << (DWORD)result[i] << " ";
		if ((i + 1)%16 == 0)
		{
			std::cout << std::endl;
		}
	}
	system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
