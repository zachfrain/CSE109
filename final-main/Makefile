client: libpack109.a client.o
	g++ build/objects/release/client.o -o client -lpack109 -Lbuild/lib/release -std=c++11
	g++ build/objects/release/server.o -o server -lpack109 -Lbuild/lib/release -std=c++11
	mkdir -p build/bin/release
	mv client build/bin/release/client
	mv server build/bin/release/server
	

libpack109.a:
	g++ src/lib.cpp -c -Iinclude -std=c++11
	ar rs libpack109.a lib.o 
	mkdir -p build/lib/release
	mkdir -p build/objects/release
	mv *.o build/objects/release
	mv libpack109.a build/lib/release

client.o:
	g++ test/client.cpp -c -lpack109 -Lbuild/lib/release -Iinclude -std=c++11
	g++ test/server.cpp -c -lpack109 -Lbuild/lib/release -Iinclude -std=c++11
	mkdir -p build/objects/release
	mv *.o build/objects/release


clean:
	rm -f *.a
	rm -f *.o
	rm -rf build