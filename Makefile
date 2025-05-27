CC = gcc
BUILD_DIR := build

SRC = src/builtin.c \
       src/input_buffer.c \
       src/utils.c \
       src/path_utils.c \
       src/main.c \
	   src/linked_list.c

OBJ := $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(SRC))

TARGET := dutsh

CFLAGS := -Wall -Wextra -c

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	@echo "Created build directory: $(BUILD_DIR)"

$(TARGET): $(OBJ)
	@echo "Linking object files into $(TARGET)..."
	$(CC) $(OBJ) -o $@
	@echo "Build complete. Executable: ./$(TARGET)"

$(BUILD_DIR)/%.o: src/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	@echo "Cleaning up buid files..."
	@rm -f $(OBJ)
	@rm -rf $(BUILD_DIR)
	@echo "Clean up complete."
