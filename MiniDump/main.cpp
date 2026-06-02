#include <windows.h>
#include <DbgHelp.h>
#include <iostream>

// Link the dbghelp library
#pragma comment(lib, "dbghelp.lib")

// Exception filter function
LONG WINAPI CrashFilter(EXCEPTION_POINTERS* pExceptionInfo) {
    // Create the dump file
    HANDLE hFile = CreateFileA(
        "crash_dump.dmp", 
        GENERIC_WRITE, 
        0, 
        NULL, 
        CREATE_ALWAYS, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL
    );

    if (hFile != INVALID_HANDLE_VALUE) {
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ExceptionPointers = pExceptionInfo;
        dumpInfo.ClientPointers = FALSE;

        // Write the minidump to the file
        BOOL success = MiniDumpWriteDump(
            GetCurrentProcess(),
            GetCurrentProcessId(),
            hFile,
            MiniDumpNormal, // Dump type configuration
            &dumpInfo,
            NULL,
            NULL
        );

        if (success) {
            std::cout << "Minidump successfully created!" << std::endl;
        } else {
            std::cout << "Failed to write minidump. Error: " << GetLastError() << std::endl;
        }

        CloseHandle(hFile);
    } else {
        std::cout << "Failed to create dump file. Error: " << GetLastError() << std::endl;
    }

    // Terminate the app after handling
    return EXCEPTION_EXECUTE_HANDLER;
}

int main() {
    // Register the crash handler
    SetUnhandledExceptionFilter(CrashFilter);

    std::cout << "Application running. Triggering crash..." << std::endl;

    // Simulate an unhandled exception (Access Violation)
    int* badPointer = nullptr;
    *badPointer = 42; 

    return 0;
}