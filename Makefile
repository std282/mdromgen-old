# Project name
PROJ := ProjectName

# Set this to 1, if you want to get listings
MAKE_LST := 0

# Set this to 1, if you want to enable optimization
OPTIMIZE := 1

# Set this to 1, if you want to enable link-time optimization
ENABLE_LTO := 0

# Output file dependencies
DEPS := startup
DEPS += intmgr

###############################################################################
# LET GNU MAKE HANDLE THE REST                                                #
###############################################################################

export OPTIMIZE
export ENABLE_LTO

# Utilities
MK := make
CC := m68k-linux-gnu-gcc-8
LD := m68k-linux-gnu-gcc-8
DU := m68k-linux-gnu-objcopy
AR := m68k-linux-gnu-ar
RP := util/romfix-run
DA := m68k-linux-gnu-objdump

LNK_SCRIPT = link.ld

ROM_INFO_SRC = rominfo/rominfo.c
ROM_INFO_OBJ = rominfo/rominfo.o

# Compiler parameters
COMPILER_PARAMS := -c
COMPILER_PARAMS += -std=c11 -Wall -Wextra
COMPILER_PARAMS += -Iinc
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
endif

COMPILER_PARAMS += -fno-tree-loop-distribute-patterns

ifeq ($(ENABLE_LTO), 0)
# do nothing
else
COMPILER_PARAMS += -flto
endif

COMPILER_PARAMS += -fshort-enums
COMPILER_PARAMS += -fwrapv
COMPILER_PARAMS += -freg-struct-return
COMPILER_PARAMS += -fcall-used-%d0
COMPILER_PARAMS += -fcall-used-%d1
COMPILER_PARAMS += -fcall-used-%a0
COMPILER_PARAMS += -fcall-used-%a1
COMPILER_PARAMS += -fcall-saved-%d7
COMPILER_PARAMS += -fcall-saved-%a5

# Linker parameters
LINKER_PARAMS := -T $(LNK_SCRIPT)
LINKER_PARAMS += -Wl,--build-id=none
LINKER_PARAMS += -Llib
LINKER_PARAMS += -static
LINKER_PARAMS += -nostdlib
LINKER_PARAMS += -m68000

LINKER_LIBRARIES := $(addprefix -l,$(DEPS)) -lgcc

LIBS := $(addprefix lib/lib,$(DEPS))
LIBS := $(addsuffix .a,$(LIBS))

ifeq ($(ENABLE_LTO), 0)
# do nothing
else
LINKER_PARAMS += -flto
LINKER_PARAMS += -fuse-linker-plugin
endif

# Dumper parameters
DUMPER_PARAMS := -O binary

# Archiver parameters
ARCHIVER_PARAMS := rcs

# Files to work with
SRC := $(wildcard src/*.c)
OBJ := $(patsubst %.c,%.o,$(SRC))

OUT := $(PROJ).bin

ifeq ($(MAKE_LST), 0)
# do nothing
else
OUT += $(PROJ).lst
endif

# Finally, targets
.PHONY: all clean
.PRECIOUS: $(RP) $(LIBS)

all: $(OUT)

%.bin: %.elf $(RP)
	$(DU) $(DUMPER_PARAMS) $< $@
	$(RP) $@

$(ROM_INFO_OBJ): $(ROM_INFO_SRC)
	$(CC) -c $< -o $@

%.lst: %.elf
	$(DA) --disassemble $< > $@

%.elf: $(OBJ) $(ROM_INFO_OBJ) $(LIBS)
	$(LD) $(LINKER_PARAMS) $^ -o $@ $(LINKER_LIBRARIES)

%.o: %.c
	$(CC) $(COMPILER_PARAMS) $< -o $@

lib/lib%.a: lib/%/
	$(MK) -C $<

$(RP):
	$(MK) -C util/romfix

clean:
	rm $(OUT)

cleanprecious:
	rm $(LIBS) $(RP)
