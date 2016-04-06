IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=.
LDIR =../lib

_DEPS = header.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = boardsize.o clear.o count.o countlib.o gennew.o main.o play.o showboard.o finalscore.o undo.o fixedhandicap.o checkboard.o ko.o placefreehandicap.o read.o setfreehandicap.o minimax.o valid.o isterminal.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ipgo.002.058: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f ipgo.002.058 $(ODIR)/*.o *~ core $(INCDIR)/*~ 
