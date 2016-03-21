CC=clang
SOURCES1=pierwszy.c wspolny.c
SOURCES2=drugi.c wspolny.c
SOURCES3=test.c
SOURCES4=fork1.c
CFLAGS=-g
ARCHIV=pierwszy.c drugi.c wspolny.c wspolny.h
all: pierwszy drugi test fork
pierwszy: $(SOURCES1)
	$(CC) -o /bin/pierwszy $(CFLAGS) $(SOURCES1)
drugi: $(SOURCES2)
	$(CC) -o bin/drugi $(CFLAGS) $(SOURCES2)
test: $(SOURCES3)
	$(CC) -o bin/test $(CFLAGS) $(SOURCES3)
fork: $(SOURCES4)
	$(CC) -o bin/fork $(CFLAGS) $(SOURCES4)
clean:
	rm -rf *.o bin/* prace.tar
