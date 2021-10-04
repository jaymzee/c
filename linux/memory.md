## i386
stack just under 0x8048000
a little more than 128MB for stack and about 2GB for text and data

kernel up to 1 GB starting at at least 0xC0000000

## amd64
because most instructions still only accept 32-bit immediate operands
the small code model suggests using 0 to 0x7effffff for code and data

stack is just under the shared library space 0x800000000000
