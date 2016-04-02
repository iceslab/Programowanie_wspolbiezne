CC=clang
EXEC_1=simple
EXEC_2=simple_modify
EXEC_3=popen

SOURCES_1=simple.c
SOURCES_2=simple_modify.c
SOURCES_3=popen.c

BIN=bin

CFLAGS=-g
all: $(EXEC_1) $(EXEC_2) $(EXEC_3)
$(EXEC_1): $(SOURCES_1)
	$(CC) -o $(BIN)/$(EXEC_1) $(CFLAGS) $(SOURCES_1)
$(EXEC_2): $(SOURCES_2)
	$(CC) -o $(BIN)/$(EXEC_2) $(CFLAGS) $(SOURCES_2)
$(EXEC_3): $(SOURCES_3)
	$(CC) -o $(BIN)/$(EXEC_3) $(CFLAGS) $(SOURCES_3)
clean:
	rm -rf *.o $(BIN)/*
