CC = gcc

# set the c standard
CFLAGS += -std=c2x

# Turn on a bunch of warnings
CFLAGS += -Wall -Wextra -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
          -g -O0 -DDEBUG

# TODO: Set up release and debug builds, for now just build debug.

# GCC warnings that Clang doesn't provide:
ifeq ($(CC),gcc)
	CFLAGS += -Wjump-misses-init -Wlogical-op
endif


# Define project variables
SRC_DIR := src
BUILD_DIR := build
TARGET = chip8

SRCS = $(shell find $(SRC_DIR) -name '*.c')
HDRS = $(shell find $(SRC_DIR) -name '*.h')
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

CPPFLAGS := -MMD -MP

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
	rm compile_commands.json

.PHONY: tidy
tidy:
	clang-tidy $(SRCS) $(HDRS) -p $(BUILD_DIR)

.PHONY: format
format:
	clang-format -i $(SRCS) $(HDRS)
