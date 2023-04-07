# Parameters
CC = gcc
CFLAGS := -g -Wall -std=c99 -lm

EXECUTABLE := Mathis
EXTENSION := 

INCLUDEDIR := src
OBJDIR := obj
SRCDIR := src
BINDIR := bin


# Do not touch below this line
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# SRC_FILES := $(shell find $(SRCDIR) -name '*.c')
SRC_FILES := $(call rwildcard,.,*.c)

HEADER_FILES := $(shell find $(INCLUDEDIR) -name '*.h')

OBJ_FILES := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o, $(SRC_FILES))

EXE_FILE := $(BINDIR)/$(EXECUTABLE)

.PHONY: all
all: $(EXE_FILE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(EXE_FILE) $(OBJ_FILES)
$(EXE_FILE): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(CFLAGS) -o $@

.PHONY: clean
clean:
	-rm -r ./$(OBJDIR)/*.o
	-rm -r ./$(EXE_FILE)$(EXTENSION)

.PHONY: run
run: $(EXE_FILE)
	@./$(EXE_FILE)$(EXTENSION)
