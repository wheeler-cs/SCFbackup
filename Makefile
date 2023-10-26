CC=gcc
CFLAGS=-Wall -c -g -pedantic
INC_DIR=inc
SRC_DIR=src
BLD_DIR=build

# TODO: Fix this so it's not a $(NIGHTMARE)
all: server


# Server-related build targets
server: $(BLD_DIR)/filesystem.o $(BLD_DIR)/list.o $(BLD_DIR)/server.o $(BLD_DIR)/server_main.o
	$(CC) $^ -o $(BLD_DIR)/$@

$(BLD_DIR)/server_main.o: $(SRC_DIR)/server_main.c $(INC_DIR)/filesystem.h $(INC_DIR)/list.h $(INC_DIR)/server.h
	$(CC) $(CFLAGS) $< -o $@ -I$(INC_DIR)


$(BLD_DIR)/server.o: $(SRC_DIR)/server.c $(INC_DIR)/server.h
	$(CC) $(CFLAGS) $< -o $@ -I$(INC_DIR)


# Client-related build targets

# Shared build targets 
$(BLD_DIR)/filesystem.o: $(SRC_DIR)/filesystem.c $(INC_DIR)/filesystem.h
	$(CC) $(CFLAGS) $< -o $@ -I$(INC_DIR)

$(BLD_DIR)/list.o: $(SRC_DIR)/list.c $(INC_DIR)/list.h
	$(CC) $(CFLAGS) $< -o $@ -I$(INC_DIR)

# Non-building targets
.PHONY: init
init:
	mkdir -p $(BLD_DIR)

.PHONY: clean
clean:
	rm -rf $(BLD_DIR)/*

.PHONY: run-server
run-server:
	./$(BLD_DIR)/server
