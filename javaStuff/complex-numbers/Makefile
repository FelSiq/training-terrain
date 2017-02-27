CFLAGS = -Xlint
CC = javac
RN = java
EXT = class

all: complex commandTree manager
complex:
	$(CC) ./complex/complex.java $(CFLAGS)
commandTree:
	$(CC) ./complex/commandTree.java $(CFLAGS)
manager:
	$(CC) complexManager.java $(CFLAGS)
run:
	$(RN) complexManager
debug:
	$(RN) complexManager -DEBUG
clean:
	rm ./complex/*.$(EXT)
	rm ./*.$(EXT)