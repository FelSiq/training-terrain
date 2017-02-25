CFLAGS = -Xlint
CC = javac
RN = java
EXT = class

all: complex linkedlist commandTree manager
complex:
	$(CC) complex.java $(CFLAGS)
linkedlist:
	$(CC) clList.java $(CFLAGS)
commandTree:
	$(CC) commandTree.java $(CFLAGS)
manager:
	$(CC) complexManager.java $(CFLAGS)
run:
	$(RN) complexManager
clean:
	rm *.$(EXT)