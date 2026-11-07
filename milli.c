#include <windows.h>

// Definizione del tuo carattere personalizzato (8 byte - pattern a scacchiera)
unsigned char customChar[8] = {
  0b01010101,
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101,
  0b10101010
};

// Funzione esportata per restituire il carattere
__declspec(dllexport) void GetCustomChar(unsigned char *dest) {
    for(int i = 0; i < 8; i++) {
        dest[i] = customChar[i];
    }
}

// Punto di ingresso standard per le DLL di Windows
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
