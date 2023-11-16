6# Makefile for tic-tac-dolan

# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Libraries to include
LIBS = -lncurses

# Name of the output executable
TARGET = tic-tac-dolan

# Source files
SRCS = tic-tac-dolan.c

# Object files (automatically generated from source files)
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Clean target for removing compiled files
clean:
	rm -f $(TARGET) $(OBJS)

# Suffix rule for .c to .o
.c.o:
	$(CC) $(CFLAGS) -c $<

# Specify dependencies (optional, useful if your project grows)
# For example:
# tic-tac-dolan.o: tic-tac-dolan.c
