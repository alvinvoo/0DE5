#include <stdio.h>
#include <string.h>

void bin(char *buffer, char c)
{
  char temp[8] = {};
  for (int b = 7; b >= 0; b--)
  {
    // start printing from most significant bit first
    int bit = (c >> b) & 0b00000001;
    sprintf(&temp[7 - b], "%u", bit);
  }
  // maxlen needs to plus 1 needs to include null terminator
  snprintf(buffer, 9, "%s", temp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *str = argv[1];

    printf("ASCII:");
    for (int i=0; i< strlen(str); i++) {
      printf("      %c", str[i]);
    }
    printf("\n");
    printf("Hex:");
    for (int i=0; i< strlen(str); i++) {
      printf("      %3X", str[i]);
    }
    printf("\n");
    printf("Dec:");
    for (int i=0; i< strlen(str); i++) {
      printf("      %u", str[i]);
    }
    printf("\n");
    printf("Bin:");
    for (int i = 0; i < strlen(str); i++) {
      printf("     ");

      // CAREFUL: need to include null terminator
      char res[9] = {};
      bin(res, str[i]);
      printf("%s", res);
    }
}
