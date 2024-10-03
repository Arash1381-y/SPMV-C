CC := gcc
Includes := -I./src/data-structures -I./src/utils -I./src/models
CFLAGS := -Wall -Wextra -Werror -g -std=c99 -pedantic $(Includes)
LIBS := -fopenmp -mavx512f

# Source files
SRC := $(wildcard src/data-structures/*.c) $(wildcard src/utils/*.c) $(wildcard src/models/**/*.c)


OBJ_DIR := obj
OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC)))


.PHONY: all clean benchmark

vpath %.c src/data-structures src/utils src/models/baseline src/models/sparse-singlethread src/models/sparse-multithread src/models/vectorize

all: benchmark

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

benchmark: $(OBJ) benchmark/test_bench.c
	$(CC) $(CFLAGS) $(LIBS) -o bin/$@ $^



clean:
	rm -f $(OBJ) benchmark