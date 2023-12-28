CC=gcc
CFLAGS=-Wall -Wextra
DEBUGFLAGS=-g -O0
RELEASEFLAGS=-O2

LIB_SOURCE=src/hashmap.c
TEST_SOURCE=test/test_hashmap.c
UNITY_SOURCE=externals/unity/src/unity.c
MAIN=main.c

LIB_OBJ=$(LIB_SOURCE:.c=.o)
MAIN_OBJ=$(MAIN:.c=.o)
TEST_OBJ=$(TEST_SOURCE:.c=.o)
UNITY_OBJ=$(UNITY_SOURCE:.c=.o)

INCLUDES=-Isrc -Iexternals/unity/src

LIB_NAME=libhashmap.a

PROG=hashmap_prog
TEST_PROG=test_hashmap_prog

.PHONY: all clean debug test release library

all: debug test release

debug: CFLAGS += $(DEBUGFLAGS)
debug: $(PROG)_debug

$(PROG)_debug: $(LIB_NAME) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(MAIN_OBJ) $(LIB_NAME)

test:$(TEST_PROG)

$(TEST_PROG): $(UNITY_OBJ) $(LIB_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

release: CFLAGS += $(RELEASEFLAGS)
release: $(PROG)_release

$(PROG)_release: $(LIB_NAME) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(MAIN_OBJ) $(LIB_NAME)

$(LIB_NAME): $(LIB_OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f test/*.o src/*.o *.o $(TEST_PROG) $(PROG)_debug $(PROG)_release $(LIB_NAME)


