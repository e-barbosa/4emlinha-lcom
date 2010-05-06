all: main.exe

main.exe: main.o funcs.o ints.o video-graphics.o
	gcc main.o funcs.o ints.o video-graphics.o -o main.exe	
	
main.o: main.c
	gcc -Wall -c main.c -o main.o
	
funcs.o: funcs.c funcs.h
	gcc -Wall -c funcs.c -o funcs.o
	
ints.o: ints.c ints.h
	gcc -Wall -c ints.c -o ints.o
	
video-graphics.o: video-graphics.c video-graphics.h
	gcc -Wall -c video-graphics.c -o video-graphics.o

clean:
	rm *.o *.exe