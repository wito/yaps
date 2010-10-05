CC=gcc
CFLAGS=-Wall -I/usr/include/libxml2 -Iinc -D DEBUG -std=c99
LFLAGS=-lm

TDIR=
TODIR=
ODIR=obj

_TEST = 
TEST = $(patsubst %,$(TODIR)/%.test,$(_TEST))

_OBJ = yaps.o vector.o particle.o world.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

yaps: $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o yaps
