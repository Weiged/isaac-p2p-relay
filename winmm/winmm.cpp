#include <windows.h>

// 取消 Windows 宏定义，避免与成员变量名冲突
#undef PlaySound
#undef PlaySoundA
#undef PlaySoundW

#include <string>
#include <algorithm>


struct winmm_dll
{
    HMODULE dll;
    FARPROC CloseDriver;
    FARPROC DefDriverProc;
    FARPROC DriverCallback;
    FARPROC DrvGetModuleHandle;
    FARPROC GetDriverModuleHandle;
    FARPROC NotifyCallbackData;
    FARPROC OpenDriver;
    FARPROC PlaySound;
    FARPROC PlaySoundA;
    FARPROC PlaySoundW;
    FARPROC SendDriverMessage;
    FARPROC WOW32DriverCallback;
    FARPROC WOW32ResolveMultiMediaHandle;
    FARPROC WOWAppExit;
    FARPROC aux32Message;
    FARPROC auxGetDevCapsA;
    FARPROC auxGetDevCapsW;
    FARPROC auxGetNumDevs;
    FARPROC auxGetVolume;
    FARPROC auxOutMessage;
    FARPROC auxSetVolume;
    FARPROC joy32Message;
    FARPROC joyConfigChanged;
    FARPROC joyGetDevCapsA;
    FARPROC joyGetDevCapsW;
    FARPROC joyGetNumDevs;
    FARPROC joyGetPos;
    FARPROC joyGetPosEx;
    FARPROC joyGetThreshold;
    FARPROC joyReleaseCapture;
    FARPROC joySetCapture;
    FARPROC joySetThreshold;
    FARPROC mci32Message;
    FARPROC mciDriverNotify;
    FARPROC mciDriverYield;
    FARPROC mciExecute;
    FARPROC mciFreeCommandResource;
    FARPROC mciGetCreatorTask;
    FARPROC mciGetDeviceIDA;
    FARPROC mciGetDeviceIDFromElementIDA;
    FARPROC mciGetDeviceIDFromElementIDW;
    FARPROC mciGetDeviceIDW;
    FARPROC mciGetDriverData;
    FARPROC mciGetErrorStringA;
    FARPROC mciGetErrorStringW;
    FARPROC mciGetYieldProc;
    FARPROC mciLoadCommandResource;
    FARPROC mciSendCommandA;
    FARPROC mciSendCommandW;
    FARPROC mciSendStringA;
    FARPROC mciSendStringW;
    FARPROC mciSetDriverData;
    FARPROC mciSetYieldProc;
    FARPROC mid32Message;
    FARPROC midiConnect;
    FARPROC midiDisconnect;
    FARPROC midiInAddBuffer;
    FARPROC midiInClose;
    FARPROC midiInGetDevCapsA;
    FARPROC midiInGetDevCapsW;
    FARPROC midiInGetErrorTextA;
    FARPROC midiInGetErrorTextW;
    FARPROC midiInGetID;
    FARPROC midiInGetNumDevs;
    FARPROC midiInMessage;
    FARPROC midiInOpen;
    FARPROC midiInPrepareHeader;
    FARPROC midiInReset;
    FARPROC midiInStart;
    FARPROC midiInStop;
    FARPROC midiInUnprepareHeader;
    FARPROC midiOutCacheDrumPatches;
    FARPROC midiOutCachePatches;
    FARPROC midiOutClose;
    FARPROC midiOutGetDevCapsA;
    FARPROC midiOutGetDevCapsW;
    FARPROC midiOutGetErrorTextA;
    FARPROC midiOutGetErrorTextW;
    FARPROC midiOutGetID;
    FARPROC midiOutGetNumDevs;
    FARPROC midiOutGetVolume;
    FARPROC midiOutLongMsg;
    FARPROC midiOutMessage;
    FARPROC midiOutOpen;
    FARPROC midiOutPrepareHeader;
    FARPROC midiOutReset;
    FARPROC midiOutSetVolume;
    FARPROC midiOutShortMsg;
    FARPROC midiOutUnprepareHeader;
    FARPROC midiStreamClose;
    FARPROC midiStreamOpen;
    FARPROC midiStreamOut;
    FARPROC midiStreamPause;
    FARPROC midiStreamPosition;
    FARPROC midiStreamProperty;
    FARPROC midiStreamRestart;
    FARPROC midiStreamStop;
    FARPROC mixerClose;
    FARPROC mixerGetControlDetailsA;
    FARPROC mixerGetControlDetailsW;
    FARPROC mixerGetDevCapsA;
    FARPROC mixerGetDevCapsW;
    FARPROC mixerGetID;
    FARPROC mixerGetLineControlsA;
    FARPROC mixerGetLineControlsW;
    FARPROC mixerGetLineInfoA;
    FARPROC mixerGetLineInfoW;
    FARPROC mixerGetNumDevs;
    FARPROC mixerMessage;
    FARPROC mixerOpen;
    FARPROC mixerSetControlDetails;
    FARPROC mmDrvInstall;
    FARPROC mmGetCurrentTask;
    FARPROC mmTaskBlock;
    FARPROC mmTaskCreate;
    FARPROC mmTaskSignal;
    FARPROC mmTaskYield;
    FARPROC mmioAdvance;
    FARPROC mmioAscend;
    FARPROC mmioClose;
    FARPROC mmioCreateChunk;
    FARPROC mmioDescend;
    FARPROC mmioFlush;
    FARPROC mmioGetInfo;
    FARPROC mmioInstallIOProcA;
    FARPROC mmioInstallIOProcW;
    FARPROC mmioOpenA;
    FARPROC mmioOpenW;
    FARPROC mmioRead;
    FARPROC mmioRenameA;
    FARPROC mmioRenameW;
    FARPROC mmioSeek;
    FARPROC mmioSendMessage;
    FARPROC mmioSetBuffer;
    FARPROC mmioSetInfo;
    FARPROC mmioStringToFOURCCA;
    FARPROC mmioStringToFOURCCW;
    FARPROC mmioWrite;
    FARPROC mmsystemGetVersion;
    FARPROC mod32Message;
    FARPROC mxd32Message;
    FARPROC sndPlaySoundA;
    FARPROC sndPlaySoundW;
    FARPROC tid32Message;
    FARPROC timeBeginPeriod;
    FARPROC timeEndPeriod;
    FARPROC timeGetDevCaps;
    FARPROC timeGetSystemTime;
    FARPROC timeGetTime;
    FARPROC timeKillEvent;
    FARPROC timeSetEvent;
    FARPROC waveInAddBuffer;
    FARPROC waveInClose;
    FARPROC waveInGetDevCapsA;
    FARPROC waveInGetDevCapsW;
    FARPROC waveInGetErrorTextA;
    FARPROC waveInGetErrorTextW;
    FARPROC waveInGetID;
    FARPROC waveInGetNumDevs;
    FARPROC waveInGetPosition;
    FARPROC waveInMessage;
    FARPROC waveInOpen;
    FARPROC waveInPrepareHeader;
    FARPROC waveInReset;
    FARPROC waveInStart;
    FARPROC waveInStop;
    FARPROC waveInUnprepareHeader;
    FARPROC waveOutBreakLoop;
    FARPROC waveOutClose;
    FARPROC waveOutGetDevCapsA;
    FARPROC waveOutGetDevCapsW;
    FARPROC waveOutGetErrorTextA;
    FARPROC waveOutGetErrorTextW;
    FARPROC waveOutGetID;
    FARPROC waveOutGetNumDevs;
    FARPROC waveOutGetPitch;
    FARPROC waveOutGetPlaybackRate;
    FARPROC waveOutGetPosition;
    FARPROC waveOutGetVolume;
    FARPROC waveOutMessage;
    FARPROC waveOutOpen;
    FARPROC waveOutPause;
    FARPROC waveOutPrepareHeader;
    FARPROC waveOutReset;
    FARPROC waveOutRestart;
    FARPROC waveOutSetPitch;
    FARPROC waveOutSetPlaybackRate;
    FARPROC waveOutSetVolume;
    FARPROC waveOutUnprepareHeader;
    FARPROC waveOutWrite;
    FARPROC wid32Message;
    FARPROC wod32Message;

