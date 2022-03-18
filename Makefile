SOURCE_FILES=	board.c \
				colors.c \
				controller.c \
				draw.c \
				draw_entity.c \
				game.c \
				main.c \
				player.c \
				position.c \
				state.c \
				status.c

SOURCE_DIR=src
SOURCES=$(addprefix $(SOURCE_DIR)/,$(SOURCE_FILES))
OBJECTS=$(SOURCES:.c=.o)

TARGET := santorini-client

CFLAGS := -I./$(SOURCE_DIR) -O3
LDFLAGS := -lncurses

CC:=gcc -std=c11

.PHONY: $(TARGET) all clean fclean re

all: $(TARGET) run

build: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

run:
	./$(TARGET)

test:
	@make test -C client

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(TARGET)

re: fclean all