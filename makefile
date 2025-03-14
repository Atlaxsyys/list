.PHONY: all build run

build:
	make -C list build
	
run:
	make -C list run

list.o:
	make -C list list.o

main.o:
	make -C list main.o

clean:
	make -C list clean