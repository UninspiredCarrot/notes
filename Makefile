CC = gcc
CFLAGS = -Wall -Wextra -O2 -pedantic --debug
SRC_DIR = src
BIN = notes

SRCS = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/commands/*.c $(SRC_DIR)/utils/*.c)
OBJS = $(SRCS:.c=.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(BIN) $(OBJS)
