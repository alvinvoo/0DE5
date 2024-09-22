#include <stdio.h>
#include "lib.c"

int main() {
  struct Bitmap bitmap = init_bitmap(15, 15);
  fill(&bitmap, 0, 0, 14, 1, 0xFF0000);
  fill(&bitmap, 0, 2, 14, 3, 0xF5A988);
  fill(&bitmap, 0, 13, 14, 14, 0x58CEFA);
  write_bitmap(&bitmap, "out.bmp");

  free_bitmap(&bitmap);

  return 0;
}