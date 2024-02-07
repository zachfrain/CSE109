all: client server
	mkdir -p build/bin/release
	mv $^ build/bin/release

client:
	gcc src/bin/client.c -o client

server:
	gcc src/bin/server.c -o server

clean:
	rm -rf build