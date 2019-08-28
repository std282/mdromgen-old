# Project name
LIBNAME := intmgr

###############################################################################
# LET GNU MAKE HANDLE THE REST                                                #
###############################################################################

# Utilities
CC := m68k-linux-gnu-gcc-8
AR := m68k-linux-gnu-ar

# Compiler parameters
COMPILER_PARAMS := -c 
COMPILER_PARAMS += -std=c11 -Wall -Wextra 
COMPILER_PARAMS += -I../../inc 
COMPILER_PARAMS += -m68000
COMPILER_PARAMS += -nostdlib
COMPILER_PARAMS += -ffreestanding

ifeq ($(OPTIMIZE), 0)
COMPILER_PARAMS += -O0
else
COMPILER_PARAMS += -O3
COMPILER_PARAMS += -fipa-pta
COMPILER_PARAMS += -free
COMPILER_PARAMS += -fira-region=all
COMPILER_PARAMS += -ftree-loop-distribution
COMPILER_PARAMS += -fsplit-loops

ifeq ($(ENABLE_LTO), 0) 
# do nothing
else
COMPILER_PARAMS += -flto
endif # ENABLE_LTO

endif # OPTIMIZE

COMPILER_PARAMS += -fno-tree-loop-distribute-patterns

COMPILER_PARAMS += -fshort-enums
COMPILER_PARAMS += -fwrapv
COMPILER_PARAMS += -freg-struct-return
COMPILER_PARAMS += -fcall-used-%d0
COMPILER_PARAMS += -fcall-used-%d1
COMPILER_PARAMS += -fcall-used-%a0
COMPILER_PARAMS += -fcall-used-%a1
COMPILER_PARAMS += -fcall-saved-%d7
COMPILER_PARAMS += -fcall-saved-%a5

# Archiver parameters
ARCHIVER_PARAMS := rcs

# Files to work with
SRC := $(wildcard src/*.c)
OBJ := $(patsubst %.c,%.o,$(SRC))

OUT := ../lib$(LIBNAME).a

# Finally, targets
.PHONY: all clean

all: $(OUT)

lib%.a: $(OBJ)
	$(AR) $(ARCHIVER_PARAMS) $@ $^

%.o: %.c
	$(CC) $(COMPILER_PARAMS) $< -o $@

clean:
	rm $(OUT)

