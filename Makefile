IDIR=include
BOOST="D:/Program Files/boost_1_75_0/boost_1_75_0"
CC=g++
CFLAGS=-I$(IDIR) -I$(BOOST) -MMD -std=c++17 -g -lstdc++fs

_DEPS= src/Chapters/Chapters.h \
    src/Generic/BookChapter.h \
    src/Generic/Widget.h \
	src/TourOfCpp/Matrix.h \
	src/TourOfCpp/MyVector.h \
	src/TourOfCpp/SimpleCollection.h \
	src/TourOfCpp/TourOfCpp.h

_OBJ = obj/main.o obj/BookChapter.o obj/Widget.o \
       obj/C1_DeducingTypes.o obj/C2_Auto.o  obj/C3_ModernCpp.o obj/Matrix.o \
	   obj/TourOfCpp.o

OBJ = $(patsubst %,$(ODIR)%,$(_OBJ))

EffectiveModernCpp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

obj/main.o: src/main.cpp $(_DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

GEN_DIR := src/Generic $(_DEPS)
$(ODIR)/%.o: $(GEN_DIR)/%.cpp
   $(CC) $(CFLAGS) -c -o $@ $<

CHAPTER_DIR := src/Chapters $(_DEPS)
$(ODIR)/%.o: $(CHAPTER_DIR)/%.cpp
   $(CC) $(CFLAGS) -c -o $@ $<

TOUR_DIR := src/TourOfCpp $(_DEPS)
$(ODIR)/%.o: $(TOUR_DIR)/%.cpp
   $(CC) $(CFLAGS) -c -o $@ $<

-include $(OBJ_FILES:.o=.d)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o