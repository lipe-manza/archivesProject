# --- Compiler Settings ---
# CC specifies the compiler to be used. For C, we typically use gcc.
CC = gcc

# CFLAGS specifies the flags passed to the compiler.
# -Wall, -Wextra turn on most compilation warnings.
# -Iinclude tells the compiler to look for header files (.h) in the 'include' directory.
# -g adds debugging information.
CFLAGS = -Wall -Wextra -Iinclude -g

# --- Directories ---
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# --- Name of the final executable ---
# You can change "program" to "main" or any other name you want for your app.
TARGET = $(BIN_DIR)/program

# --- Files ---
# The wildcard function automatically finds all .c files in the src/ directory.
# When you create a new .c file in src/, it will be automatically picked up!
SRCS = $(wildcard $(SRC_DIR)/*.c)

# patsubst transforms the list of .c files into a list of .o files.
# e.g., src/main.c becomes obj/main.o
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# --- Rules ---

# The first rule is the default. It runs when you just type `make`.
all: $(TARGET)

# Rule to link the object files and create the final executable.
# $@ refers to the target ($(TARGET)) and $^ refers to all prerequisites ($(OBJS)).
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile a source file (.c) into an object file (.o).
# $< refers to the first prerequisite (the .c file).
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# The 'run' target lets you type `make run` to build and execute the program in one step.
run: all
	./$(TARGET)

# The 'debug' target lets you type `make debug` to run the program inside gdb.
debug: all
	gdb ./$(TARGET)

# The 'clean' target removes compiled files. Run it with `make clean`.
# .PHONY tells Make that these are commands, not actual files to be created.
.PHONY: all run debug clean

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
