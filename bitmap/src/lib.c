#include <stdlib.h>
#include <assert.h>

typedef unsigned int color_t; // warning, we need at least guaranteed 3 bytes to store the colors RGB,
// but C language only guarantee up to 2 byte for `int`; though for most computers nowadays `int` is up to 4 bytes
// might not work for a smaller machine

struct Bitmap {
  int width;
  int height;
  color_t *pixels; // pointer to 1d array of height * width * sizeof(color_t)
  // reminder: pointers only cost 8 bytes
};

struct Bitmap init_bitmap(int width, int height) {
  color_t *pixels = malloc(width * height * sizeof(color_t));
  struct Bitmap bitmap = { .width = width, .height = height, .pixels = pixels};
  return bitmap;
}

void set_pixel(struct Bitmap *bitmap, int x, int y, color_t color) {
  if (x < 0 || x >= bitmap->width || y < 0 || y >= bitmap->height) {
    return;
  }

  bitmap->pixels[y * bitmap->width + x] = color;
}

void fill(struct Bitmap *bitmap, int x1, int y1, int x2, int y2, color_t color) {
  for (int y = y1; y <= y2; y++) {
    for (int x = x1; x <= x2; x++) {
      set_pixel(bitmap, x, y, color);
    }
  }
}

int calc_row_size(int width) {
  // next 4 bytes -> bfSize
  int row_length = width * 3; // RGB
  // each row must be padded in the multiples of 4 bytes
  row_length += 4 - (row_length % 4); // if its 5 pixels, then its 15 + (4 - 3) = 16 bytes

  assert(row_length % 4 == 0);

  return row_length;
}

int calc_image_size(int width, int height) {
  return calc_row_size(width) * height;
}

void write_fileheader(int width, int height, FILE *file) {
  // first 2 bytes - bfType
  fputs("BM", file); // magic file type for bitmap

  int image_size = calc_image_size(width, height);
  int file_size = 14 + 40 + image_size;
  // since this copy the 4 bytes, we need to be mindful of the endianness as bmp needs little endian format
  // but since our (most) computer is little endian based, it will copy correctly
  fwrite(&file_size, 4, 1, file);

  // reserved 4 bytes
  int reserved = 0;
  fwrite(&reserved, 4, 1, file);
  // offset 4 bytes -> 54 bytes offset until data section
  int offset = 14 + 40;
  fwrite(&offset, 4, 1, file);
}

void write_infoheader(int width, int height, FILE *file) {
  int header_size = 40;
  int planes = 1;
  int bits_per_pixel = 24;
  int compression = 0;
  int image_size = calc_image_size(width, height);
  int x_pixels_per_meter = 0;
  int y_pixels_per_meter = 0;
  int colors_used = 0;
  int important_colors_used = 0;
  fwrite(&header_size, 4, 1, file);
  fwrite(&width, 4, 1, file);
  fwrite(&height, 4, 1, file);
  fwrite(&planes, 2, 1, file);
  fwrite(&bits_per_pixel, 2, 1, file);
  fwrite(&compression, 4, 1, file);
  fwrite(&image_size, 4, 1, file);
  fwrite(&x_pixels_per_meter, 4, 1, file);
  fwrite(&y_pixels_per_meter, 4, 1, file);
  fwrite(&colors_used, 4, 1, file);
  fwrite(&important_colors_used, 4, 1, file);
}

void write_pixeldata(struct Bitmap *bitmap, FILE *file) {
  int row_size = calc_row_size(bitmap->width);

  // renders from bottoms up, left to right
  for (int y = bitmap->height - 1; y >= 0; y--) {
    for (int x = 0; x < bitmap->width; x++) {
      color_t color = bitmap->pixels[y * bitmap->width + x];
      unsigned char red = (color & 0xFF0000) >> 16;
      unsigned char green = (color & 0x00FF00) >> 8;
      unsigned char blue = color & 0x0000FF;
      // little endianness will just grab the least significant byte
      fwrite(&blue, 1, 1, file);
      fwrite(&green, 1, 1, file);
      fwrite(&red, 1, 1, file);
    }
    for (int i = bitmap->width * 3; i < row_size; i++) {
      fputc(0, file); // padding
    }
  }
}

void write_bitmap(struct Bitmap *bitmap, const char *filename) {
  FILE *file = fopen(filename, "wb");
  if (file == NULL) {
    return;
  }

  write_fileheader(bitmap->width, bitmap->height, file);
  write_infoheader(bitmap->width, bitmap->height, file);
  write_pixeldata(bitmap, file);

  fclose(file);
}

void free_bitmap(struct Bitmap *bitmap) {
  // if passing by value, then it would make a _copy_ of `bitmap` here instead
  // the pointer bitmap.pixels would be a _copy_ with still the correct memory address of the original
  free(bitmap->pixels);
  bitmap->pixels = NULL;
}