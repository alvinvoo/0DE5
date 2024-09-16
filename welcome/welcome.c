#include <stdio.h>

/*
* RSP - Stack Pointer
* RBP - Stack Base Pointer

* opcode: 55 is `push rbp`
* its a one byte opcode that corresponds to the instruction `push rbp`
50 – push rax
51 – push rcx
52 – push rdx
55 – push rbp
*/


int make_it_higher(int n) {
  return n + 100 + 20 + 7;
}

int main() {
  int name = 0;

  while (1) {
    name = make_it_higher(name);
    // %04X formats the output to ensure it’s always 4 digits wide and uses uppercase letters for hexadecimal values.
    printf("Welcome to %04X\n", name);
  }
}