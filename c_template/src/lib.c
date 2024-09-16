#include <stdlib.h>
#include <string.h>

int add(int a, int b) {
  return a + b;
}

// problem: returning strings
// char *a is same as char a[], which is the syntax sugar
// a bit weird, considering Golang is []char a
// problem: whatever data stored in stack memory in this function will be cleaned up afterwards
// "cleaned up" - means will be "reused" by somebody else, and filled with gibberish data
char *my_strcat(char *a, char *b) {
  char buffer[5] = {0};
  sprintf(buffer, "%s%s", a, b);
  return buffer; // returning pointer to buffer; whereby the content would later be cleaned up
}

// solution 1: pass in a buffer pointer, the buffer content will be modified directly
// this is also a common pattern used in Golang (if you know the buffer size b4hand)
// new problem: if a or b exceeds the buffer size, there will be buffer overflow
void my_strcat1(char buffer[], char a[], char b[]) {
  sprintf(buffer, "%s%s", a, b);
}

// solution 1: better, we specify the size
// snprintf will cut off at exact specified size
void my_strcat_better1(char *buffer, size_t buflen, char *a, char *b) {
  snprintf(buffer, buflen, "%s%s", a, b);
}

// solution 2: allocate heap memory
// problem: the caller needs to free the allocated heap memory
// else memory leak
// but no choice, if want dynamic memory; let's say if we want the buffer to
// fully encompass a + b but we dunno the sizes of them at first
char *my_strcat_heap(char *a, char *b) {
  char *result = malloc((strlen(a) + strlen(b) + 1) * sizeof(char));
  sprintf(result, "%s%s", a, b);
  return result;
}