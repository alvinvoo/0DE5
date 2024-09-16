## How to modify instructions in memory using Radare2
0. To compile with no optimization, `gcc -O0 -g -o welcome ./welcome.c`
1. `r2 -w -d -r profile.rr2 -e log.level=0 -d welcome`
  - -d is debug mode, will print out stdout
  - -w is write mode, able to modify memory 
2. use `v` to go into Visual mode (Radare2 shell)
3. inside the shell, type `:` to bring up command prompt 
4. `s main` to seek for main function
  - and to point RIP at that address
5. click any address or reference to be directed
6. go to `str.Welcome_to__04X_n` section
7. `s 0x560030c08004`, lets say `0x560030c08004` is the address
8. use `ps 17` to check the next 17 bytes string 
9. can also use `pD 17` but this is dissemblying, so output is same as per visual
10. can directly amend the bytes 
  - `w 57656c636f6d6520746f20616263640a00`
  - `wx 57656c636f6d6520746f20616263640a00`
  - `wz Welcome to abcd\n`
  - note that there's a null 0x00 terminator (1 byte) behind the string
11. if want to update the binary file, type `w` again
12. to debug
  - `db <address>` to place break points
  - `dc` to continue until break point
  - in visual mode, press `s` to step into, `S` to step over
  - no idea what's hot key for placing break points at RIP yet

## Notes
1. Registers in x86-64:

    rax is a 64-bit register.
    eax is the lower 32 bits of the rax register. In x86-64, if you write to the eax register, it automatically zeroes out the upper 32 bits of rax.

## Resource
https://www.0de5.net/stimuli/a-reintroduction-to-programming/essentials/about-0de5-and-the-core-ideas