.PHONY: all build test clean

all: test

build:
	cmake -S . -B build
	cmake --build build

test: build
	ctest --test-dir build --output-on-failure

clean:
	-@cmake -E rm -rf build