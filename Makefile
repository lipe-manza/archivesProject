all:
	gcc -o programTrab src/main.c src/core/*.c src/sql/*.c src/btree/*.c -Iinclude -lm

run:
	./programTrab

test: all
	./test.fish

clean:
	rm -f programTrab *.bin *.got

ZIP_NAME = programa.zip

zip: clean
	zip -r $(ZIP_NAME)  include/ src/ Makefile
