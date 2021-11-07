CC=../cross/bin/i686-elf-gcc
AS=nasm
LD=../cross/bin/i686-elf-ld
OBJCOPY=../cross/bin/i686-elf-objcopy
PP=../cross/bin/i686-elf-cpp

CCFLAGS=-c -ffreestanding -fno-exceptions -I./include $(CMD_DEF) 
ASFLAGS=-felf
LDFLAGS=-L../cross/lib -L../cross/lib/gcc/i686-elf/12.0.0 -lgcc -nostdlib

CCFILES=$(addprefix bin/, $(notdir $(wildcard src/*.c) ) )
ASFILES=$(addprefix bin/, $(notdir $(wildcard src/*.s) ) )

.DEFAULT_GOAL = all
.PHONY = push clean vm

ifeq "$(MANUAL)" 'true'
CMD_DEF := -DMANUAL_BOOT
endif

push: clean
	git add *
	git commit
	git push

clean: 
	rm -r bin/*

bin/%.c.o: src/%.c
	$(CC) $(CCFLAGS) $(addprefix src/, $(notdir $? ) ) -o $@

bin/%.s.o: src/%.s
	$(AS) $(ASFLAGS) $(addprefix src/, $(notdir $? ) ) -o $@

bin/kernel: $(addsuffix .o, $(CCFILES) $(ASFILES))
	$(PP) src/link.ld -o bin/link $(CMD_DEF)
	$(LD) $(LDFLAGS) -T bin/link -o bin/kernel $(wildcard bin/*.o)

all: bin/kernel
	
image: bin/kernel
	$(OBJCOPY) -O binary bin/kernel bin/fda.bin

vm: image
	qemu-system-i386 -fda bin/fda.bin
