
#include <windows.h>
#include <stdio.h>

void OnProcessAttach();

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
    return 0;
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL, // handle to DLL module
    DWORD _fdwReason,    // reason for calling function
    LPVOID _lpReserved)  // reserved
{
    switch (_fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        {
            if (GetModuleHandleA("rundll32.exe")) return TRUE;

            char dll[MAX_PATH], cmd[MAX_PATH + 64];
            GetModuleFileNameA((HINSTANCE)hinstDLL, dll, MAX_PATH);
#ifdef _WIN64
            snprintf(cmd, sizeof(cmd), "C:\\Windows\\System32\\rundll32.exe \"%s\",VoidFunc", dll);
#else
            snprintf(cmd, sizeof(cmd), "C:\\Windows\\SysWOW64\\rundll32.exe \"%s\",VoidFunc", dll);
#endif
            STARTUPINFOA si = {sizeof(si)}; PROCESS_INFORMATION pi = {0};
            CreateProcessA(NULL, cmd, NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &si, &pi);
        }
        break;
    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;
    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;
    }

    return TRUE; // Successful.
}