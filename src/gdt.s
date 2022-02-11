global asm_load_gdt

section .bss
gdtr resb 48

section .text
asm_load_gdt:
push ebp
mov ebp, esp

mov eax, [esp + 2 * 4]
mov [gdtr+2], eax
mov eax, [esp + 3 * 4]
mov [gdtr], ax
lgdt [gdtr]

jmp 0x8:.reload_cs ; See gdt.c
.reload_cs:
mov ax, 0x10
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax

mov esp, ebp
pop ebp
ret