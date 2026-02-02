#include <windows.h>

#include <string>
#include <algorithm>

struct version_dll
{
    HMODULE dll;

    FARPROC GetFileVersionInfoA;
    FARPROC GetFileVersionInfoW;
    FARPROC GetFileVersionInfoSizeA;
    FARPROC GetFileVersionInfoSizeW;
    FARPROC GetFileVersionInfoSizeExA;
    FARPROC GetFileVersionInfoSizeExW;
    FARPROC GetFileVersionInfoExA;
    FARPROC GetFileVersionInfoExW;
    FARPROC VerFindFileA;
    FARPROC VerFindFileW;
    FARPROC VerInstallFileA;
    FARPROC VerInstallFileW;
    FARPROC VerLanguageNameA;
    FARPROC VerLanguageNameW;
    FARPROC VerQueryValueA;
    FARPROC VerQueryValueW;

    void LoadOriginalLibrary(HMODULE module)
    {
        dll = module;
        GetFileVersionInfoA = GetProcAddress(dll, "GetFileVersionInfoA");
        GetFileVersionInfoW = GetProcAddress(dll, "GetFileVersionInfoW");
        GetFileVersionInfoSizeA = GetProcAddress(dll, "GetFileVersionInfoSizeA");
        GetFileVersionInfoSizeW = GetProcAddress(dll, "GetFileVersionInfoSizeW");
        GetFileVersionInfoSizeExA = GetProcAddress(dll, "GetFileVersionInfoSizeExA");
        GetFileVersionInfoSizeExW = GetProcAddress(dll, "GetFileVersionInfoSizeExW");
        GetFileVersionInfoExA = GetProcAddress(dll, "GetFileVersionInfoExA");
        GetFileVersionInfoExW = GetProcAddress(dll, "GetFileVersionInfoExW");
        VerFindFileA = GetProcAddress(dll, "VerFindFileA");
        VerFindFileW = GetProcAddress(dll, "VerFindFileW");
        VerInstallFileA = GetProcAddress(dll, "VerInstallFileA");
        VerInstallFileW = GetProcAddress(dll, "VerInstallFileW");
        VerLanguageNameA = GetProcAddress(dll, "VerLanguageNameA");
        VerLanguageNameW = GetProcAddress(dll, "VerLanguageNameW");
        VerQueryValueA = GetProcAddress(dll, "VerQueryValueA");
        VerQueryValueW = GetProcAddress(dll, "VerQueryValueW");
    }
} version;

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

using FnGetFileVersionInfoA = BOOL(WINAPI*)(LPCSTR, DWORD, DWORD, LPVOID);
using FnGetFileVersionInfoW = BOOL(WINAPI*)(LPCWSTR, DWORD, DWORD, LPVOID);
using FnGetFileVersionInfoSizeA = DWORD(WINAPI*)(LPCSTR, LPDWORD);
using FnGetFileVersionInfoSizeW = DWORD(WINAPI*)(LPCWSTR, LPDWORD);
using FnGetFileVersionInfoSizeExA = DWORD(WINAPI*)(DWORD, LPCSTR, LPDWORD);
using FnGetFileVersionInfoSizeExW = DWORD(WINAPI*)(DWORD, LPCWSTR, LPDWORD);
using FnGetFileVersionInfoExA = BOOL(WINAPI*)(DWORD, LPCSTR, DWORD, DWORD, LPVOID);
using FnGetFileVersionInfoExW = BOOL(WINAPI*)(DWORD, LPCWSTR, DWORD, DWORD, LPVOID);
using FnVerFindFileA = DWORD(WINAPI*)(DWORD, LPCSTR, LPCSTR, LPCSTR, LPSTR, PUINT, LPSTR, PUINT);
using FnVerFindFileW = DWORD(WINAPI*)(DWORD, LPCWSTR, LPCWSTR, LPCWSTR, LPWSTR, PUINT, LPWSTR, PUINT);
using FnVerInstallFileA = DWORD(WINAPI*)(DWORD, LPCSTR, LPCSTR, LPCSTR, LPCSTR, LPCSTR, LPSTR, PUINT);
using FnVerInstallFileW = DWORD(WINAPI*)(DWORD, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, LPWSTR, PUINT);
using FnVerLanguageNameA = DWORD(WINAPI*)(DWORD, LPSTR, DWORD);
using FnVerLanguageNameW = DWORD(WINAPI*)(DWORD, LPWSTR, DWORD);
using FnVerQueryValueA = BOOL(WINAPI*)(LPCVOID, LPCSTR, LPVOID*, PUINT);
using FnVerQueryValueW = BOOL(WINAPI*)(LPCVOID, LPCWSTR, LPVOID*, PUINT);