    void LoadOriginalLibrary(HMODULE module)
    {
        dll = module;
        CloseDriver = GetProcAddress(dll, "CloseDriver");
        DefDriverProc = GetProcAddress(dll, "DefDriverProc");
        DriverCallback = GetProcAddress(dll, "DriverCallback");
        DrvGetModuleHandle = GetProcAddress(dll, "DrvGetModuleHandle");
        GetDriverModuleHandle = GetProcAddress(dll, "GetDriverModuleHandle");
        NotifyCallbackData = GetProcAddress(dll, "NotifyCallbackData");
        OpenDriver = GetProcAddress(dll, "OpenDriver");
        PlaySound = GetProcAddress(dll, "PlaySound");
        PlaySoundA = GetProcAddress(dll, "PlaySoundA");
        PlaySoundW = GetProcAddress(dll, "PlaySoundW");
        SendDriverMessage = GetProcAddress(dll, "SendDriverMessage");
        WOW32DriverCallback = GetProcAddress(dll, "WOW32DriverCallback");
        WOW32ResolveMultiMediaHandle = GetProcAddress(dll, "WOW32ResolveMultiMediaHandle");
        WOWAppExit = GetProcAddress(dll, "WOWAppExit");
        aux32Message = GetProcAddress(dll, "aux32Message");
        auxGetDevCapsA = GetProcAddress(dll, "auxGetDevCapsA");
        auxGetDevCapsW = GetProcAddress(dll, "auxGetDevCapsW");
        auxGetNumDevs = GetProcAddress(dll, "auxGetNumDevs");
        auxGetVolume = GetProcAddress(dll, "auxGetVolume");
        auxOutMessage = GetProcAddress(dll, "auxOutMessage");
        auxSetVolume = GetProcAddress(dll, "auxSetVolume");
        joy32Message = GetProcAddress(dll, "joy32Message");
        joyConfigChanged = GetProcAddress(dll, "joyConfigChanged");
        joyGetDevCapsA = GetProcAddress(dll, "joyGetDevCapsA");
        joyGetDevCapsW = GetProcAddress(dll, "joyGetDevCapsW");
        joyGetNumDevs = GetProcAddress(dll, "joyGetNumDevs");
        joyGetPos = GetProcAddress(dll, "joyGetPos");
        joyGetPosEx = GetProcAddress(dll, "joyGetPosEx");
        joyGetThreshold = GetProcAddress(dll, "joyGetThreshold");
        joyReleaseCapture = GetProcAddress(dll, "joyReleaseCapture");
        joySetCapture = GetProcAddress(dll, "joySetCapture");
        joySetThreshold = GetProcAddress(dll, "joySetThreshold");
        mci32Message = GetProcAddress(dll, "mci32Message");
        mciDriverNotify = GetProcAddress(dll, "mciDriverNotify");
        mciDriverYield = GetProcAddress(dll, "mciDriverYield");
        mciExecute = GetProcAddress(dll, "mciExecute");
        mciFreeCommandResource = GetProcAddress(dll, "mciFreeCommandResource");
        mciGetCreatorTask = GetProcAddress(dll, "mciGetCreatorTask");
        mciGetDeviceIDA = GetProcAddress(dll, "mciGetDeviceIDA");
        mciGetDeviceIDFromElementIDA = GetProcAddress(dll, "mciGetDeviceIDFromElementIDA");
        mciGetDeviceIDFromElementIDW = GetProcAddress(dll, "mciGetDeviceIDFromElementIDW");
        mciGetDeviceIDW = GetProcAddress(dll, "mciGetDeviceIDW");
        mciGetDriverData = GetProcAddress(dll, "mciGetDriverData");
        mciGetErrorStringA = GetProcAddress(dll, "mciGetErrorStringA");
        mciGetErrorStringW = GetProcAddress(dll, "mciGetErrorStringW");
        mciGetYieldProc = GetProcAddress(dll, "mciGetYieldProc");
        mciLoadCommandResource = GetProcAddress(dll, "mciLoadCommandResource");
        mciSendCommandA = GetProcAddress(dll, "mciSendCommandA");
        mciSendCommandW = GetProcAddress(dll, "mciSendCommandW");
        mciSendStringA = GetProcAddress(dll, "mciSendStringA");
        mciSendStringW = GetProcAddress(dll, "mciSendStringW");
        mciSetDriverData = GetProcAddress(dll, "mciSetDriverData");
        mciSetYieldProc = GetProcAddress(dll, "mciSetYieldProc");
        mid32Message = GetProcAddress(dll, "mid32Message");
        midiConnect = GetProcAddress(dll, "midiConnect");
        midiDisconnect = GetProcAddress(dll, "midiDisconnect");
        midiInAddBuffer = GetProcAddress(dll, "midiInAddBuffer");
        midiInClose = GetProcAddress(dll, "midiInClose");
        midiInGetDevCapsA = GetProcAddress(dll, "midiInGetDevCapsA");
        midiInGetDevCapsW = GetProcAddress(dll, "midiInGetDevCapsW");
        midiInGetErrorTextA = GetProcAddress(dll, "midiInGetErrorTextA");
        midiInGetErrorTextW = GetProcAddress(dll, "midiInGetErrorTextW");
        midiInGetID = GetProcAddress(dll, "midiInGetID");
        midiInGetNumDevs = GetProcAddress(dll, "midiInGetNumDevs");
        midiInMessage = GetProcAddress(dll, "midiInMessage");
        midiInOpen = GetProcAddress(dll, "midiInOpen");
        midiInPrepareHeader = GetProcAddress(dll, "midiInPrepareHeader");
        midiInReset = GetProcAddress(dll, "midiInReset");
        midiInStart = GetProcAddress(dll, "midiInStart");
        midiInStop = GetProcAddress(dll, "midiInStop");
        midiInUnprepareHeader = GetProcAddress(dll, "midiInUnprepareHeader");
        midiOutCacheDrumPatches = GetProcAddress(dll, "midiOutCacheDrumPatches");
        midiOutCachePatches = GetProcAddress(dll, "midiOutCachePatches");
        midiOutClose = GetProcAddress(dll, "midiOutClose");
        midiOutGetDevCapsA = GetProcAddress(dll, "midiOutGetDevCapsA");
        midiOutGetDevCapsW = GetProcAddress(dll, "midiOutGetDevCapsW");
        midiOutGetErrorTextA = GetProcAddress(dll, "midiOutGetErrorTextA");
        midiOutGetErrorTextW = GetProcAddress(dll, "midiOutGetErrorTextW");
        midiOutGetID = GetProcAddress(dll, "midiOutGetID");
        midiOutGetNumDevs = GetProcAddress(dll, "midiOutGetNumDevs");
        midiOutGetVolume = GetProcAddress(dll, "midiOutGetVolume");
        midiOutLongMsg = GetProcAddress(dll, "midiOutLongMsg");
        midiOutMessage = GetProcAddress(dll, "midiOutMessage");
        midiOutOpen = GetProcAddress(dll, "midiOutOpen");
        midiOutPrepareHeader = GetProcAddress(dll, "midiOutPrepareHeader");
        midiOutReset = GetProcAddress(dll, "midiOutReset");
        midiOutSetVolume = GetProcAddress(dll, "midiOutSetVolume");
        midiOutShortMsg = GetProcAddress(dll, "midiOutShortMsg");
        midiOutUnprepareHeader = GetProcAddress(dll, "midiOutUnprepareHeader");
        midiStreamClose = GetProcAddress(dll, "midiStreamClose");
        midiStreamOpen = GetProcAddress(dll, "midiStreamOpen");
        midiStreamOut = GetProcAddress(dll, "midiStreamOut");
        midiStreamPause = GetProcAddress(dll, "midiStreamPause");
        midiStreamPosition = GetProcAddress(dll, "midiStreamPosition");
        midiStreamProperty = GetProcAddress(dll, "midiStreamProperty");
        midiStreamRestart = GetProcAddress(dll, "midiStreamRestart");
        midiStreamStop = GetProcAddress(dll, "midiStreamStop");
        mixerClose = GetProcAddress(dll, "mixerClose");
        mixerGetControlDetailsA = GetProcAddress(dll, "mixerGetControlDetailsA");
        mixerGetControlDetailsW = GetProcAddress(dll, "mixerGetControlDetailsW");
        mixerGetDevCapsA = GetProcAddress(dll, "mixerGetDevCapsA");
        mixerGetDevCapsW = GetProcAddress(dll, "mixerGetDevCapsW");
        mixerGetID = GetProcAddress(dll, "mixerGetID");
        mixerGetLineControlsA = GetProcAddress(dll, "mixerGetLineControlsA");
        mixerGetLineControlsW = GetProcAddress(dll, "mixerGetLineControlsW");
        mixerGetLineInfoA = GetProcAddress(dll, "mixerGetLineInfoA");
        mixerGetLineInfoW = GetProcAddress(dll, "mixerGetLineInfoW");
        mixerGetNumDevs = GetProcAddress(dll, "mixerGetNumDevs");
        mixerMessage = GetProcAddress(dll, "mixerMessage");
        mixerOpen = GetProcAddress(dll, "mixerOpen");
        mixerSetControlDetails = GetProcAddress(dll, "mixerSetControlDetails");
        mmDrvInstall = GetProcAddress(dll, "mmDrvInstall");
        mmGetCurrentTask = GetProcAddress(dll, "mmGetCurrentTask");
        mmTaskBlock = GetProcAddress(dll, "mmTaskBlock");
        mmTaskCreate = GetProcAddress(dll, "mmTaskCreate");
        mmTaskSignal = GetProcAddress(dll, "mmTaskSignal");
        mmTaskYield = GetProcAddress(dll, "mmTaskYield");
        mmioAdvance = GetProcAddress(dll, "mmioAdvance");
        mmioAscend = GetProcAddress(dll, "mmioAscend");
        mmioClose = GetProcAddress(dll, "mmioClose");
        mmioCreateChunk = GetProcAddress(dll, "mmioCreateChunk");
        mmioDescend = GetProcAddress(dll, "mmioDescend");
        mmioFlush = GetProcAddress(dll, "mmioFlush");
        mmioGetInfo = GetProcAddress(dll, "mmioGetInfo");
        mmioInstallIOProcA = GetProcAddress(dll, "mmioInstallIOProcA");
        mmioInstallIOProcW = GetProcAddress(dll, "mmioInstallIOProcW");
        mmioOpenA = GetProcAddress(dll, "mmioOpenA");
        mmioOpenW = GetProcAddress(dll, "mmioOpenW");
        mmioRead = GetProcAddress(dll, "mmioRead");
        mmioRenameA = GetProcAddress(dll, "mmioRenameA");
        mmioRenameW = GetProcAddress(dll, "mmioRenameW");
        mmioSeek = GetProcAddress(dll, "mmioSeek");
        mmioSendMessage = GetProcAddress(dll, "mmioSendMessage");
        mmioSetBuffer = GetProcAddress(dll, "mmioSetBuffer");
        mmioSetInfo = GetProcAddress(dll, "mmioSetInfo");
        mmioStringToFOURCCA = GetProcAddress(dll, "mmioStringToFOURCCA");
        mmioStringToFOURCCW = GetProcAddress(dll, "mmioStringToFOURCCW");
        mmioWrite = GetProcAddress(dll, "mmioWrite");
        mmsystemGetVersion = GetProcAddress(dll, "mmsystemGetVersion");
        mod32Message = GetProcAddress(dll, "mod32Message");
        mxd32Message = GetProcAddress(dll, "mxd32Message");
        sndPlaySoundA = GetProcAddress(dll, "sndPlaySoundA");
        sndPlaySoundW = GetProcAddress(dll, "sndPlaySoundW");
        tid32Message = GetProcAddress(dll, "tid32Message");
        timeBeginPeriod = GetProcAddress(dll, "timeBeginPeriod");
        timeEndPeriod = GetProcAddress(dll, "timeEndPeriod");
        timeGetDevCaps = GetProcAddress(dll, "timeGetDevCaps");
        timeGetSystemTime = GetProcAddress(dll, "timeGetSystemTime");
        timeGetTime = GetProcAddress(dll, "timeGetTime");
        timeKillEvent = GetProcAddress(dll, "timeKillEvent");
        timeSetEvent = GetProcAddress(dll, "timeSetEvent");
        waveInAddBuffer = GetProcAddress(dll, "waveInAddBuffer");
        waveInClose = GetProcAddress(dll, "waveInClose");
        waveInGetDevCapsA = GetProcAddress(dll, "waveInGetDevCapsA");
        waveInGetDevCapsW = GetProcAddress(dll, "waveInGetDevCapsW");
        waveInGetErrorTextA = GetProcAddress(dll, "waveInGetErrorTextA");
        waveInGetErrorTextW = GetProcAddress(dll, "waveInGetErrorTextW");
        waveInGetID = GetProcAddress(dll, "waveInGetID");
        waveInGetNumDevs = GetProcAddress(dll, "waveInGetNumDevs");
        waveInGetPosition = GetProcAddress(dll, "waveInGetPosition");
        waveInMessage = GetProcAddress(dll, "waveInMessage");
        waveInOpen = GetProcAddress(dll, "waveInOpen");
        waveInPrepareHeader = GetProcAddress(dll, "waveInPrepareHeader");
        waveInReset = GetProcAddress(dll, "waveInReset");
        waveInStart = GetProcAddress(dll, "waveInStart");
        waveInStop = GetProcAddress(dll, "waveInStop");
        waveInUnprepareHeader = GetProcAddress(dll, "waveInUnprepareHeader");
        waveOutBreakLoop = GetProcAddress(dll, "waveOutBreakLoop");
        waveOutClose = GetProcAddress(dll, "waveOutClose");
        waveOutGetDevCapsA = GetProcAddress(dll, "waveOutGetDevCapsA");
        waveOutGetDevCapsW = GetProcAddress(dll, "waveOutGetDevCapsW");
        waveOutGetErrorTextA = GetProcAddress(dll, "waveOutGetErrorTextA");
        waveOutGetErrorTextW = GetProcAddress(dll, "waveOutGetErrorTextW");
        waveOutGetID = GetProcAddress(dll, "waveOutGetID");
        waveOutGetNumDevs = GetProcAddress(dll, "waveOutGetNumDevs");
        waveOutGetPitch = GetProcAddress(dll, "waveOutGetPitch");
        waveOutGetPlaybackRate = GetProcAddress(dll, "waveOutGetPlaybackRate");
        waveOutGetPosition = GetProcAddress(dll, "waveOutGetPosition");
        waveOutGetVolume = GetProcAddress(dll, "waveOutGetVolume");
        waveOutMessage = GetProcAddress(dll, "waveOutMessage");
        waveOutOpen = GetProcAddress(dll, "waveOutOpen");
        waveOutPause = GetProcAddress(dll, "waveOutPause");
        waveOutPrepareHeader = GetProcAddress(dll, "waveOutPrepareHeader");
        waveOutReset = GetProcAddress(dll, "waveOutReset");
        waveOutRestart = GetProcAddress(dll, "waveOutRestart");
        waveOutSetPitch = GetProcAddress(dll, "waveOutSetPitch");
        waveOutSetPlaybackRate = GetProcAddress(dll, "waveOutSetPlaybackRate");
        waveOutSetVolume = GetProcAddress(dll, "waveOutSetVolume");
        waveOutUnprepareHeader = GetProcAddress(dll, "waveOutUnprepareHeader");
        waveOutWrite = GetProcAddress(dll, "waveOutWrite");
        wid32Message = GetProcAddress(dll, "wid32Message");
        wod32Message = GetProcAddress(dll, "wod32Message");
    }
} winmm;


