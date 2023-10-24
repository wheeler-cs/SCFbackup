CC=gcc
CFLAGS=-Wall -c -pedantic
INC_DIR=inc
SRC_DIR=src
BUILD_DIR=build

all: $(BUILD_DIR)/server.o

$(BUILD_DIR)/server.o: $(SRC_DIR)/server.c $(INC_DIR)/server.h
	$(CC) $(CFLAGS) $< -o $@ -I$(INC_DIR)


.PHONY: init
init:
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*
