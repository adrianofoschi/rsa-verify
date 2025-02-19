
CFLAGS = -Wall

OBJS = main.o rsa.o sha256.o

verify: ${OBJS}
	$(CC) -o verify ${OBJS}

clean:
	rm -f ${OBJS}