// x86 转发函数 - 使用 naked + jmp 保持栈和寄存器不变
extern "C" {
    __declspec(naked) void _CloseDriver() { __asm { jmp [winmm.CloseDriver] } }
    __declspec(naked) void _DefDriverProc() { __asm { jmp [winmm.DefDriverProc] } }
    __declspec(naked) void _DriverCallback() { __asm { jmp [winmm.DriverCallback] } }
    __declspec(naked) void _DrvGetModuleHandle() { __asm { jmp [winmm.DrvGetModuleHandle] } }
    __declspec(naked) void _GetDriverModuleHandle() { __asm { jmp [winmm.GetDriverModuleHandle] } }
    __declspec(naked) void _NotifyCallbackData() { __asm { jmp [winmm.NotifyCallbackData] } }
    __declspec(naked) void _OpenDriver() { __asm { jmp [winmm.OpenDriver] } }
    __declspec(naked) void _PlaySound() { __asm { jmp [winmm.PlaySound] } }
    __declspec(naked) void _PlaySoundA() { __asm { jmp [winmm.PlaySoundA] } }
    __declspec(naked) void _PlaySoundW() { __asm { jmp [winmm.PlaySoundW] } }
    __declspec(naked) void _SendDriverMessage() { __asm { jmp [winmm.SendDriverMessage] } }
    __declspec(naked) void _WOW32DriverCallback() { __asm { jmp [winmm.WOW32DriverCallback] } }
    __declspec(naked) void _WOW32ResolveMultiMediaHandle() { __asm { jmp [winmm.WOW32ResolveMultiMediaHandle] } }
    __declspec(naked) void _WOWAppExit() { __asm { jmp [winmm.WOWAppExit] } }
    __declspec(naked) void _aux32Message() { __asm { jmp [winmm.aux32Message] } }
    __declspec(naked) void _auxGetDevCapsA() { __asm { jmp [winmm.auxGetDevCapsA] } }
    __declspec(naked) void _auxGetDevCapsW() { __asm { jmp [winmm.auxGetDevCapsW] } }
    __declspec(naked) void _auxGetNumDevs() { __asm { jmp [winmm.auxGetNumDevs] } }
    __declspec(naked) void _auxGetVolume() { __asm { jmp [winmm.auxGetVolume] } }
    __declspec(naked) void _auxOutMessage() { __asm { jmp [winmm.auxOutMessage] } }
    __declspec(naked) void _auxSetVolume() { __asm { jmp [winmm.auxSetVolume] } }
    __declspec(naked) void _joy32Message() { __asm { jmp [winmm.joy32Message] } }
    __declspec(naked) void _joyConfigChanged() { __asm { jmp [winmm.joyConfigChanged] } }
    __declspec(naked) void _joyGetDevCapsA() { __asm { jmp [winmm.joyGetDevCapsA] } }
    __declspec(naked) void _joyGetDevCapsW() { __asm { jmp [winmm.joyGetDevCapsW] } }
    __declspec(naked) void _joyGetNumDevs() { __asm { jmp [winmm.joyGetNumDevs] } }
    __declspec(naked) void _joyGetPos() { __asm { jmp [winmm.joyGetPos] } }
    __declspec(naked) void _joyGetPosEx() { __asm { jmp [winmm.joyGetPosEx] } }
    __declspec(naked) void _joyGetThreshold() { __asm { jmp [winmm.joyGetThreshold] } }
    __declspec(naked) void _joyReleaseCapture() { __asm { jmp [winmm.joyReleaseCapture] } }
    __declspec(naked) void _joySetCapture() { __asm { jmp [winmm.joySetCapture] } }
    __declspec(naked) void _joySetThreshold() { __asm { jmp [winmm.joySetThreshold] } }
    __declspec(naked) void _mci32Message() { __asm { jmp [winmm.mci32Message] } }
    __declspec(naked) void _mciDriverNotify() { __asm { jmp [winmm.mciDriverNotify] } }
    __declspec(naked) void _mciDriverYield() { __asm { jmp [winmm.mciDriverYield] } }
    __declspec(naked) void _mciExecute() { __asm { jmp [winmm.mciExecute] } }
    __declspec(naked) void _mciFreeCommandResource() { __asm { jmp [winmm.mciFreeCommandResource] } }
    __declspec(naked) void _mciGetCreatorTask() { __asm { jmp [winmm.mciGetCreatorTask] } }
    __declspec(naked) void _mciGetDeviceIDA() { __asm { jmp [winmm.mciGetDeviceIDA] } }
    __declspec(naked) void _mciGetDeviceIDFromElementIDA() { __asm { jmp [winmm.mciGetDeviceIDFromElementIDA] } }
    __declspec(naked) void _mciGetDeviceIDFromElementIDW() { __asm { jmp [winmm.mciGetDeviceIDFromElementIDW] } }
    __declspec(naked) void _mciGetDeviceIDW() { __asm { jmp [winmm.mciGetDeviceIDW] } }
    __declspec(naked) void _mciGetDriverData() { __asm { jmp [winmm.mciGetDriverData] } }
    __declspec(naked) void _mciGetErrorStringA() { __asm { jmp [winmm.mciGetErrorStringA] } }
    __declspec(naked) void _mciGetErrorStringW() { __asm { jmp [winmm.mciGetErrorStringW] } }
    __declspec(naked) void _mciGetYieldProc() { __asm { jmp [winmm.mciGetYieldProc] } }
    __declspec(naked) void _mciLoadCommandResource() { __asm { jmp [winmm.mciLoadCommandResource] } }
    __declspec(naked) void _mciSendCommandA() { __asm { jmp [winmm.mciSendCommandA] } }
    __declspec(naked) void _mciSendCommandW() { __asm { jmp [winmm.mciSendCommandW] } }
    __declspec(naked) void _mciSendStringA() { __asm { jmp [winmm.mciSendStringA] } }
    __declspec(naked) void _mciSendStringW() { __asm { jmp [winmm.mciSendStringW] } }
    __declspec(naked) void _mciSetDriverData() { __asm { jmp [winmm.mciSetDriverData] } }
    __declspec(naked) void _mciSetYieldProc() { __asm { jmp [winmm.mciSetYieldProc] } }
    __declspec(naked) void _mid32Message() { __asm { jmp [winmm.mid32Message] } }
    __declspec(naked) void _midiConnect() { __asm { jmp [winmm.midiConnect] } }
    __declspec(naked) void _midiDisconnect() { __asm { jmp [winmm.midiDisconnect] } }
    __declspec(naked) void _midiInAddBuffer() { __asm { jmp [winmm.midiInAddBuffer] } }
    __declspec(naked) void _midiInClose() { __asm { jmp [winmm.midiInClose] } }
    __declspec(naked) void _midiInGetDevCapsA() { __asm { jmp [winmm.midiInGetDevCapsA] } }
    __declspec(naked) void _midiInGetDevCapsW() { __asm { jmp [winmm.midiInGetDevCapsW] } }
    __declspec(naked) void _midiInGetErrorTextA() { __asm { jmp [winmm.midiInGetErrorTextA] } }
    __declspec(naked) void _midiInGetErrorTextW() { __asm { jmp [winmm.midiInGetErrorTextW] } }
    __declspec(naked) void _midiInGetID() { __asm { jmp [winmm.midiInGetID] } }
    __declspec(naked) void _midiInGetNumDevs() { __asm { jmp [winmm.midiInGetNumDevs] } }
    __declspec(naked) void _midiInMessage() { __asm { jmp [winmm.midiInMessage] } }
    __declspec(naked) void _midiInOpen() { __asm { jmp [winmm.midiInOpen] } }
    __declspec(naked) void _midiInPrepareHeader() { __asm { jmp [winmm.midiInPrepareHeader] } }
    __declspec(naked) void _midiInReset() { __asm { jmp [winmm.midiInReset] } }
    __declspec(naked) void _midiInStart() { __asm { jmp [winmm.midiInStart] } }
    __declspec(naked) void _midiInStop() { __asm { jmp [winmm.midiInStop] } }
    __declspec(naked) void _midiInUnprepareHeader() { __asm { jmp [winmm.midiInUnprepareHeader] } }
    __declspec(naked) void _midiOutCacheDrumPatches() { __asm { jmp [winmm.midiOutCacheDrumPatches] } }
    __declspec(naked) void _midiOutCachePatches() { __asm { jmp [winmm.midiOutCachePatches] } }
    __declspec(naked) void _midiOutClose() { __asm { jmp [winmm.midiOutClose] } }
    __declspec(naked) void _midiOutGetDevCapsA() { __asm { jmp [winmm.midiOutGetDevCapsA] } }
    __declspec(naked) void _midiOutGetDevCapsW() { __asm { jmp [winmm.midiOutGetDevCapsW] } }
    __declspec(naked) void _midiOutGetErrorTextA() { __asm { jmp [winmm.midiOutGetErrorTextA] } }
    __declspec(naked) void _midiOutGetErrorTextW() { __asm { jmp [winmm.midiOutGetErrorTextW] } }
    __declspec(naked) void _midiOutGetID() { __asm { jmp [winmm.midiOutGetID] } }
    __declspec(naked) void _midiOutGetNumDevs() { __asm { jmp [winmm.midiOutGetNumDevs] } }
    __declspec(naked) void _midiOutGetVolume() { __asm { jmp [winmm.midiOutGetVolume] } }
    __declspec(naked) void _midiOutLongMsg() { __asm { jmp [winmm.midiOutLongMsg] } }
    __declspec(naked) void _midiOutMessage() { __asm { jmp [winmm.midiOutMessage] } }
    __declspec(naked) void _midiOutOpen() { __asm { jmp [winmm.midiOutOpen] } }
    __declspec(naked) void _midiOutPrepareHeader() { __asm { jmp [winmm.midiOutPrepareHeader] } }
    __declspec(naked) void _midiOutReset() { __asm { jmp [winmm.midiOutReset] } }
    __declspec(naked) void _midiOutSetVolume() { __asm { jmp [winmm.midiOutSetVolume] } }
    __declspec(naked) void _midiOutShortMsg() { __asm { jmp [winmm.midiOutShortMsg] } }
    __declspec(naked) void _midiOutUnprepareHeader() { __asm { jmp [winmm.midiOutUnprepareHeader] } }
    __declspec(naked) void _midiStreamClose() { __asm { jmp [winmm.midiStreamClose] } }
    __declspec(naked) void _midiStreamOpen() { __asm { jmp [winmm.midiStreamOpen] } }
    __declspec(naked) void _midiStreamOut() { __asm { jmp [winmm.midiStreamOut] } }
    __declspec(naked) void _midiStreamPause() { __asm { jmp [winmm.midiStreamPause] } }
    __declspec(naked) void _midiStreamPosition() { __asm { jmp [winmm.midiStreamPosition] } }
    __declspec(naked) void _midiStreamProperty() { __asm { jmp [winmm.midiStreamProperty] } }
    __declspec(naked) void _midiStreamRestart() { __asm { jmp [winmm.midiStreamRestart] } }
    __declspec(naked) void _midiStreamStop() { __asm { jmp [winmm.midiStreamStop] } }
    __declspec(naked) void _mixerClose() { __asm { jmp [winmm.mixerClose] } }
    __declspec(naked) void _mixerGetControlDetailsA() { __asm { jmp [winmm.mixerGetControlDetailsA] } }
    __declspec(naked) void _mixerGetControlDetailsW() { __asm { jmp [winmm.mixerGetControlDetailsW] } }
    __declspec(naked) void _mixerGetDevCapsA() { __asm { jmp [winmm.mixerGetDevCapsA] } }
    __declspec(naked) void _mixerGetDevCapsW() { __asm { jmp [winmm.mixerGetDevCapsW] } }
    __declspec(naked) void _mixerGetID() { __asm { jmp [winmm.mixerGetID] } }
    __declspec(naked) void _mixerGetLineControlsA() { __asm { jmp [winmm.mixerGetLineControlsA] } }
    __declspec(naked) void _mixerGetLineControlsW() { __asm { jmp [winmm.mixerGetLineControlsW] } }
    __declspec(naked) void _mixerGetLineInfoA() { __asm { jmp [winmm.mixerGetLineInfoA] } }
    __declspec(naked) void _mixerGetLineInfoW() { __asm { jmp [winmm.mixerGetLineInfoW] } }
    __declspec(naked) void _mixerGetNumDevs() { __asm { jmp [winmm.mixerGetNumDevs] } }
    __declspec(naked) void _mixerMessage() { __asm { jmp [winmm.mixerMessage] } }
    __declspec(naked) void _mixerOpen() { __asm { jmp [winmm.mixerOpen] } }
    __declspec(naked) void _mixerSetControlDetails() { __asm { jmp [winmm.mixerSetControlDetails] } }
    __declspec(naked) void _mmDrvInstall() { __asm { jmp [winmm.mmDrvInstall] } }
    __declspec(naked) void _mmGetCurrentTask() { __asm { jmp [winmm.mmGetCurrentTask] } }
    __declspec(naked) void _mmTaskBlock() { __asm { jmp [winmm.mmTaskBlock] } }
    __declspec(naked) void _mmTaskCreate() { __asm { jmp [winmm.mmTaskCreate] } }
    __declspec(naked) void _mmTaskSignal() { __asm { jmp [winmm.mmTaskSignal] } }
    __declspec(naked) void _mmTaskYield() { __asm { jmp [winmm.mmTaskYield] } }
    __declspec(naked) void _mmioAdvance() { __asm { jmp [winmm.mmioAdvance] } }
    __declspec(naked) void _mmioAscend() { __asm { jmp [winmm.mmioAscend] } }
    __declspec(naked) void _mmioClose() { __asm { jmp [winmm.mmioClose] } }
    __declspec(naked) void _mmioCreateChunk() { __asm { jmp [winmm.mmioCreateChunk] } }
    __declspec(naked) void _mmioDescend() { __asm { jmp [winmm.mmioDescend] } }
    __declspec(naked) void _mmioFlush() { __asm { jmp [winmm.mmioFlush] } }
    __declspec(naked) void _mmioGetInfo() { __asm { jmp [winmm.mmioGetInfo] } }
    __declspec(naked) void _mmioInstallIOProcA() { __asm { jmp [winmm.mmioInstallIOProcA] } }
    __declspec(naked) void _mmioInstallIOProcW() { __asm { jmp [winmm.mmioInstallIOProcW] } }
    __declspec(naked) void _mmioOpenA() { __asm { jmp [winmm.mmioOpenA] } }
    __declspec(naked) void _mmioOpenW() { __asm { jmp [winmm.mmioOpenW] } }
    __declspec(naked) void _mmioRead() { __asm { jmp [winmm.mmioRead] } }
    __declspec(naked) void _mmioRenameA() { __asm { jmp [winmm.mmioRenameA] } }
    __declspec(naked) void _mmioRenameW() { __asm { jmp [winmm.mmioRenameW] } }
    __declspec(naked) void _mmioSeek() { __asm { jmp [winmm.mmioSeek] } }
    __declspec(naked) void _mmioSendMessage() { __asm { jmp [winmm.mmioSendMessage] } }
    __declspec(naked) void _mmioSetBuffer() { __asm { jmp [winmm.mmioSetBuffer] } }
    __declspec(naked) void _mmioSetInfo() { __asm { jmp [winmm.mmioSetInfo] } }
    __declspec(naked) void _mmioStringToFOURCCA() { __asm { jmp [winmm.mmioStringToFOURCCA] } }
    __declspec(naked) void _mmioStringToFOURCCW() { __asm { jmp [winmm.mmioStringToFOURCCW] } }
    __declspec(naked) void _mmioWrite() { __asm { jmp [winmm.mmioWrite] } }
    __declspec(naked) void _mmsystemGetVersion() { __asm { jmp [winmm.mmsystemGetVersion] } }
    __declspec(naked) void _mod32Message() { __asm { jmp [winmm.mod32Message] } }
    __declspec(naked) void _mxd32Message() { __asm { jmp [winmm.mxd32Message] } }
    __declspec(naked) void _sndPlaySoundA() { __asm { jmp [winmm.sndPlaySoundA] } }
    __declspec(naked) void _sndPlaySoundW() { __asm { jmp [winmm.sndPlaySoundW] } }
    __declspec(naked) void _tid32Message() { __asm { jmp [winmm.tid32Message] } }
    __declspec(naked) void _timeBeginPeriod() { __asm { jmp [winmm.timeBeginPeriod] } }
    __declspec(naked) void _timeEndPeriod() { __asm { jmp [winmm.timeEndPeriod] } }
    __declspec(naked) void _timeGetDevCaps() { __asm { jmp [winmm.timeGetDevCaps] } }
    __declspec(naked) void _timeGetSystemTime() { __asm { jmp [winmm.timeGetSystemTime] } }
    __declspec(naked) void _timeGetTime() { __asm { jmp [winmm.timeGetTime] } }
    __declspec(naked) void _timeKillEvent() { __asm { jmp [winmm.timeKillEvent] } }
    __declspec(naked) void _timeSetEvent() { __asm { jmp [winmm.timeSetEvent] } }
    __declspec(naked) void _waveInAddBuffer() { __asm { jmp [winmm.waveInAddBuffer] } }
    __declspec(naked) void _waveInClose() { __asm { jmp [winmm.waveInClose] } }
    __declspec(naked) void _waveInGetDevCapsA() { __asm { jmp [winmm.waveInGetDevCapsA] } }
    __declspec(naked) void _waveInGetDevCapsW() { __asm { jmp [winmm.waveInGetDevCapsW] } }
    __declspec(naked) void _waveInGetErrorTextA() { __asm { jmp [winmm.waveInGetErrorTextA] } }
    __declspec(naked) void _waveInGetErrorTextW() { __asm { jmp [winmm.waveInGetErrorTextW] } }
    __declspec(naked) void _waveInGetID() { __asm { jmp [winmm.waveInGetID] } }
    __declspec(naked) void _waveInGetNumDevs() { __asm { jmp [winmm.waveInGetNumDevs] } }
    __declspec(naked) void _waveInGetPosition() { __asm { jmp [winmm.waveInGetPosition] } }
    __declspec(naked) void _waveInMessage() { __asm { jmp [winmm.waveInMessage] } }
    __declspec(naked) void _waveInOpen() { __asm { jmp [winmm.waveInOpen] } }
    __declspec(naked) void _waveInPrepareHeader() { __asm { jmp [winmm.waveInPrepareHeader] } }
    __declspec(naked) void _waveInReset() { __asm { jmp [winmm.waveInReset] } }
    __declspec(naked) void _waveInStart() { __asm { jmp [winmm.waveInStart] } }
    __declspec(naked) void _waveInStop() { __asm { jmp [winmm.waveInStop] } }
    __declspec(naked) void _waveInUnprepareHeader() { __asm { jmp [winmm.waveInUnprepareHeader] } }
    __declspec(naked) void _waveOutBreakLoop() { __asm { jmp [winmm.waveOutBreakLoop] } }
    __declspec(naked) void _waveOutClose() { __asm { jmp [winmm.waveOutClose] } }
    __declspec(naked) void _waveOutGetDevCapsA() { __asm { jmp [winmm.waveOutGetDevCapsA] } }
    __declspec(naked) void _waveOutGetDevCapsW() { __asm { jmp [winmm.waveOutGetDevCapsW] } }
    __declspec(naked) void _waveOutGetErrorTextA() { __asm { jmp [winmm.waveOutGetErrorTextA] } }
    __declspec(naked) void _waveOutGetErrorTextW() { __asm { jmp [winmm.waveOutGetErrorTextW] } }
    __declspec(naked) void _waveOutGetID() { __asm { jmp [winmm.waveOutGetID] } }
    __declspec(naked) void _waveOutGetNumDevs() { __asm { jmp [winmm.waveOutGetNumDevs] } }
    __declspec(naked) void _waveOutGetPitch() { __asm { jmp [winmm.waveOutGetPitch] } }
    __declspec(naked) void _waveOutGetPlaybackRate() { __asm { jmp [winmm.waveOutGetPlaybackRate] } }
    __declspec(naked) void _waveOutGetPosition() { __asm { jmp [winmm.waveOutGetPosition] } }
    __declspec(naked) void _waveOutGetVolume() { __asm { jmp [winmm.waveOutGetVolume] } }
    __declspec(naked) void _waveOutMessage() { __asm { jmp [winmm.waveOutMessage] } }
    __declspec(naked) void _waveOutOpen() { __asm { jmp [winmm.waveOutOpen] } }
    __declspec(naked) void _waveOutPause() { __asm { jmp [winmm.waveOutPause] } }
    __declspec(naked) void _waveOutPrepareHeader() { __asm { jmp [winmm.waveOutPrepareHeader] } }
    __declspec(naked) void _waveOutReset() { __asm { jmp [winmm.waveOutReset] } }
    __declspec(naked) void _waveOutRestart() { __asm { jmp [winmm.waveOutRestart] } }
    __declspec(naked) void _waveOutSetPitch() { __asm { jmp [winmm.waveOutSetPitch] } }
    __declspec(naked) void _waveOutSetPlaybackRate() { __asm { jmp [winmm.waveOutSetPlaybackRate] } }
    __declspec(naked) void _waveOutSetVolume() { __asm { jmp [winmm.waveOutSetVolume] } }
    __declspec(naked) void _waveOutUnprepareHeader() { __asm { jmp [winmm.waveOutUnprepareHeader] } }
    __declspec(naked) void _waveOutWrite() { __asm { jmp [winmm.waveOutWrite] } }
    __declspec(naked) void _wid32Message() { __asm { jmp [winmm.wid32Message] } }
    __declspec(naked) void _wod32Message() { __asm { jmp [winmm.wod32Message] } }
}


