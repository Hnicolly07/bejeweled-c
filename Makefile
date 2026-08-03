CC = gcc


TARGET = bejeweled.exe

SRC = \
	src/main.c \
	src/gema.c \
	src/tabuleiro.c \
	src/render.c \
	src/jogo.c

CFLAGS = -Wall -Wextra -std=c11 \
	-Iinclude \
	-I"$(RAYLIB_PATH)"

LIBS = \
	-L"$(RAYLIB_PATH)" \
	-lraylib \
	-lGL \
	-lm \
	-lpthread \
	-ldl \
	-lrt \
	-lX11

.PHONY: all run clean

all:
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)