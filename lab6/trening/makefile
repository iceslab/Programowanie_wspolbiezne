CC=clang
EXEC_1=pierwsze_posix
EXEC_2=licz_posix
EXEC_3=pierwsze_posix_balanced
EXEC_4=licz_posix_balanced

SOURCES_1=pierwsze_posix.c primes_utils.c
SOURCES_2=licz_posix.c primes_utils.c
SOURCES_3=pierwsze_posix_balanced.c primes_utils.c
SOURCES_4=licz_posix_balanced.c primes_utils.c

BIN=bin

CFLAGS=-g -lm -lrt

all: $(EXEC_1) $(EXEC_2) $(EXEC_3) $(EXEC_4)
$(EXEC_1): $(SOURCES_1)
	$(CC) -o $(BIN)/$(EXEC_1) $(CFLAGS) $(SOURCES_1)
$(EXEC_2): $(SOURCES_2)
	$(CC) -o $(BIN)/$(EXEC_2) $(CFLAGS) $(SOURCES_2)
$(EXEC_3): $(SOURCES_3)
	$(CC) -o $(BIN)/$(EXEC_3) $(CFLAGS) $(SOURCES_3)
$(EXEC_4): $(SOURCES_4)
	$(CC) -o $(BIN)/$(EXEC_4) $(CFLAGS) $(SOURCES_4)
clean:
	rm -rf *.o $(BIN)/*
