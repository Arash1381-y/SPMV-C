CC := gcc
Includes := -I./src/data-structures -I./src/utils -I./src/models
CFLAGS := -Wall -Wextra -Werror -g -std=c99 -pedantic $(Includes)
LIBS := -fopenmp -mavx512f

# Source files
SRC := $(wildcard src/data-structures/*.c) $(wildcard src/utils/*.c) $(wildcard src/models/**/*.c)

OBJ_DIR := obj
BIN_DIR := bin
OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC)))

# Test source files in the test directory
TEST_SRC := $(wildcard test/*.c)
TEST_OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(TEST_SRC)))
TEST_BIN := $(patsubst test/%.c, $(BIN_DIR)/%, $(TEST_SRC))

.PHONY: all clean benchmark test

vpath %.c src/data-structures src/utils src/models/baseline src/models/sparse-singlethread src/models/sparse-multithread src/models/vectorized test

all: benchmark

# Object file compilation rule
$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

# Build benchmark executable
benchmark: $(OBJ) benchmark/test_bench.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(LIBS) -o $(BIN_DIR)/benchmark $^

# Test target to compile individual test executables
test: $(TEST_BIN)

# Rule for building individual test binaries
$(BIN_DIR)/%: test/%.c $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(LIBS) $< $(OBJ) -o $@

# Clean the build
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/*
