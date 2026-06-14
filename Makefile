all:
	gcc -o programTrab src/main.c src/core/*.c src/sql/*.c -Iinclude -lm
	#gcc -o programTrab src/main.c src/core/*.c src/sql/*.c src/btree/*.c -Iinclude -lm

run:
	./programTrab

clean:
	rm -f programTrab

ZIP_NAME = programa.zip

zip: clean
	zip -r $(ZIP_NAME) data/ include/ src/ Makefile
