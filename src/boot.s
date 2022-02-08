global setup_stack
global error_handler
global _start


extern process_boot_info ; retun amount of memory
extern error_handler
extern kmain

section .bss 
tmp_stack_top resb 2048
tmp_stack_bottom:

section .text
_start:
cmp eax, 0x2BADB002
jne error_handler

mov esp, tmp_stack_bottom
push ebx
call process_boot_info
push eax
call setup_stack
call kmain
hlt

setup_stack:
pop eax
pop ebx
mov esp, ebx
push eax
ret

error_handler:
    hlt