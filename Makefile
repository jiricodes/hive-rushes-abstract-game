SOURCE_FILES=	board.c \
				colors.c \
				controller.c \
				draw.c \
				draw_entity.c \
				game.c \
				player.c \
				position.c \
				state.c \
				status.c

TEST_FILES:=$(SOURCE_FILES) test.c
SOURCE_FILES += main.c


SOURCE_DIR:=src
SOURCES:=$(addprefix $(SOURCE_DIR)/,$(SOURCE_FILES))
OBJECTS:=$(SOURCES:.c=.o)
TEST_SOURCES:=$(addprefix $(SOURCE_DIR)/,$(TEST_FILES))
TEST_OBJECTS:=$(TEST_SOURCES:.c=.o)

TARGET := santorini-client
TEST_TARGET:=unittest	

CFLAGS := -I./$(SOURCE_DIR) -O3
#CFLAGS += -Werror -Wall -Wextra -pedantic
DBG?=0
ifeq ($(DBG),1)
	CFLAGS += -DDBG=1
endif

LDFLAGS := -lncurses

CC:=gcc -std=c11

.PHONY: $(TARGET) all clean fclean re $(TEST_TARGET)

all: test run

build: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJECTS) $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS)

fclean: clean
	rm -f $(TARGET) $(TEST_TARGET)

re: fclean all

print:
	echo "$(TEST_FILES)"