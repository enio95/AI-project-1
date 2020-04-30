CC=gcc
CFLAGS=-I. -Wall
DEPS = errorMessage.h heap.h point.h read.h

ODIR=bin

_OBJ = greedy.o heap.o errorMessage.o point.o read.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS) 

greedy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm $(ODIR)/*.o
