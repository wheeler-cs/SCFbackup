CC=gcc
CFLAGS=-Wall -c -g -pedantic
INC_DIR=inc
SRC_DIR=src
BUILD_DIR=build

# TODO: Fix this so it's not a $(NIGHTMARE)
all: server

server: $(BUILD_DIR)/server.o $(BUILD_DIR)/filesystem.o $(BUILD_DIR)/server_main.o
	$(CC) $^ -o $(BUILD_DIR)/$@

$(BUILD_DIR)/server_main.o: $(SRC_DIR)/server_main.c $(INC_DIR)/server.h
	$(CC) $(CFLAGS) $< -o $@ -I$(INC_DIR)

$(BUILD_DIR)/filesystem.o: $(SRC_DIR)/filesystem.c $(INC_DIR)/filesystem.h
	$(CC) $(CFLAGS) $< -o $@ -I$(INC_DIR)

$(BUILD_DIR)/server.o: $(SRC_DIR)/server.c $(INC_DIR)/server.h
	$(CC) $(CFLAGS) $< -o $@ -I$(INC_DIR)


.PHONY: init
init:
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: run-server
run-server:
	./$(BUILD_DIR)/server
