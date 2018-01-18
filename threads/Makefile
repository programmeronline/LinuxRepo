all: ser_th client1 loop
ser_th: ser_th.o add.o
	gcc -o ser_th ser_th.o -lpthread add.o
client1: client1.o
	gcc -o client1 client1.o
loop: loop.o
	gcc -o loop loop.o

ser_th.o: ser_th.c declarations.h add.h
	gcc -c ser_th.c
client1.o: client1.c declarations.h
	gcc -c client1.c
add.o: add.c declarations.h add.h
	gcc -c add.c
loop.o: loop.c
	gcc -c loop.c
clean:
	rm *.o
