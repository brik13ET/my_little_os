format ELF
public _start

use32

section '.text' executable
        ;multiboot spec
        align 4
        dd 0x1BADB002            ;magic
        dd 0x00                  ;flags
        dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero

extrn kmain
include "src/io.asm"

section '.bss' writable
stck rb 16384


_start:
	cli
	mov esp, stck
	call kmain
	hlt

