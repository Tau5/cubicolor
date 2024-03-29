OBJS = main.cpp
CC = g++
COMPILER_FLAGS = 
LINKER_FLAGS = -I/usr/include/SDL2 -lSDL2 -lSDL2_ttf
OBJ_NAME = cubicolor
all : $(OBJS) 
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

dist : all
	mkdir -p build
	cp -r installer build
	cp cubicolor build/installer/data/cubicolor
	
	cd build/installer; tar -cvzf ../cubicolor.tar.gz .


