global serial_write

section .text

serial_write:
push ebp
mov ebp, esp

push eax
push ebx
push edx

mov edx, 0x03f8
mov ebx, [ebp + 2 * 4]

.if:
mov al, [ebx]
cmp al, 0
je .end

out dx, al
inc ebx
jmp .if

.end:
pop edx
pop ebx
pop eax

mov esp, ebp
pop ebp
ret