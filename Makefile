SOURCES := $(wildcard sources/*.c)

all:
	gcc -o bridges -pthread $(SOURCES) -I headers

install: all
	cp bridges /usr/bin
	
uninstall:
	rm /usr/bin/bridges

clean:
	rm bridges