// 检查当前进程是否是目标进程
bool IsTargetProcess(const char* targetName) {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    
    // 获取文件名部分
    std::string path(exePath);
    size_t pos = path.find_last_of("\\/");
    std::string exeName = (pos != std::string::npos) ? path.substr(pos + 1) : path;
    
    // 转换为小写进行比较
    std::transform(exeName.begin(), exeName.end(), exeName.begin(), ::tolower);
    std::string target(targetName);
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);
    
    return exeName == target;
}

// 获取进程所在目录
std::string GetProcessDirectory() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    
    std::string path(exePath);
    size_t pos = path.find_last_of("\\/");
    if (pos != std::string::npos) {
        return path.substr(0, pos + 1);
    }
    return "";
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    static HMODULE hOriginalDll = NULL;
   
    
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        
        // 加载系统目录下的原始 winmm.dll
        {
            char systemPath[MAX_PATH];
            GetSystemDirectoryA(systemPath, MAX_PATH);
            strcat_s(systemPath, "\\winmm.dll");
            
            hOriginalDll = LoadLibraryA(systemPath);
            if (hOriginalDll) {
                winmm.LoadOriginalLibrary(hOriginalDll);
            }
        }
        
        // 检查是否是目标进程 isaac-ng.exe
        if (IsTargetProcess("isaac-ng.exe")) {
            // 构建 p2p_hook.dll 的完整路径
            std::string dllPath = GetProcessDirectory() + "p2p_hook.dll";
            HMODULE hDll = LoadLibraryA(dllPath.c_str());
            if (hDll == NULL) {
                // 可选：记录错误日志
                // OutputDebugStringA(("Failed to load: " + dllPath).c_str());
            }
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
