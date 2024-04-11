# Makefile for compiling proj_prototype.c

# Compiler command
CC=gcc

# Compiler flags
CFLAGS=-Wall -Wextra -std=c99

# Target executable
TARGET=proj_prototype

# Source file
SRCS=proj_prototype.c

# Object files
OBJS=$(SRCS:.c=.o)

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET) $(OBJS)

