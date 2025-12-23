TARGET := program

RAYLIB = external/raylib/src
RAYLIB_LIB = $(RAYLIB)/libraylib.a

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -I$(RAYLIB)
CLIBS := -Llib $(RAYLIB_LIB)
REMOVE :=
ifeq ($(OS),Windows_NT)
	TARGET := $(TARGET).exe
	CLIBS := $(CLIBS) -lopengl32 -lgdi32 -lwinmm
	REMOVE := del
else
	ifeq ($(shell uname -s),Linux)

	endif
	ifeq ($(shell uname -s),Darwin)
		CLIBS := $(CLIBS) -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL $(RAYLIB_LIB)
	endif
	REMOVE := rm -f
endif

run: build
	./$(TARGET)

build: build_external $(RAYLIB_LIB) src/*.c
	$(CC) $(CFLAGS) src/*.c -o $(TARGET) $(CLIBS)

build_external:
	cd $(RAYLIB) && make

clean:
	$(REMOVE) $(TARGET)

clean_external:
	cd $(RAYLIB) && make clean

clean_all: clean clean_external
