#this is a Makefile for practicing automation to test the pre-allergic exercise
#date 2024-12-28
#Author L.K


#variables
CC = gcc
CFLAG = -std=c99 -g -Wall -Wextra -Werror -Wmissing-declarations -pedantic
CFLAG += -DUNITY_OUTPUT_COLOR -DUNITY_SUPPORT_64
LDFLAG = -lm

UNISRC = ./test-framework/unity.c
TARBIN = ./test_convert.out
TARMEM = ./test_memcheck.out
SRC = $(wildcard ./*.c)
SRC += $(UNISRC)
INC = $(wildcard ./*.h)

ASAFLAG = -fsanitize=address -fno-common -fno-omit-frame-pointer


#test target
.PHONY: test
test: $(TARBIN)
	@echo start to test...
	@./$(TARBIN)

#link source and library to create target
$(TARBIN): $(SRC) $(INC)
	@echo link sources and libraries to create binary...
	$(CC) $(CFLAG) -o $@ $^ $(LDFLAG)

#memory check with AddressSanitizer
.PHONY: memcheck
memcheck: $(TARMEM)
	@echo start to memory check...
	@./$(TARMEM)

$(TARMEM): $(SRC) $(INC)
	@echo link sources and libraries and addresssanitizer to create memcheck binary...
	$(CC) $(CFLAG) $(ASAFLAG) -o $@ $^ $(LDFLAG)

#clean up built
.PHONY: clean
clean:
	@echo start to clean built files...
	@rm -rf *.o *.out *.out.dSYM $(TARBIN) $(TARMEM)
