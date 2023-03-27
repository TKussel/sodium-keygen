CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -lsodium

SRCS = sodium-keygen.c
OBJS = $(SRCS:.c=.o)

EXECUTABLE = sodium-keygen

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(EXECUTABLE)

.PHONY: all clean
