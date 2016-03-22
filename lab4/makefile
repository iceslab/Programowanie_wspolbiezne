CC=clang
EXEC_1=pierwsze
EXEC_2=licz
EXEC_3=copy
EXEC_4=fstat

SOURCES_1=pierwsze.c primes_utils.c
SOURCES_2=licz.c primes_utils.c
SOURCES_3=copy.c
SOURCES_4=fstat.c fstat_utils.c

BIN=bin

CFLAGS=-g
all:  $(EXEC_3) $(EXEC_4) $(EXEC_1) $(EXEC_2)
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
