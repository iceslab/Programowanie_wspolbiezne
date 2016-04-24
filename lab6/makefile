CC=clang
EXEC_1=init
EXEC_2=producer
EXEC_3=consumer
EXEC_4=pierwsze_posix_balanced
EXEC_5=licz_posix_balanced

SOURCES_1=init.c
SOURCES_2=producer.c
SOURCES_3=consumer.c
SOURCES_4=pierwsze_posix_balanced.c primes_utils.c
SOURCES_5=licz_posix_balanced.c primes_utils.c

BIN=bin

CFLAGS=-g -lm -lrt

all: $(EXEC_1) $(EXEC_2) $(EXEC_3) $(EXEC_4) $(EXEC_5)
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
clean:
	rm -rf *.o $(BIN)/*
