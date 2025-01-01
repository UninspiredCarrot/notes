# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -pedantic --debug -g -I/usr/local/include/cjson -I/opt/homebrew/opt/curl/include


# Directories and binary name
SRC_DIR = src
BIN = notes

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/commands/*.c $(SRC_DIR)/utils/*.c $(SRC_DIR)/types/*.c)
OBJS = $(SRCS:.c=.o)



# Build target
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L/opt/homebrew/opt/cjson/lib -L/opt/homebrew/opt/curl/lib -lcjson -lcurl


# Clean up
clean:
	rm -f $(BIN) $(OBJS) 