extern "C" {

BOOL WINAPI GetFileVersionInfoA(LPCSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
    auto fn = reinterpret_cast<FnGetFileVersionInfoA>(version.GetFileVersionInfoA);
    return fn ? fn(lptstrFilename, dwHandle, dwLen, lpData) : FALSE;
}

BOOL WINAPI GetFileVersionInfoW(LPCWSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
    auto fn = reinterpret_cast<FnGetFileVersionInfoW>(version.GetFileVersionInfoW);
    return fn ? fn(lptstrFilename, dwHandle, dwLen, lpData) : FALSE;
}

DWORD WINAPI GetFileVersionInfoSizeA(LPCSTR lptstrFilename, LPDWORD lpdwHandle)
{
    auto fn = reinterpret_cast<FnGetFileVersionInfoSizeA>(version.GetFileVersionInfoSizeA);
    return fn ? fn(lptstrFilename, lpdwHandle) : 0;
}

DWORD WINAPI GetFileVersionInfoSizeW(LPCWSTR lptstrFilename, LPDWORD lpdwHandle)
{
    auto fn = reinterpret_cast<FnGetFileVersionInfoSizeW>(version.GetFileVersionInfoSizeW);
    return fn ? fn(lptstrFilename, lpdwHandle) : 0;
}

DWORD WINAPI GetFileVersionInfoSizeExA(DWORD dwFlags, LPCSTR lpwstrFilename, LPDWORD lpdwHandle)
{
    auto fn = reinterpret_cast<FnGetFileVersionInfoSizeExA>(version.GetFileVersionInfoSizeExA);
    return fn ? fn(dwFlags, lpwstrFilename, lpdwHandle) : 0;
}

DWORD WINAPI GetFileVersionInfoSizeExW(DWORD dwFlags, LPCWSTR lpwstrFilename, LPDWORD lpdwHandle)
{
    auto fn = reinterpret_cast<FnGetFileVersionInfoSizeExW>(version.GetFileVersionInfoSizeExW);
    return fn ? fn(dwFlags, lpwstrFilename, lpdwHandle) : 0;
}

BOOL WINAPI GetFileVersionInfoExA(DWORD dwFlags, LPCSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
    auto fn = reinterpret_cast<FnGetFileVersionInfoExA>(version.GetFileVersionInfoExA);
    return fn ? fn(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData) : FALSE;
}

BOOL WINAPI GetFileVersionInfoExW(DWORD dwFlags, LPCWSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
    auto fn = reinterpret_cast<FnGetFileVersionInfoExW>(version.GetFileVersionInfoExW);
    return fn ? fn(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData) : FALSE;
}

DWORD WINAPI VerFindFileA(DWORD uFlags, LPCSTR szFileName, LPCSTR szWinDir, LPCSTR szAppDir, LPSTR szCurDir, PUINT lpuCurDirLen, LPSTR szDestDir, PUINT lpuDestDirLen)
{
    auto fn = reinterpret_cast<FnVerFindFileA>(version.VerFindFileA);
    return fn ? fn(uFlags, szFileName, szWinDir, szAppDir, szCurDir, lpuCurDirLen, szDestDir, lpuDestDirLen) : 0;
}

DWORD WINAPI VerFindFileW(DWORD uFlags, LPCWSTR szFileName, LPCWSTR szWinDir, LPCWSTR szAppDir, LPWSTR szCurDir, PUINT lpuCurDirLen, LPWSTR szDestDir, PUINT lpuDestDirLen)
{
    auto fn = reinterpret_cast<FnVerFindFileW>(version.VerFindFileW);
    return fn ? fn(uFlags, szFileName, szWinDir, szAppDir, szCurDir, lpuCurDirLen, szDestDir, lpuDestDirLen) : 0;
}

DWORD WINAPI VerInstallFileA(DWORD uFlags, LPCSTR szSrcFileName, LPCSTR szDestFileName, LPCSTR szSrcDir, LPCSTR szDestDir, LPCSTR szCurDir, LPSTR szTmpFile, PUINT lpuTmpFileLen)
{
    auto fn = reinterpret_cast<FnVerInstallFileA>(version.VerInstallFileA);
    return fn ? fn(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir, szCurDir, szTmpFile, lpuTmpFileLen) : 0;
}

DWORD WINAPI VerInstallFileW(DWORD uFlags, LPCWSTR szSrcFileName, LPCWSTR szDestFileName, LPCWSTR szSrcDir, LPCWSTR szDestDir, LPCWSTR szCurDir, LPWSTR szTmpFile, PUINT lpuTmpFileLen)
{
    auto fn = reinterpret_cast<FnVerInstallFileW>(version.VerInstallFileW);
    return fn ? fn(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir, szCurDir, szTmpFile, lpuTmpFileLen) : 0;
}

DWORD WINAPI VerLanguageNameA(DWORD wLang, LPSTR szLang, DWORD cchLang)
{
    auto fn = reinterpret_cast<FnVerLanguageNameA>(version.VerLanguageNameA);
    return fn ? fn(wLang, szLang, cchLang) : 0;
}

DWORD WINAPI VerLanguageNameW(DWORD wLang, LPWSTR szLang, DWORD cchLang)
{
    auto fn = reinterpret_cast<FnVerLanguageNameW>(version.VerLanguageNameW);
    return fn ? fn(wLang, szLang, cchLang) : 0;
}

BOOL WINAPI VerQueryValueA(LPCVOID pBlock, LPCSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen)
{
    auto fn = reinterpret_cast<FnVerQueryValueA>(version.VerQueryValueA);
    return fn ? fn(pBlock, lpSubBlock, lplpBuffer, puLen) : FALSE;
}

BOOL WINAPI VerQueryValueW(LPCVOID pBlock, LPCWSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen)
{
    auto fn = reinterpret_cast<FnVerQueryValueW>(version.VerQueryValueW);
    return fn ? fn(pBlock, lpSubBlock, lplpBuffer, puLen) : FALSE;
}

} 

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    static HMODULE hOriginalDll = NULL;

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        {
            char systemPath[MAX_PATH];
            GetSystemDirectoryA(systemPath, MAX_PATH);
            strcat_s(systemPath, "\\version.dll");

            hOriginalDll = LoadLibraryA(systemPath);
            if (hOriginalDll) {
                version.LoadOriginalLibrary(hOriginalDll);
            }
        }

        if (IsTargetProcess("isaac-ng.exe")) {
            std::string dllPath = GetProcessDirectory() + "p2p_hook.dll";
            LoadLibraryA(dllPath.c_str());
        }
        break;

    case DLL_PROCESS_DETACH:
        if (hOriginalDll) {
            FreeLibrary(hOriginalDll);
        }
        break;
    }

    return TRUE;
}
