CC=g++
IDIR=include
ODIR=obj
SDIR=src
TARGET=run
CPPFLAGS=-O3 -std=c++14 -I$(IDIR) -pthread

_OBJ=main.o Manager.o 
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

_DEPS=Manager.h StampedSnap.h WFSnapshot.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

all: $(TARGET)

$(TARGET): $(OBJ) $(DEPS)
	$(CC) -o $@ $^ $(CPPFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(TARGET) *~
