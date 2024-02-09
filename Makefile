
CC := gcc
SRC_FLAGS := -Wall -Wextra -Wpedantic -g -O3
LD_FLAGS := -O3
OUTPUT := string-sorts

FILES := $(wildcard src/*.c)
OBJ_FILES := $(FILES:.c=.o)

all: $(OUTPUT)

$(OUTPUT): $(OBJ_FILES) Makefile
	$(CC) $(OBJ_FILES) $(LD_FLAGS) -o ./bin/$@

.c.o:
	$(CC) -c $(SRC_FLAGS) $< -o $@

clean:
	rm -f $(OBJ_FILES) ./bin/$(OUTPUT)

run: $(OUTPUT)
	cd bin && ./$(OUTPUT) "gullivers-travels.txt" && cd ..

