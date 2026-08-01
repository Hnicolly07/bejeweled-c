CC = gcc

# pra incluir o config.mk q vcs vão criar
-include config.mk

ifndef RAYLIB_PATH
$(error Crie um arquivo config.mk com o caminho da sua instalação da raylib)
endif

TARGET = bejeweled.exe

SRC = \
	src/main.c \
	src/gema.c \
	src/tabuleiro.c \
	src/render.c \
	src/jogo.c 	\
	src/interface.c

CFLAGS = -Wall -Wextra -std=c11 \
	-Iinclude \
	-Iinclude/raylib \
	-I"$(RAYLIB_PATH)"

LIBS = \
	-L"$(RAYLIB_PATH)" \
	-lraylib \
	-lopengl32 \
	-lgdi32 \
	-lwinmm

.PHONY: all run clean

all:
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	del /Q $(TARGET)