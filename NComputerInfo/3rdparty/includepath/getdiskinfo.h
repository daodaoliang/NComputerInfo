#include <windows.h>

struct diskInfo{
	char controllerType[1024];
	char type[1024];
	char modelNumber[1024];
	char serialNumber[1024];
	char revisionNumber[1024];
	char driveType[1024];
	DWORD bufferSize;
	DWORD cylinders;
	DWORD heads;
	DWORD sectors;
	//_int64 computerID;
};
