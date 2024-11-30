# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Target executable
TARGET = build/program

# Source files
SRCS = main.c utils.c

# Object files (derived from SRCS)
OBJS = $(SRCS:%.c=build/%.o)

# Default target
all: build_dir $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Rule to create object files
build/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
build_dir:
	mkdir -p build

# Clean up build files
clean:
	rm -rf build
