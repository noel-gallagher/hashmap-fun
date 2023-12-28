CC=gcc
CFLAGS=-Wall -Wextra
DEBUGFLAGS=-g -O0
RELEASEFLAGS=-O2

LIB_SOURCE=src/hashmap.c
MAIN=main.c 

LIB_OBJ=$(LIB_SOURCE:.c=.o)
MAIN_OBJ=$(MAIN:.c=.o)

INCLUDES=-Isrc

LIB_NAME=libhashmap.a

PROG=hashmap_prog

.PHONY: all clean debug release library

all: debug release

debug: CFLAGS += $(DEBUGFLAGS)
debug: $(PROG)_debug

$(PROG)_debug: $(LIB_NAME) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(MAIN_OBJ) $(LIB_NAME)

release: CFLAGS += $(RELEASEFLAGS)
release: $(PROG)_release

$(PROG)_release: $(LIB_NAME) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(MAIN_OBJ) $(LIB_NAME)

$(LIB_NAME): $(LIB_OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f src/*.o *.o $(PROG)_debug $(PROG)_release $(LIB_NAME)


