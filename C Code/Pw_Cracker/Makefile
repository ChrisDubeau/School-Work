###########################3
#Name: Christopher Dubeau
#Student #: 1793075
#username: Dubeauc3
##############################

CC = gcc
CFLAGS = -g -Wall -ansi -lpthread -DMEMWATCH -DMW_STDIO -D_XOPEN_SOURCE

build: pw_crack

pw_crack:	pw_crack.c memwatch.o bcrypt/bcrypt.a pw_crack.h
	$(CC) $(CFLAGS) pw_crack.c -o pw_crack memwatch.o bcrypt/bcrypt.a pw_crack.h

memwatch.o: memwatch.c memwatch.h
	$(CC) $(CFLAGS) -c memwatch.c memwatch.h
	
clean:
	rm *.o *.h.gch *.log pw_crack