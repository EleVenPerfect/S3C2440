objs := head.o init.o serial.o main.o

000.bin: $(objs)
	arm-linux-ld -Ttext 0x000000 -o timer_elf $^
	arm-linux-objcopy -O binary -S timer_elf $@
	arm-linux-objdump -D -m arm timer_elf > timer.dis
	
%.o:%.c
	arm-linux-gcc -Wall -nostdlib -O2 -c -o $@ $<

%.o:%.S
	arm-linux-gcc -Wall -nostdlib -O2 -c -o $@ $<

clean:
	rm -f timer.bin timer_elf timer.dis *.o		
	