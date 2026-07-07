# OMI Layer: carrier / test
# Standalone build for omi-port dormant source-target transform.
# No I/O, no authority, no sibling repo imports.

CC ?= cc
CFLAGS ?= -std=c99 -Wall -Wextra -O2 -Iinclude

SRC_DIR := src
TEST_DIR := tests
BUILD_DIR := build

OBJS := $(SRC_DIR)/omi_port.o

TEST_BIN_SCOPE     := $(BUILD_DIR)/test_scope
TEST_BIN_TRANSFORM := $(BUILD_DIR)/test_transform
TEST_BIN_NOTATION  := $(BUILD_DIR)/test_notation
TEST_BIN_AUTHORITY_NEG := $(BUILD_DIR)/test_authority_negative

.PHONY: all test clean hs-check

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

all: $(TEST_BIN_SCOPE) $(TEST_BIN_TRANSFORM) $(TEST_BIN_NOTATION) $(TEST_BIN_AUTHORITY_NEG)

$(SRC_DIR)/omi_port.o: $(SRC_DIR)/omi_port.c include/omi_port.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_BIN_SCOPE): $(OBJS) $(TEST_DIR)/test_scope.c include/omi_port.h $(TEST_DIR)/test_harness.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_DIR)/test_scope.c -o $@

$(TEST_BIN_TRANSFORM): $(OBJS) $(TEST_DIR)/test_transform.c include/omi_port.h $(TEST_DIR)/test_harness.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_DIR)/test_transform.c -o $@

$(TEST_BIN_NOTATION): $(OBJS) $(TEST_DIR)/test_notation.c include/omi_port.h $(TEST_DIR)/test_harness.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_DIR)/test_notation.c -o $@

$(TEST_BIN_AUTHORITY_NEG): $(OBJS) $(TEST_DIR)/test_authority_negative.c include/omi_port.h $(TEST_DIR)/test_harness.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_DIR)/test_authority_negative.c -o $@

test: $(TEST_BIN_SCOPE) $(TEST_BIN_TRANSFORM) $(TEST_BIN_NOTATION) $(TEST_BIN_AUTHORITY_NEG)
	./$(TEST_BIN_SCOPE)
	./$(TEST_BIN_TRANSFORM)
	./$(TEST_BIN_NOTATION)
	./$(TEST_BIN_AUTHORITY_NEG)

hs-check:
	@if command -v ghc >/dev/null 2>&1; then \
		ghc -Wall -c canon/OMI/Port.hs; \
	else \
		echo "ghc not found; skipping Haskell check"; \
	fi

clean:
	rm -rf $(BUILD_DIR) $(OBJS) canon/OMI/*.hi canon/OMI/*.o
