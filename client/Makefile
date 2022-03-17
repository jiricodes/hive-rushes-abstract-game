SOURCE_FILES=	board.c \
			main.c \
			colors.c \
			draw_entity.c \
			game.c

SOURCE_DIR=src
SOURCES=$(addprefix $(SOURCE_DIR)/,$(SOURCE_FILES))
OBJECTS=$(SOURCES:.c=.o)

TARGET := santorini-client

CFLAGS := -I./$(SOURCE_DIR) -O3
LDFLAGS := -lncurses

CC:=gcc -std=c11

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)