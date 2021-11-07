use16

global boot

section .data
msg	db	"text from src/boot.s", 0
fmt	db	0x07

section .boot
boot_mark	db	0xAA, 0x55

section .text
boot:	cli
	mov	eax,	fmt
	push	eax
	mov	eax,	msg
	push	eax
	call	print.prologue
	call	print
	call	print.epilogue
boot.end:
	jmp	boot.end

getmem.prologue:
	sti
	ret

getmem.epilogue:
	cli
	ret

getmem:	int	0x12
	ret

strlen.prologue:
	push	ebx
	push	ebp
	mov	ebp,	esp
	sub	ebp,	12	; ebp, ebx, ret_addr, value <-- HERE
	ret

strlen.epilogue:
	pop	ebp
	pop	ebx
	ret

strlen:
	xor	eax,	eax
strlen.begin:
	mov	bh,	[ebp]	
	cmp	bh,	0
	je	strlen.end
	inc	ebp
	inc	eax
	jmp	strlen.begin
strlen.end:
	ret

print.prologue:
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	ebp
	mov	ebp,	esp
	sub	ebp,	28	; ebp, edx, ecx, ebx, eax, ret_addr, FMT, VAL <-- HERE
	sti
	ret

print.epilogue:
	pop	ebp
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	cli
	ret

print:
	mov	bh,	0
	mov	bl,	[ebp + 4]
	mov	ebp,	[ebp]
	push	ebp
	call	strlen.prologue
	call	strlen
	call	strlen.epilogue
	mov	cx,	ax
	mov	dx,	0	
	mov	ah,	0x13
	mov	al,	1
	int	0x10
	ret	
