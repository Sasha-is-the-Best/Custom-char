#include <stdio.h>

// Definizione del carattere personalizzato 8x8
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

int main() {
    printf("Carattere personalizzato 8x8 (Scacchiera):\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%c", (customChar[i] & (1 << j)) ? '#' : '.');
        }
        printf("\n");
    }
    return 0;
}
