IDIR=include
ODIR=obj/
BOOST="D:/Program Files/boost_1_75_0"
CC=g++
CFLAGS=-I$(IDIR) -I$(BOOST) -std=c++17 -g -lstdc++fs

_DEPS= src/Chapters/Chapters.h \
    src/Generic/BookChapter.h \
    src/Generic/Widget.h \
	src/TourOfCpp/Matrix.h \
	src/TourOfCpp/MyVector.h \
	src/TourOfCpp/SimpleCollection.h \
	src/TourOfCpp/TourOfCpp.h

DEPS = $(patsubst %,$(IDIR)%,$(_DEPS))

_CHAPTERS = $(wildcard src/Chapters/*.cpp)
CHAPTERS = $(patsubst src/Chapters/%.cpp, %.o, $(_CHAPTERS))

_OBJ = main.o BookChapter.o Widget.o \
       $(CHAPTERS) Matrix.o \
	   TourOfCpp.o
	   
OBJ = $(patsubst %,$(ODIR)%,$(_OBJ))

EffectiveModernCpp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

obj/main.o: src/main.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/BookChapter.o: src/Generic/BookChapter.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/Widget.o: src/Generic/Widget.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/Matrix.o: src/TourOfCpp/Matrix.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/TourOfCpp.o: src/TourOfCpp/TourOfCpp.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/%.o: src/Chapters/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

OBJECT_FILES := $(wildcard $(ODIR)*.o)
clean:
	rm -f $(OBJECT_FILES)