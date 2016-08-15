PREFIX=powerpc-none-eabi-
BINARY=test
FILES=entry test
OBJS=$(addsuffix .o, $(FILES))


all: $(BINARY).bin

clean:
	rm -f $(BINARY).bin
	rm -f $(BINARY).elf
	rm -f *.o

$(BINARY).bin: $(BINARY).elf
	$(PREFIX)objcopy -O binary $< $@
	$(PREFIX)objdump -d $<

$(BINARY).elf: $(OBJS)
	$(PREFIX)gcc -T linker.ld -o $@ -mcpu=405 -ffreestanding -O2 -nostdlib $^

%.o: %.c
	$(PREFIX)gcc -c $< -o $@ -mcpu=405 -ffreestanding -O2 -Wall

