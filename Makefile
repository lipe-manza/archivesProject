all:
	gcc -o programTrab src/main.c src/core/*.c src/sql/*.c src/btree/*.c -Iinclude -lm

debug:
	gcc -g -o programTrab src/main.c src/core/*.c src/sql/*.c src/btree/*.c -Iinclude -lm

run:
	./programTrab
