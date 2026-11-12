#include <windows.h>
#include <stdio.h>

// Definizione del tuo carattere personalizzato 8x8 (Pattern a scacchiera)
unsigned char customChar[8] = {
  0b01111111,
  0b01010101,
  0b01010101,
  0b00010101,
  0b00010101,
  0b01010101,
  0b01010111,
  0b01010101
};

// Funzione che simula l'invio/stampa del carattere nella finestra attiva
void InviaCarattereAStrisce() {
    // Esempio: Stampa la matrice stilizzata nella console del programma
    printf("\n--- Carattere Attivato (Alt + 3) ---\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%c", (customChar[i] & (1 << j)) ? '#' : '.');
        }
        printf("\n");
    }
    printf("------------------------------------\n");
}

// Funzione di Callback per intercettare i tasti a livello di sistema
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT *)lParam;
        
        // Controlla se il tasto è stato premuto
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            // Verifica se il tasto ALT è premuto
            if ((GetAsyncKeyState(VK_MENU) & 0x8000)) {
                // Impostato su '3' o VK_NUMPAD3 (puoi cambiarlo)
                if (pKeyboard->vkCode == '3' || pKeyboard->vkCode == VK_NUMPAD3) {
                    InviaCarattereAStrisce();
                }
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    // Nasconde o mostra un messaggio di avvio nella console
    printf("=== Programma Hook Attivo ===\n");
    printf("Tieni premuto ALT e premi '3' per stampare il carattere.\n");

    // Imposta l'hook globale sulla tastiera di Windows
    HHOOK hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    if (hKeyboardHook == NULL) {
        MessageBox(NULL, "Errore durante l'installazione dell'hook!", "Errore", MB_ICONERROR);
        return 1;
    }

    // Loop dei messaggi di Windows per mantenere l'ascolto attivo in background
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Rimuove l'hook alla chiusura
    UnhookWindowsHookEx(hKeyboardHook);
    return 0;
}
