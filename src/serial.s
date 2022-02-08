global serial_write
global serial_init

section .text
serial_init:
    push eax
    push edx
    mov edx, 0x03f9
    mov eax, 0
    out dx, al      ; Disable all interrupts
    
    mov edx, 0x03fb
    mov eax, 0x80
    out dx, al      ; Enable DLAB (set baud rate divisor)
    mov edx, 0x03f8
    mov eax, 0x03
    out dx, al ; Set divisor to 3 (lo byte) 38400 baud
    
    mov edx, 0x03f9
    mov eax, 0
    out dx, al      ;                  (hi byte)
    mov edx, 0x03fb
    mov eax, 0x03
    out dx, al ; 8 bits, no parity, one stop bit
    mov edx, 0x03fa
    mov eax, 0xC7
    out dx, al ; Enable FIFO, clear them, with 14-byte threshold

    mov edx, 0x03fc
    mov eax, 0x0B
    out dx, al      ; IRQs enabled, RTS/DSR set
    mov eax, 0x1E
    out dx, al      ; Set in loopback mode, test the serial chip
    pop edx
    pop eax
ret

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