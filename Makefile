IDIR=include
CC=g++
CFLAGS=-I$(IDIR)

_DEPS= src/Chapters/Chapters.h \
    src/Generic/BookChapter.h \
    src/Generic/Widget.h

_OBJ = obj/main.o obj/BookChapter.o obj/Widget.o \
       obj/C1_DeducingTypes.o

DEPS = $(patsubst %,$(IDIR)%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)%,$(_OBJ))

EffectiveModernCpp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

obj/main.o: src/main.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/BookChapter.o: src/Generic/BookChapter.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/Widget.o: src/Generic/Widget.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/C1_DeducingTypes.o: src/Chapters/C1_DeducingTypes.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o