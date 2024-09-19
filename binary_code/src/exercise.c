#include <stdio.h>

int main() {
  unsigned char bytes[25] = {
      0b01001101,
      0x79,
      0b00100000,
      0b01101110,
      0x61,
      0x6D,
      0b01100101,
      0x20,
      0x69,
      0x73,
      0b00101110,
      '.',
      0b00101110,
      0b00100000,
      'A',
      'l',
      'v',
      'i',
      'n',
      '.',
      '\0'
  };

  for (int i = 0; i < sizeof(bytes); i++) {
    printf("[%2u]  ", i);
    // binary
    for (int b = 7; b >= 0; b--) {
      // start printing from most significant bit first
      int bit = (bytes[i] >> b) & 0b00000001;
      printf("%u", bit);
    }

    printf("  %2x   %3u  %5c\n", bytes[i], bytes[i], bytes[i]);
  }

  printf("%s \n", bytes);
}