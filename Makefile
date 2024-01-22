CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: geraos main executable

geraos:
	$(CC) $(CFLAGS) -c codigos/*.c

main:
	$(CC) $(CFLAGS) -o main *.o

executable:
	./main casos/01

clean:
	rm -rf *.o main *.txt