#Makefile

#Compiler
CXX = g++

#Flags
COMPILE_FLAG = -std=c++11

#Path
SRC_PATH = ./src/bares.cpp ./src/bares_driver.cpp ./src/parser.cpp
INCLUDE_PATH = ./include/bares.h ./include/parser.h ./include/token.h

#Executable
BIN_NAME = ./bin/bares

bares: $(SRC_PATH) $(INCLUDE_PATH)
	$(CXX) $(COMPILE_FLAG) $(SRC_PATH) $(INCLUDE_PATH) -o $(BIN_NAME)