all: main
	mkdir -p build/bin
	mkdir -p build/lib
	mkdir -p build/objects
	mv *.o build/objects
	mv *.a build/lib
	mv main build/bin

main: main.o libmyls.a
	gcc main.o -o main -lmyls -L.

main.o: src/bin/main.c
	gcc src/bin/main.c -c -I include

libmyls.a: src/lib.c
	gcc src/lib.c -c -I include
	ar rs libmyls.a lib.o

libmyls.so: [src/lib.c][0]
	gcc -c -fpic src/lib.c
	gcc -shared -o libmyls.so lib.o
	mv *.so build/lib
	
clean:
	rm -rf build


[0]: http://crasseux.com/books/ctutorial/Building-a-library.html#Building%20a%20library
