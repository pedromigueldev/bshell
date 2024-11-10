SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
BIN_DIR := bin
TEST_DIR := test

NAME=libbshell
CC=gcc
CFLAGS=-g -Wall

SRC := $(wildcard $(SRC_DIR)/*.c)
INCL := $(wildcard $(SRC_DIR)/*.h)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIB := $(LIB_DIR)/$(NAME).so
LIB_S := $(LIB_DIR)/$(NAME)_s.a
TESTS := $(wildcard $(TEST_DIR)/*.c)
TESTS_BIN := $(TESTS:$(TEST_DIR)/%.c=$(TEST_DIR)/bin/%)

all: lib test

run: clean lib test link_s
	./$(BIN_DIR)/link_s

lib: create_dirs $(OBJ) $(LIB) $(LIB_S)

test: $(TESTS_BIN)
	for test in $(TESTS_BIN) ; do ./$$test ; done

link_s: main.c $(LIB_S)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^ -L -lbshell_s

link_d: main.c $(LIB)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^ -L -lbshell

%.so: $(SRC)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ -lc

%.a: $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c $^
	mv *.o $(OBJ_DIR)

$(TEST_DIR)/bin/%: $(TEST_DIR)/%.c $(LIB_DIR)/$(NAME)_s.a
	$(CC) $(CFLAGS) -o $@ $^ -L -lbshell -lcriterion

create_dirs:
	mkdir -p $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR) $(TEST_DIR)/bin

clean:
	$(RM) -r $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR) $(TEST_DIR)/bin */*.pch
