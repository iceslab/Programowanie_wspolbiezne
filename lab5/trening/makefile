CC=clang
EXEC_1=simple
EXEC_2=simple_modify
EXEC_3=popen
EXEC_4=pierwsze
EXEC_5=fifo_save
EXEC_6=fifo_read
EXEC_7=pierwsze_named
EXEC_8=licz
EXEC_9=pierwsze_balanced
EXEC_10=licz_balanced

SOURCES_1=simple.c
SOURCES_2=simple_modify.c
SOURCES_3=popen.c
SOURCES_4=pierwsze.c primes_utils.c

SOURCES_5=fifo_save.c
SOURCES_6=fifo_read.c

SOURCES_7=pierwsze_named.c primes_utils.c
SOURCES_8=licz.c primes_utils.c

SOURCES_9=pierwsze_balanced.c primes_utils.c
SOURCES_10=licz_balanced.c primes_utils.c

BIN=bin

CFLAGS=-g

all: $(EXEC_1) $(EXEC_2) $(EXEC_3) $(EXEC_4) $(EXEC_5) $(EXEC_6) $(EXEC_7) $(EXEC_8) $(EXEC_9) $(EXEC_10)
$(EXEC_1): $(SOURCES_1)
	$(CC) -o $(BIN)/$(EXEC_1) $(CFLAGS) $(SOURCES_1)
$(EXEC_2): $(SOURCES_2)
	$(CC) -o $(BIN)/$(EXEC_2) $(CFLAGS) $(SOURCES_2)
$(EXEC_3): $(SOURCES_3)
	$(CC) -o $(BIN)/$(EXEC_3) $(CFLAGS) $(SOURCES_3)
$(EXEC_4): $(SOURCES_4)
	$(CC) -o $(BIN)/$(EXEC_4) $(CFLAGS) $(SOURCES_4)
$(EXEC_5): $(SOURCES_5)
	$(CC) -o $(BIN)/$(EXEC_5) $(CFLAGS) $(SOURCES_5)
$(EXEC_6): $(SOURCES_6)
	$(CC) -o $(BIN)/$(EXEC_6) $(CFLAGS) $(SOURCES_6)
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
