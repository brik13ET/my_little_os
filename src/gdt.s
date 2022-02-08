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

mov esp, ebp
pop ebp
ret