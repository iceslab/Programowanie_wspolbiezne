CC=clang
EXEC_1=server_ftp
EXEC_2=client_ftp
EXEC_3=producer
EXEC_4=consumer

SOURCES_1=server_ftp.c
SOURCES_2=client_ftp.c
SOURCES_3=producer.c
SOURCES_4=consumer.c

BIN=bin

CFLAGS=-g -lm -lrt -pthread

all: $(EXEC_1) $(EXEC_2)
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
