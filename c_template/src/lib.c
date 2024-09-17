#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
  // puts("Buffer content before (char by char):\n");
  // for (int i = 0; i < 5; i++) {
  //   printf("buffer[%d] = '%c' (ASCII %d)\n", i, buffer[i], buffer[i]);
  // }

  // pointer buffer only points at the first location
  // trying to dereferencing will just accesses the value at the memory location pointed to by buffer (which would be a char, i.e. first element)
  // so the below will return 1
  // printf("buf len %d \n", sizeof(*buffer));

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

// exercise: fizzbuzz
void fizzbuzz(int n) {
  for (int i=1; i <=n; i++) {
    if (i % 15 == 0) {
      puts("fizzbuzz");
    } else if (i % 5 == 0) {
      puts("buzz");
    } else if (i % 3 == 0) {
      puts("fizz");
    } else {
      printf("%d\n", i);
    }
  }
}

const int MAX_LEN = 200; 
void fizzbuzz2(int n) {
  char result[MAX_LEN] = {0};
  int nextInd = 0; 

  for (int i=1; i <=n; i++) {
    if (i % 15 == 0) {
      char fizzbuzzstr[9] = "fizzbuzz";
      for (int j=0; j<8; j++){
        result[j + nextInd] = fizzbuzzstr[j]; 
      }

      nextInd += 8;

      puts("fizzbuzz");
    } else if (i % 5 == 0) {
      char fizzbuzzstr[5] = "buzz";
      for (int j=0; j<4; j++){
        result[j + nextInd] = fizzbuzzstr[j];
      }

      nextInd += 4; // dont add null terminator, as its a continuation

      puts("buzz");
    } else if (i % 3 == 0) {
      char fizzbuzzstr[5] = "fizz";
      for (int j=0; j<4; j++){
        result[j + nextInd] = fizzbuzzstr[j];
      }

      nextInd += 4;
      
      puts("fizz");
    } else {
      char str[20];
      snprintf(str, 20, "%d", i);
      int len = (int)(log10(i) + 1);

      for (int j=0; j<len; j++){
        result[j + nextInd] = str[j];
      }

      nextInd += len;
      printf("%d\n", i);
    }

    if (i==n) {
      // last char
      result[nextInd] = '.';
    } else {
      result[nextInd++] = ',';
      result[nextInd++] = ' ';
    }
  }

  printf("result: %s\n", result);
}

char snprintf_success(int check, int buflen) {
  return check >=0 && check < buflen;
}

void generate_fizzbuzz(char *buffer, size_t buflen, int upto) {
  for (int i = 1; i <= upto; i++) {
    int check = 0; // serves as a counter as well

    if (i % 15 == 0) {
      check = snprintf(buffer, buflen, "FizzBuzz");
    } else if (i % 5 == 0) {
      check = snprintf(buffer, buflen, "Buzz");
    } else if (i % 3 == 0) {
      check = snprintf(buffer, buflen, "Fizz");
    } else {
      check = snprintf(buffer, buflen, "%d", i);
    }

    buffer += check; // increment the pointer
    buflen -= check; // decrement the maxlen to check

    if (i == upto) {
      check = snprintf(buffer, buflen, ".");
    } else {
      check = snprintf(buffer, buflen, ", ");
    }

    buffer += check;
    buflen -= check; // decrement the maxlen to check

    if (!snprintf_success(check, buflen)) {
      printf("error buffer overflow: <check> %d <buflen> %zu", check, buflen);
      return;
    }
  }
}
