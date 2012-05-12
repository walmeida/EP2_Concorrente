IDIR = ./include
ODIR = obj
BDIR = bin

CC = gcc
CFLAGS = -ansi -Wall -I$(IDIR) -g
LIBS = -lpthread

EXE = caminhosminimos

_DEPS = graph.h queue.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o queue.o graph.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BDIR)/$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BDIR)/$(EXE) *~ core $(INCDIR)/*~ 