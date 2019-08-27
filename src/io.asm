public print
public read
public strlen
public clear

; get char*
print: ; 0xb8000
push ebp
mov ebp,esp
push eax
push ebx
xor eax,eax
xor ebx,ebx

; push [ebp+8]
; call strlen
; pop eax
.iter:
	inc ebx
	mov	eax, [ebp+4+ebx]
	mov	[0xb8000+ebx*2], eax
	mov	byte [0xb8001+ebx*2],0x07
	cmp eax, 0
	jne .iter
pop ebx
pop eax
leave
ret

clear:
	push ebp
	mov ebp, esp
	push eax
	xor eax, eax
	.iter:
		inc eax
		mov BYTE [0xb8000+(eax*2)], ' '
		mov BYTE [0xb8000+(eax*2)+1], 0x07
		cmp eax, 80*25;
		jne .iter
	pop eax
	leave
ret

; ret char*
read:
push ebp
mov ebp,esp


leave
ret

; get char*
strlen:
push ebp
mov ebp,esp
push eax
xor eax, eax
.iter:
	inc DWORD [ebp-4]
	add eax, 4
	cmp BYTE [ebp+8+eax], 0
	jne .iter
pop eax
leave
ret