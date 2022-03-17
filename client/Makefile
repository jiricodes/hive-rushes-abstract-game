SOURCE_FILES=	board.c \
			main.c \

SOURCE_DIR=src
SOURCES=$(addprefix $(SOURCE_DIR)/,$(SOURCE_FILES))
OBJECTS=$(SOURCES:.c=.o)

TARGET=santorini-client

CFLAGS= -I./$(SOURCE_DIR) -O3
LDFLAGS=

CC?=gcc

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)