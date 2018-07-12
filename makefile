#Flags
CC = gcc
CFLAGS =
LIB = lib/

#rules
main: 
	$(CC) $(CFLAGS) -L$(LIB) Q1_Bruteforce.c -Iinclude -o q1b
	$(CC) $(CFLAGS) -L$(LIB) Q1_PreSort.c -Iinclude -o q1P
	$(CC) $(CFLAGS) -L$(LIB) Q2_Bruteforce.c -Iinclude -o q2b
	$(CC) $(CFLAGS) -L$(LIB) Q2_Horspool.c -Iinclude -o q2h
	$(CC) $(CFLAGS) -L$(LIB) Q2_Boyer_Moore.c -Iinclude -o q2bm

