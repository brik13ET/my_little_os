all:
	git push os master
	fasm src/main.asm bin/main.o
	gcc -m32 src/main.c -c -o bin/c_main.o
	ld -m elf_i386 -T src/link.ld -o bin/kernel bin/main.o bin/c_main.o

vm:
	qemu-system-x86_64 -kernel bin/kernel