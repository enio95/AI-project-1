CC=gcc
CFLAGS=-I. -Wall
DEPS = integerLinkedList.h extraFunctions.h state.h errorMessage.h point.h read.h

ODIR=./bin

_OBJ = integerLinkedList.o extraFunctions.o state.o errorMessage.o point.o read.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS) 

all: localSearch iterativeLocalSearch

iterativeLocalSearch: $(ODIR)/iterativeLocalSearch.o $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

localSearch: $(ODIR)/localSearch.o $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm $(ODIR)/*.o
