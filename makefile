all: main.exe	

main.exe: main.o liblcom.a
	gcc main.o -L. -llcom -o main.exe
	
main.o: main.c
	gcc -Wall -c main.c -o main.o
	
funcs.o: funcs.c funcs.h
	gcc -Wall -c funcs.c -o funcs.o
	
ints.o: ints.c ints.h
	gcc -Wall -c ints.c -o ints.o
	
video-graphics.o: video-graphics.c video-graphics.h
	gcc -Wall -c video-graphics.c -o video-graphics.o
	
sprite.o: sprite.c sprite.h
	gcc -Wall -c sprite.c -o sprite.o

kbd_isr.o: kbd_isr.asm
	nasm -o0 -t -f coff kbd_isr.asm -o kbd_isr.o
	
music.o: music.c music.h
	gcc -Wall -c music.c -o music.o
	
ints_asm.o: ints_asm.asm
	nasm -t -f coff ints_asm.asm -o ints_asm.o

interrup.o: interrup.asm
	nasm -t -f coff interrup.asm -o interrup.o
	
timer.o: timer.h timer.c
	gcc -Wall -c timer.c -o timer.o

kbc.o: kbc.h kbc.c
	gcc -Wall -c kbc.c -o kbc.o

queue.o: queue.h queue.c
	gcc -Wall -c queue.c -o queue.o
	
liblcom.a: main.o funcs.o ints.o video-graphics.o sprite.o kbd_isr.o music.o ints_asm.o interrup.o timer.o kbc.o queue.o
	ar -cr liblcom.a main.o funcs.o ints.o video-graphics.o sprite.o kbd_isr.o music.o ints_asm.o interrup.o timer.o kbc.o queue.o
	
clean:
	rm -rf *.o *.exe

rebuild: clean all