CC = gcc
CFLAGS = -Wall -Wextra -O2 -pthread
BINDIR = bin

CONCURRENCY_SRC = $(wildcard concurrency/*.c)
IPC_SRC = $(wildcard ipc-networking/*.c)

CONCURRENCY_BINS = $(patsubst concurrency/%.c,$(BINDIR)/%,$(CONCURRENCY_SRC))
IPC_BINS = $(patsubst ipc-networking/%.c,$(BINDIR)/%,$(IPC_SRC))

.PHONY: all clean

all: $(BINDIR) $(CONCURRENCY_BINS) $(IPC_BINS)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/%: concurrency/%.c
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR)/%: ipc-networking/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BINDIR) output.txt
