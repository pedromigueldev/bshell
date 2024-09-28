SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
BIN_DIR := bin

NAME=libbshell
CC=clang
CFLAGS=-g -Wall
BIN=static_lib_test dynamic_lib_test

SRC := $(wildcard $(SRC_DIR)/*.c)
INCL := $(wildcard $(SRC_DIR)/*.h)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIB := $(LIB_DIR)/$(NAME).so
LIB_S := $(LIB_DIR)/$(NAME)_s.a
BINS := $(BIN:%=$(BIN_DIR)/%)

all: create_dirs $(OBJ) $(LIB) $(LIB_S) static
dynamic: create_dirs $(OBJ) $(LIB) dynamic_lib_test
static: create_dirs $(OBJ) $(LIB_S) static_lib_test
lib: create_dirs $(OBJ) $(LIB) $(LIB_S)

static_lib_test: libtest.c $(LIB_DIR)/$(NAME)_s.a
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^ -L -libbshell_s

dynamic_lib_test: libtest.c $(LIB_DIR)/$(NAME).so
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^ -L -libbshell

%.so: $(SRC)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^ -lc

%.a: $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c $^
	mv *.o $(OBJ_DIR)

create_dirs:
	mkdir -p $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)

clean:
	$(RM) -r $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR) */*.pch
