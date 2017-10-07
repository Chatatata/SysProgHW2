IDIR = ./include
CC = gcc
CFLAGS = -I$(IDIR) -Wall -g -std=c11 

ODIR = obj
LDIR = ./lib

LIBS = -lm

SRCDIR = ./src

_DEPS = kill_child_on_exit.h test_helpers.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = kill_child_on_exit.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kill_child_on_exit_unit_tests: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

