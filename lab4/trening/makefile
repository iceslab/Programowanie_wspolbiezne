CC=clang
EXEC_1=pierwsze
EXEC_2=licz
EXEC_3=copy
EXEC_4=fcopy
EXEC_5=fstat
EXEC_6=dir

SOURCES_1=pierwsze.c
SOURCES_2=licz.c
SOURCES_3=copy.c
SOURCES_4=fcopy.c
SOURCES_5=fstat.c fstat_utils.c
SOURCES_6=dir.c fstat_utils.c

BIN=bin

CFLAGS=-g
all: $(EXEC_1) $(EXEC_2) $(EXEC_3) $(EXEC_4) $(EXEC_5) $(EXEC_6)
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
clean:
	rm -rf *.o $(BIN)/*
