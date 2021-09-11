IDIR=include
ODIR=obj
BOOST="D:/Program Files/boost_1_75_0/boost_1_75_0"
CC=g++
CFLAGS= -std=c++17 -g -lstdc++fs
DEPFLAGS = -MMD

TARGET = EffectiveModernCpp

SRCDIRS = $(sort $(dir $(wildcard src/*/))) src
INCLUDES = -I$(IDIR) -I$(BOOST)

VPATH = $(SRCDIRS)
SRC = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp))
SRC_F = $(notdir $(SRC))
OBJ = $(addprefix $(ODIR)/, $(SRC_F:%.cpp=%.o))
DEP = $(OBJ:%.o=%.d)

.PHONY: all clean 

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Include dependencies
-include $(DEP)

$(ODIR)/%.o: %.cpp
	$(CC) -c $(INCLUDES) -o $@ $< $(CFLAGS) $(DEPFLAGS)

REMOVE_FILES := $(wildcard $(ODIR)/*.o) $(wildcard $(ODIR)/*.d)
clean:
	rm -f $(REMOVE_FILES)