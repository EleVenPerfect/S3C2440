clock.bin : head.S clock.c leds.c
	arm-linux-gcc -nostdlib -c -o head.o head.S
	arm-linux-gcc -nostdlib -c -o clock.o clock.c
	arm-linux-gcc -nostdlib -c -o leds.o leds.c
	arm-linux-ld -Ttext 0x30000000 head.o clock.o leds.o -o sdram_elf
	arm-linux-objcopy -O binary -S sdram_elf clock.bin
	arm-linux-objdump -D -m arm  sdram_elf > clock.dis
clean:
	rm -f   sdram.dis sdram.bin sdram_elf *.o
