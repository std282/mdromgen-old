OUT := ../romfix-run

CC := gcc
COMPILER_PARAMS := -std=c11 -Os -Wall -Wextra

SRC := $(wildcard *.c)

# Targets
.PHONY: all

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(COMPILER_PARAMS) $^ -o $@
