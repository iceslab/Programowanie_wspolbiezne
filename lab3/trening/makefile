CC=clang
SOURCES_1=copy.c
SOURCES_2=pierwsze.c
SOURCES_3=licz.c
EXEC_1=copy
EXEC_2=pierwsze
EXEC_3=licz
BIN=bin
CFLAGS=-g
ARCHIV=SOURCES_1 SOURCES_2
all: $(EXEC_1) $(EXEC_2) $(EXEC_3)
$(EXEC_1): $(SOURCES_1)
	$(CC) -o $(BIN)/$(EXEC_1) $(CFLAGS) $(SOURCES_1)
$(EXEC_2): $(SOURCES_2)
	$(CC) -o $(BIN)/$(EXEC_2) $(CFLAGS) $(SOURCES_2)
$(EXEC_3): $(SOURCES_3)
	$(CC) -o $(BIN)/$(EXEC_3) $(CFLAGS) $(SOURCES_3)
clean:
	rm -rf *.o *.tar $(BIN)/*
