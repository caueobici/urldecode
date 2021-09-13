
all: url

install: url
	cp ./url /bin/url

url: buildDir url.o main.o
	gcc -o url build/*

main.o: src/main.c src/url.h
	gcc -c src/main.c -o build/main.o
url.o: src/url.c src/url.h
	gcc -c src/url.c -o build/url.o

buildDir:
	mkdir -p build/

clean:
	rm -rf ./build/ ./url
