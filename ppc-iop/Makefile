PREFIX=powerpc-none-eabi-
BINARY=ppc_test
FILES=entry
OBJS=$(addsuffix .o, $(FILES))


all: $(BINARY).bin

clean:
	rm -f $(BINARY).bin
	rm -f $(BINARY).elf
	rm -f *.o

debug:
	$(PREFIX)objdump -d $(BINARY).elf

$(BINARY).bin: $(BINARY).elf
	$(PREFIX)objcopy -O binary $< $@

$(BINARY).elf: $(OBJS)
	$(PREFIX)gcc -T linker.ld -o $@ -mcpu=405 -ffreestanding -O2 -nostdlib $^

%.o: %.c
	$(PREFIX)gcc -c $< -o $@ -mcpu=405 -ffreestanding -O2 -Wall

