ifdef CROSS
_CROSS=${CROSS}
else
$(warning No provoded $$CROSS)
endif

CC=$(_CROSS)/bin/i686-elf-gcc
AS=nasm
LD=$(_CROSS)/bin/i686-elf-ld
OBJCOPY=$(_CROSS)/bin/i686-elf-objcopy
PP=$(_CROSS)/bin/i686-elf-cpp

CCFLAGS=-c -ffreestanding -fno-exceptions -I./include $(CMD_DEF) -g -ggdb
ASFLAGS=-felf
LDFLAGS=-L$(_CROSS)/lib -L$(_CROSS)/lib/gcc/i686-elf/11.2.0 -lgcc -nostdlib

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
	$(LD) $(LDFLAGS) -T src/link.ld -o bin/kernel $(wildcard bin/*.o)

all: bin/kernel
	
image: bin/kernel
	$(OBJCOPY) --strip-debug bin/kernel bin/kernel.elf

vm: image
	qemu-system-i386 -m 64m -kernel bin/kernel.elf -curses -serial file:serial.log $(CMD_VM)

blink_vm: image
	qemu-system-i386 -m 80m -kernel bin/kernel.elf -display none -serial stdio $(CMD_VM)

debug: image
	qemu-system-i386 -m 64m -kernel bin/kernel.elf -display none -s -S -serial file:serial.log $(CMD_VM)
