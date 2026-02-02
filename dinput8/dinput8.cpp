#include <windows.h>

#include <cstdarg>
#include <cstdio>
#include <string>
#include <algorithm>

struct dinput8_dll
{
    HMODULE dll;

    FARPROC DirectInput8Create;
    FARPROC DllCanUnloadNow;
    FARPROC DllGetClassObject;
    FARPROC DllRegisterServer;
    FARPROC DllUnregisterServer;

    void LoadOriginalLibrary(HMODULE module)
    {
        dll = module;
        DirectInput8Create = GetProcAddress(dll, "DirectInput8Create");
        DllCanUnloadNow = GetProcAddress(dll, "DllCanUnloadNow");
        DllGetClassObject = GetProcAddress(dll, "DllGetClassObject");
        DllRegisterServer = GetProcAddress(dll, "DllRegisterServer");
        DllUnregisterServer = GetProcAddress(dll, "DllUnregisterServer");
    }
} dinput8;

static void DebugLogA(const char* fmt, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    OutputDebugStringA(buffer);
}

static void DebugLogLastErrorA(const char* prefix)
{
    DWORD err = GetLastError();
    DebugLogA("%s GetLastError=%lu\n", prefix, static_cast<unsigned long>(err));
}

static bool IsTargetProcess(const char* targetName)
{
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    std::string path(exePath);
    size_t pos = path.find_last_of("\\/");
    std::string exeName = (pos != std::string::npos) ? path.substr(pos + 1) : path;

    std::transform(exeName.begin(), exeName.end(), exeName.begin(), ::tolower);
    std::string target(targetName);
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);

    return exeName == target;
}

static std::string GetProcessDirectory()
{
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    std::string path(exePath);
    size_t pos = path.find_last_of("\\/");
    if (pos != std::string::npos) {
        return path.substr(0, pos + 1);
    }
    return "";
}

using FnDirectInput8Create = HRESULT(WINAPI*)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);
using FnDllCanUnloadNow = HRESULT(WINAPI*)(void);
using FnDllGetClassObject = HRESULT(WINAPI*)(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
using FnDllRegisterServer = HRESULT(WINAPI*)(void);
using FnDllUnregisterServer = HRESULT(WINAPI*)(void);

extern "C" {

HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
    auto fn = reinterpret_cast<FnDirectInput8Create>(dinput8.DirectInput8Create);
    return fn ? fn(hinst, dwVersion, riidltf, ppvOut, punkOuter) : E_FAIL;
}

HRESULT WINAPI DllCanUnloadNow(void)
{
    auto fn = reinterpret_cast<FnDllCanUnloadNow>(dinput8.DllCanUnloadNow);
    return fn ? fn() : S_FALSE;
}

HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    auto fn = reinterpret_cast<FnDllGetClassObject>(dinput8.DllGetClassObject);
    return fn ? fn(rclsid, riid, ppv) : CLASS_E_CLASSNOTAVAILABLE;
}

HRESULT WINAPI DllRegisterServer(void)
{
    auto fn = reinterpret_cast<FnDllRegisterServer>(dinput8.DllRegisterServer);
    return fn ? fn() : E_FAIL;
}

HRESULT WINAPI DllUnregisterServer(void)
{
    auto fn = reinterpret_cast<FnDllUnregisterServer>(dinput8.DllUnregisterServer);
    return fn ? fn() : E_FAIL;
}

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    static HMODULE hOriginalDll = NULL;

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        DebugLogA("[dinput8-proxy] DLL_PROCESS_ATTACH module=%p\n", hModule);

        {
            char systemPath[MAX_PATH];
            GetSystemDirectoryA(systemPath, MAX_PATH);
            strcat_s(systemPath, "\\dinput8.dll");

            hOriginalDll = LoadLibraryA(systemPath);
            if (hOriginalDll) {
                dinput8.LoadOriginalLibrary(hOriginalDll);
                DebugLogA("[dinput8-proxy] Loaded original dinput8.dll: %s module=%p\n", systemPath, hOriginalDll);
            } else {
                DebugLogA("[dinput8-proxy] Failed to load original dinput8.dll: %s\n", systemPath);
                DebugLogLastErrorA("[dinput8-proxy] LoadLibraryA(original dinput8.dll) failed.");
            }
        }

        if (IsTargetProcess("isaac-ng.exe")) {
            std::string dllPath = GetProcessDirectory() + "p2p_hook.dll";
            DebugLogA("[dinput8-proxy] Target process matched. Loading hook: %s\n", dllPath.c_str());
            SetLastError(0);
            HMODULE hHook = LoadLibraryA(dllPath.c_str());
            if (hHook) {
                DebugLogA("[dinput8-proxy] Loaded p2p_hook.dll: module=%p\n", hHook);
            } else {
                DebugLogA("[dinput8-proxy] Failed to load p2p_hook.dll: %s\n", dllPath.c_str());
                DebugLogLastErrorA("[dinput8-proxy] LoadLibraryA(p2p_hook.dll) failed.");
            }
        } else {
            DebugLogA("[dinput8-proxy] Not target process. Skipping hook load.\n");
        }
        break;

    case DLL_PROCESS_DETACH:
        DebugLogA("[dinput8-proxy] DLL_PROCESS_DETACH module=%p\n", hModule);
        if (hOriginalDll) {
            FreeLibrary(hOriginalDll);
        }
        break;
    }

    return TRUE;
}
