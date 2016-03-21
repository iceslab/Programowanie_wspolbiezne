CC=clang
EXEC_1=pierwsze
EXEC_2=licz

SOURCES_1=pierwsze.c
SOURCES_2=licz.c

BIN=bin

CFLAGS=-g
all: $(EXEC_1) $(EXEC_2)
$(EXEC_1): $(SOURCES_1)
	$(CC) -o $(BIN)/$(EXEC_1) $(CFLAGS) $(SOURCES_1)
$(EXEC_2): $(SOURCES_2)
	$(CC) -o $(BIN)/$(EXEC_2) $(CFLAGS) $(SOURCES_2)
clean:
	rm -rf *.o $(BIN)/*
