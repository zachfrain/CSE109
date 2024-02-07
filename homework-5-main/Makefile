test: test.o libhashset.a
	g++ test.o -o tester -lhashset -llinkedlist -L. -Llib
	mkdir -p build/bin/release
	mkdir -p build/lib/release
	mkdir -p build/objects
	mv *.o build/objects
	mv *.a build/lib/release
	mv tester build/bin/release/test

test.o: test/test.cpp
	g++ test/test.cpp -c -I include -I lib

static: src/lib.cpp
	mkdir -p build/bin/release
	mkdir -p build/lib/release
	mkdir -p build/lib/debug
	mkdir -p build/objects
	g++ src/lib.cpp -c -I lib -I include
	ar rs liblinkedlist.a lib.o
	mv *.a build/lib/release
	mv *.o build/objects

shared: src/lib.cpp
	g++ src/lib.cpp -c -I lib -I include
	gcc -shared -o liblinkedlist.so lib.o
	mv *.so build/lib/release
	mv *.o build/objects

debug: src/lib.cpp
	g++ src/lib.cpp -c -g -I lib -I include
	gcc -shared -g -o liblinkedlist.so lib.o
	mv *.so build/lib/debug
	mv *.o build/objects

clean:
	rm -rf build
