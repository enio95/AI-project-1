CC=gcc
CFLAGS=-I. -Wall
DEPS = errorMessage.h point.h read.h

ODIR=bin

_OBJ = converter.o errorMessage.o point.o read.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS) 

converter: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm $(ODIR)/*.o
