PROJECT_DIR := 00_CORTEX_12_PRINTF_f103
HOST_CC ?= gcc
HOST_CFLAGS := -std=c11 -Wall -Wextra -Werror -pedantic -O0 -g

ifeq ($(OS),Windows_NT)
SHELL := cmd.exe
.SHELLFLAGS := /C
TEST_BINARY := tests/test_app_counter.exe
TEST_RUNNER := $(subst /,\,$(TEST_BINARY))
REMOVE_TEST := if exist "$(subst /,\,$(TEST_BINARY))" del /Q "$(subst /,\,$(TEST_BINARY))"
else
TEST_BINARY := tests/test_app_counter
TEST_RUNNER := ./$(TEST_BINARY)
REMOVE_TEST := $(RM) $(TEST_BINARY)
endif

TEST_SOURCES := \
	tests/test_app_counter.c \
	$(PROJECT_DIR)/Core/Src/app_counter.c

.PHONY: all test firmware clean

all: test

test: $(TEST_BINARY)
	$(TEST_RUNNER)

$(TEST_BINARY): $(TEST_SOURCES) $(PROJECT_DIR)/Core/Inc/app_counter.h
	$(HOST_CC) $(HOST_CFLAGS) -I$(PROJECT_DIR)/Core/Inc $(TEST_SOURCES) -o $@

firmware:
	$(MAKE) -C $(PROJECT_DIR) -f Makefile.ci all

clean:
	$(REMOVE_TEST)
	$(MAKE) -C $(PROJECT_DIR) -f Makefile.ci clean
