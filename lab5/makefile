CC=clang
EXEC_4=pierwsze
EXEC_7=pierwsze_named
EXEC_8=licz
EXEC_9=pierwsze_balanced
EXEC_10=licz_balanced

SOURCES_4=pierwsze.c primes_utils.c

SOURCES_7=pierwsze_named.c primes_utils.c
SOURCES_8=licz.c primes_utils.c

SOURCES_9=pierwsze_balanced.c primes_utils.c
SOURCES_10=licz_balanced.c primes_utils.c

BIN=bin

CFLAGS=-g -lm

all: $(EXEC_4) $(EXEC_7) $(EXEC_8) $(EXEC_9) $(EXEC_10)
$(EXEC_4): $(SOURCES_4)
	$(CC) -o $(BIN)/$(EXEC_4) $(CFLAGS) $(SOURCES_4)
$(EXEC_7): $(SOURCES_7)
	$(CC) -o $(BIN)/$(EXEC_7) $(CFLAGS) $(SOURCES_7)
$(EXEC_8): $(SOURCES_8)
	$(CC) -o $(BIN)/$(EXEC_8) $(CFLAGS) $(SOURCES_8)
$(EXEC_9): $(SOURCES_9)
	$(CC) -o $(BIN)/$(EXEC_9) $(CFLAGS) $(SOURCES_9)
$(EXEC_10): $(SOURCES_10)
	$(CC) -o $(BIN)/$(EXEC_10) $(CFLAGS) $(SOURCES_10)
clean:
	rm -rf *.o $(BIN)/*
