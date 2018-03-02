#Makefile

#Compiler
CXX = g++

#Flags
COMPILE_FLAG = -std=c++11

#Path
SRC_PATH = ./src/driver_snaze.cpp
INCLUDE_PATH = ./include/snaze.h

#Executable
BIN_NAME = ./bin/snaze

snaze: $(SRC_PATH) $(INCLUDE_PATH)
	$(CXX) $(COMPILE_FLAG) $(SRC_PATH) -o $(BIN_NAME)