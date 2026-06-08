all:
	gcc -o programTrab src/*.c -Iheaders -lm

run:
	./programTrab

clean:
	rm -f programTrab
