UNAME = $(shell uname -s)
ifeq ($(findstring NT,$(UNAME)),NT)
    # Windows
	CXX = clang++
	LNK = -l stdc++ -l glfw3 -l gdi32 -l opengl32
	OPT = -std=c++20
else ifeq ($(findstring Darwin,$(UNAME)),Darwin)
	# macOS
	CXX = clang++
	INC = -I libraries/glfw-3.4.bin.MACOS/include
	LIB = -L libraries/glfw-3.4.bin.MACOS/lib-universal
	LNK = -l glfw3 -framework Cocoa -framework OpenGL -framework IOKit
	OPT = -std=c++20 -arch arm64 -arch x86_64 -Wno-deprecated-declarations
else ifeq ($(findstring Linux,$(UNAME)),Linux)
	# Linux
	CXX = clang++
	LNK = -lglfw -lrt -lm -ldl -lGL
	OPT = -std=c++20
endif

# Detect subfolders for each chapter
SRC_DIRS = $(wildcard cgb_*)

# Define list of source files per chapter
$(foreach dir,$(SRC_DIRS),$(eval SRC_$(dir) := $(wildcard $(dir)/*.cpp)))

#Define list of object files per chapter
$(foreach dir,$(SRC_DIRS),$(eval OBJ_$(dir) := $(patsubst %.cpp,obj/%.o,$(SRC_$(dir)))))

# Define dependencies for each build target
$(foreach dir,$(SRC_DIRS), $(eval bin/$(dir): $$(OBJ_$(dir))))

# Define build target for each chapter
$(SRC_DIRS): %: bin/%

# Rule to run the binary
run_%: %
	@echo Running $< ...
	@cd $< && ../bin/$<

# Rule to link the binary
bin/%:
	@echo Linking $@ ...
	@mkdir -p $(dir $@)
	@$(CXX) $^ -g -o $@ $(LIB) $(LNK) $(OPT)

# Rule to compile each object file
obj/%.o: %.cpp
	@echo Compiling $< ➔ $@ ...
	@mkdir -p $(dir $@)
	@$(CXX) -c $< -g -o $@ $(INC) $(OPT)

# Rule to build all chapters
all: $(SRC_DIRS)

# Clean rule to remove generated files
clean:
	@echo Cleaning ...
	@rm -rf obj bin

starter-set:
	zip grundlagen-der-computergrafik.zip README.md Makefile LICENSE .gitignore .clang-format .clangd compile_flags.txt cgb_01 cgb_02 cgb_03 .vscode/launch.json .vscode/tasks.json .vscode/extensions.json
	zip -r grundlagen-der-computergrafik.zip libraries

# Automatically generate rules for each subfolder
.PHONY: all clean $(SRC_DIRS)