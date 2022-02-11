global serial_write
global serial_write_len

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

serial_write_len:
enter 12, 0

push eax
push ebx
push edx

mov ebx, [esp + 2 * 4] ; len
mov edx, 0x000003f8
.for:
cmp ebx, 0
je .endfor

lea eax, [esp + 3 * 4]
out dx, al

inc DWORD [esp + 3 * 4]
dec ebx
jmp .for

.endfor:

pop edx
pop ebx
pop eax

leave
ret