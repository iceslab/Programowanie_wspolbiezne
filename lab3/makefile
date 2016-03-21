CC=clang
EXEC_1=fork
EXEC_2=execl
EXEC_3=sub_exec
EXEC_4=system

EXEC_5=pierwsze
EXEC_6=licz

SOURCES_1=fork.c
SOURCES_2=execl.c
SOURCES_3=sub_exec.c
SOURCES_4=system.c

SOURCES_5=pierwsze.c
SOURCES_6=licz.c

CFLAGS=-g
all: $(EXEC_1) $(EXEC_2) $(EXEC_3) $(EXEC_4) $(EXEC_5) $(EXEC_6)
$(EXEC_1): $(SOURCES_1)
	$(CC) -o $(EXEC_1) $(CFLAGS) $(SOURCES_1)
$(EXEC_2): $(SOURCES_2)
	$(CC) -o $(EXEC_2) $(CFLAGS) $(SOURCES_2)
$(EXEC_3): $(SOURCES_3)
	$(CC) -o $(EXEC_3) $(CFLAGS) $(SOURCES_3)
$(EXEC_4): $(SOURCES_4)
	$(CC) -o $(EXEC_4) $(CFLAGS) $(SOURCES_4)
$(EXEC_5): $(SOURCES_5)
	$(CC) -o $(EXEC_5) $(CFLAGS) $(SOURCES_5)
$(EXEC_6): $(SOURCES_6)
	$(CC) -o $(EXEC_6) $(CFLAGS) $(SOURCES_6)
clean:
	rm -rf *.o $(EXEC_1) $(EXEC_2) $(EXEC_3) $(EXEC_4) $(EXEC_5) $(EXEC_6)
