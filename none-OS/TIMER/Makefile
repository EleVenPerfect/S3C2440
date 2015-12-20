LIBPATH=-static  -L /opt/EmbedSky/4.3.3/lib/gcc/arm-none-linux-gnueabi/4.3.3 -lgcc
objs := head.o init.o serial.o main.o

000.bin: $(objs)
	arm-linux-ld  -Ttext 0x000000 -o timer_elf $^
	arm-linux-objcopy -O binary -S timer_elf $@
	arm-linux-objdump -D -m arm timer_elf > timer.dis
	
%.o:%.c
	arm-linux-gcc -nostdlib -Wall -O2 -c -o $@ $<

%.o:%.S
	arm-linux-gcc -nostdlib -Wall -O2 -c -o $@ $<

clean:
	rm -f 000.bin timer_elf timer.dis *.o		
	