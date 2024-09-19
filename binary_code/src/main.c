#include <stdio.h>

int main() {
  unsigned char bytes[10] = {};

  bytes[0] = 0b00000011;

  bytes[1] = 72;

  // 72 / 2 = 36 r 0 least significant bit
  // 36 / 2 = 18 r 0
  // 18 / 2 = 9 r 0
  // 9 / 2 = 4 r 1
  // 4 / 2 = 2 r 0
  // 2 / 2 = 1 r 0
  // 1 / 2 = 0 r 1    most significant bit

  // intuition 1: how to get 72 into binary format
  // think of a loop that bitshift from the least significant bit to the most
  // i.e. bitshift from right to left
  // every bitshift is effectively a division by 2 and discarding the remainder
  bytes[2] = 0b1001000;

  // multiply by 2, bitshift a 0 to right 
  bytes[3] = 0b10010000;

  // divide by 2, bitshift a 0 to left 
  // similar to base 10, by shifting a 0 to left (decrease by 10x), 0 to right (increase by 10x)
  bytes[4] = 0b0100100;

  bytes[5] = 0x65;
  bytes[6] = 108;
  // this is actually octal, 0o154, just unfortunately it's represented by a specifier `0` in C and JS
  bytes[7] = 0154;
  // lower case `h`, just by changing 6th bit (refer to saved Screenshot.jpg)
  bytes[8] = 0b01101000;
  bytes[9] = 'o';

  printf(" Idx  Dec Hex  Oct       Bin  C\n");
  printf("----  --- ---  ---  --------  -\n");
  for (int i = 0; i< 10; i++) {
    printf("[%2u]  %3u  %2x  %3o  ", i , bytes[i], bytes[i], bytes[i]);

    for (int b = 7; b >= 0; b--) {
      // start printing from most significant bit first
      int bit = (bytes[i] >> b) & 0b00000001;
      printf("%u", bit);
    }

    printf("  %c\n", bytes[i]);
  }

  printf("'%s'\n", bytes);

  return 0;
}