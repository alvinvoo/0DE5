## Notes
### On memory (Physically RAM)
1. Data Section
  - for string/array literals (static data) in code
  - also for code (instructions)
2. Stack Memory
  - for local function variables
3. Heap (potential memory leak)
  - for allocated, resizeable (dynamic), data structures

## Others
1. Size of a pointer is 8 bytes (on 64 bits system)
  - a charater pointer, char *ptr
  - this points at one location only
  - *ptr, this deferences the pointer (return one char)
  - &ptr, this gets the address of the pointer (i.e. char **ptr)

## Resources
https://www.0de5.net/stimuli/a-reintroduction-to-programming/essentials/just-enough-c-to-have-fun