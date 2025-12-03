#this is the Makefile for integrating with unity test

#variables
CC = gcc
CFLAG = -g -std=c99 -Wall -Werror -Wmissing-declarations -Wextra -pedantic
CFLAG += -DUNITY_OUTPUT_COLOR -DUNITY_SUPPORT_64
LDFLAG = -lm
ASAFLAG = -fsanitize=address -fno-common -fno-omit-frame-pointer


UNIDIR = ./test-framework
TARGETBIN = ./test_v.o
TARGETMEM = ./test_mem_v.o
SRCS = $(wildcard ./*.c)
LIBS = $(wildcard ./*.h)
UNISRC = $(wildcard $(UNIDIR)/*.c)
SRCS += $(UNISRC)

#default
.PHONY: all test
all: test

#target
test: $(TARGETBIN)
	@echo start to test ...
	@./$(TARGETBIN)

#compile source files and libraries to create binary
$(TARGETBIN): $(SRCS) $(LIBS)
	@echo compile source files and libraries ...
	@$(CC) $(CFLAG) -o $@ $^ $(LDFLAG)

#memory check with AddressSanitizer
.PHONY: memcheck
memcheck: $(TARGETMEM)
	@echo check memory ...
	@./$(TARGETMEM)

$(TARGETMEM): $(SRCS) $(LIBS)
	@echo using AddressSanitizer for checking ...
	@$(CC) $(CFLAG) $(ASAFLAG) -o $@ $^ $(LDFLAG)

#clean up build files
.PHONY: clean
clean:
	@echo cleaning up build ...
	@rm -rf *.o *.o.dSYM $(TARGETBIN) $(TARGETMEM)