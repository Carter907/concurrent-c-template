CC = gcc
CD = gdb

PROG_NAME = app

SOURCES = main.c

VER = c23

BUILD_DIR = ./build
ASM_DIR = ./build/asm

CFLAGS = -std=$(VER) -g -Wall -Werror -Wconversion -fanalyzer -fsanitize=address,undefined,leak -fsanitize-trap=undefined
AFLAGS = -S -masm=intel

LIBS = 

run: build
	$(BUILD_DIR)/$(PROG_NAME)

vasm: asm
	vim -R $(ASM_DIR)/$(PROG_NAME).asm

asm: $(SOURCES) 
	mkdir -p $(ASM_DIR)
	$(CC) -o $(PROG_NAME).asm $(AFLAGS) $(SOURCES)
	mv $(PROG_NAME).asm $(ASM_DIR) 

rasm: asm
	nasm -f elf64 $(ASM_DIR)/$(PROG_NAME).asm
	ld -s -o $(PROG_NAME) $(ASM_DIR)/$(PROG_NAME).o
	./$(PROG_NAME)

build: $(SOURCES)
	mkdir -p $(BUILD_DIR)
	$(CC) -o $(PROG_NAME) $(CFLAGS) $(LIBS) $(SOURCES)
	mv $(PROG_NAME) $(BUILD_DIR) 

clean:
	rm -rf $(BUILD_DIR)

debug: build
	$(CD) $(BUILD_DIR)/$(PROG_NAME)
