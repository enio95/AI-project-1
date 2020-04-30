CC=gcc
CFLAGS=-I. -Wall
DEPS = heap.h stateArray.h extraFunctions.h integerLinkedList.h stateLinkedList.h state.h errorMessage.h point.h read.h

ODIR=bin

_OBJ = heap.o stateArray.o extraFunctions.o integerLinkedList.o stateLinkedList.o state.o errorMessage.o point.o read.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS) 

all: dfs iterativeDfs branchAndBound aStar bfs

dfs: $(ODIR)/dfs.o $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

iterativeDfs: $(ODIR)/iterativeDfs.o $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

branchAndBound: $(ODIR)/branchAndBound.o $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

aStar: $(ODIR)/aStar.o $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

bfs: $(ODIR)/bfs.o $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm $(ODIR)/*.o
