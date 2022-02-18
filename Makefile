IDIR=include
ODIR=obj
CC=g++
CFLAGS= -std=c++17 -g -lstdc++fs
DEPFLAGS = -MMD

TARGET = EffectiveModernCpp

SRCDIRS = $(sort $(dir $(wildcard src/*/))) src
INCLUDES = -I$(IDIR)

VPATH = $(SRCDIRS)
SRC = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp))
SRC_F = $(notdir $(SRC))
OBJ = $(addprefix $(ODIR)/, $(SRC_F:%.cpp=%.o))
DEP = $(OBJ:%.o=%.d)

.PHONY: all clean 

all: EffectiveModernCpp

EffectiveModernCpp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Include dependencies
-include $(DEP)

$(ODIR)/%.o: %.cpp | $(ODIR)
	$(CC) -c $(INCLUDES) -o $@ $< $(CFLAGS) $(DEPFLAGS)

$(ODIR):
	mkdir -p $@

.PHONY: clean all

REMOVE_FILES := $(wildcard $(ODIR)/*.o) $(wildcard $(ODIR)/*.d)
clean:
	rm -f $(REMOVE_FILES)