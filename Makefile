CC=gcc

all: | build

build:
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf build/*
