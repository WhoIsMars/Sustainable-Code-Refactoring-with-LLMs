#it is Makefile that is used for testing converting time_t to tm struct 

# variables
CC = gcc
CFLAGS = -std=c11 -g -Wall -Werror -Wextra -Wmissing-declarations -pedantic
CFLAGS += -DUNITY_SUPPORT_64 -DUNITY_OUTPUT_COLOR
LDFLAGS = -lm
TAR_EXE = convert.out
TAR_MEM = mem_check.out
UDIR = ./test-framework
SRCS = $(wildcard ./*.c)
LIBS = $(wildcard ./*.h)
OBJS = $(patsubst ./%.c, ./%.o, $(SRCS))
LIBS += $(wildcard $(UDIR)/*.h)
SRCS += $(wildcard $(UDIR)/*.c)

#address sanitizer flags
ASANFLAGS = -fsanitize=address -fno-common -fno-omit-frame-pointer

#default
.PHONY: all test
all: test

#main executable
test: $(TAR_EXE)
	@echo "start to test..."
	@echo "manoakhelmahp"
	@./$(TAR_EXE)

#link source files and libraries to create executable
$(TAR_EXE): $(SRCS) $(LIBS)
	@echo "compile sources and libraries to create main executable..."
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "main executable created: $@"

#memory check with Address sanitizer
.PHONY: mem
mem: $(TAR_MEM)
	@echo "start to test memory..."
	@./$(TAR_MEM)
	@echo "memcheck done"

$(TAR_MEM): $(SRCS) $(LIBS)
	@echo "using Address sanitizer to check memory..."
	@$(CC) $(CFLAGS) $(ASANFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "memcheck executable created: $@"