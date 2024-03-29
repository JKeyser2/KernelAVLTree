CC=gcc
CFLAGS=-Wall -Wextra
EXEC=test_file_one


all: $(EXEC)


$(EXEC): test_file_one.c
	$(CC) $(CFLAGS) test_file_one.c -o $(EXEC)


Clean:
	rm -f $(EXEC)
