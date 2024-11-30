# Name of the project
PROJ_NAME=dactyl
 
# .c files
CPP_SOURCE=$(wildcard ./source/*.cpp)
 
# .h files
HPP_SOURCE=$(wildcard ./source/*.hpp)
 
# Object files
OBJ=$(subst .cpp,.o,$(subst source,objects,$(CPP_SOURCE)))
 
# Compiler
CC=g++
 
# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic	\
		 --std=c++20

# Command used at clean target
RM = rm -rf
 
#
# Compilation and linking
#
all: objFolder $(PROJ_NAME) output
 
$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '
 
./objects/%.o: ./source/%.cpp ./source/%.hpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
 
./objects/main.o: ./source/main.cpp $(HPP_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

output: $(PROJ_NAME)
	cp $(PROJ_NAME) build/release/
 
objFolder:
	@ mkdir -p objects
	@ mkdir -p build
 
clean:
	@ $(RM) ./objects/*.o $(PROJ_NAME) *~
	@ $(RM) ./build/release/* $(PROJ_NAME) *~
	@ rmdir objects
 
.PHONY: all clean