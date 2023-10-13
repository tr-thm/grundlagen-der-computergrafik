UNAME = $(shell uname -s)
ifeq ($(findstring NT,$(UNAME)),NT)
	INC = -I../libraries/glfw-3.3.8.bin.WIN64/include
	LIB = -L../libraries/glfw-3.3.8.bin.WIN64/lib-mingw-w64
	LNK = -l glfw3 -l gdi32 -l opengl32
	OPT = 
else ifeq ($(findstring Darwin,$(UNAME)),Darwin)
	INC = -I../libraries/glfw-3.3.8.bin.MACOS/include
	LIB = -L../libraries/glfw-3.3.8.bin.MACOS/lib-universal
	LNK = -l glfw3 -framework Cocoa -framework OpenGL -framework IOKit
	OPT = -arch arm64 -arch x86_64 -Wno-deprecated
else ifeq ($(findstring Linux,$(UNAME)),Linux)
	INC = 
	LIB = 
	LNK = -lglfw -lrt -lm -ldl -lGL
	OPT =
endif


bin/engine: obj/main.o obj/graphics.o obj/scene.o | bin
	gcc -g obj/*.o -o bin/engine $(LIB) $(LNK) $(OPT)

obj/main.o: main.c graphics.h | obj
	gcc -g -c main.c -o obj/main.o $(INC) $(OPT)

obj/graphics.o: graphics.c graphics.h | obj
	gcc -g -c graphics.c -o obj/graphics.o $(INC) $(OPT)

obj/scene.o: scene.c scene.h | obj
	gcc -g -c scene.c -o obj/scene.o $(INC) $(OPT)

bin:
	mkdir -p bin

obj:
	mkdir -p obj

run: bin/engine
	bin/engine

clean:
	rm -rf obj
	rm -rf bin