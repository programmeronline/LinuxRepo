all : server client1 client2 client3 add sub mul
client1: client1.o
	gcc -o client1 client1.o
client2: client2.o
	gcc -o client2 client2.o
client3: client3.o
	gcc -o client3 client3.o
server: server.o readcommand.o notifyclient.o
	gcc -o server server.o readcommand.o notifyclient.o
add: add.o
	gcc -o add add.o
sub: sub.o
	gcc -o sub sub.o
mul: mul.o
	gcc -o mul mul.o
loop: loop.o
	gcc -o loop loop.o

server.o: server.c headers.h declarations.h
	gcc -c server.c
client1.o: client1.c headers.h declarations.h
	gcc -c client1.c
client2.o: client2.c headers.h declarations.h
	gcc -c client2.c
client3.o: client2.c headers.h declarations.h
	gcc -c client3.c
add.o: add.c headers.h declarations.h
	gcc -c add.c
sub.o: sub.c headers.h declarations.h
	gcc -c sub.c
mul.o: mul.c headers.h declarations.h
	gcc -c mul.c
loop.o: loop.c headers.h
	gcc -c loop.c
readcommand.o: readcommand.c declarations.h headers.h
	gcc -c readcommand.c
notifyclient.o: notifyclient.c declarations.h headers.h
	gcc -c notifyclient.c
clean:
	rm *.o
