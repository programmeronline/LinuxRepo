all: server client1
client1: client1.o
	gcc -o client1 client.c
server: server.o
	gcc -o server server.o -lpthread
server.o: server.c declarations.h
	gcc -c server.c
client1.o: client.c declarations.h
	gcc -c client.c
clean:
	rm *.o
