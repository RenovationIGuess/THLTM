CC = gcc
CFLAGS = -Wall
SRC_FILES = $(wildcard *.c)
EXE_FILES = $(patsubst %.c,%,$(SRC_FILES))

all: $(EXE_FILES)

%: %.c
	$(CC) $(CFLAGS) -o $@.exe $<

clean:
	rm -f $(EXE_FILES:%=%*.exe)

.PHONY: all clean
