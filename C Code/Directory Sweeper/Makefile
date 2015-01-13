###########################3
#Name: Christopher Dubeau
#Student #: 1793075
#username: Dubeauc3
##############################

CC = gcc
CFLAGS = -g -Wall -ansi -DMEMWATCH -DMW_STDIO
build: dirsweeper

dirsweeper:	dirsweepermain.o dirsweepersupport.o memwatch.o
	$(CC) $(CFLAGS) -o dirsweeper memwatch.o dirsweepermain.o dirsweepersupport.o
	
dirsweepermain.o: dirsweepermain.c memwatch.h
	$(CC) $(CFLAGS) -c dirsweepermain.c memwatch.h
	
dirsweepersupport.o: dirsweepersupport.c memwatch.h
	$(CC) $(CFLAGS) -c dirsweepersupport.c memwatch.h
	
memwatch.o: memwatch.c memwatch.h
	$(CC) $(CFLAGS) -c memwatch.c memwatch.h
	
clean:
	rm *.o *.h.gch *.log dirsweeper