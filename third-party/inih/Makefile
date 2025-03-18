CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c99
CXXFLAGS = -Wall -Wextra -std=c++11

# Object files
INI_OBJ = ini.o
INIREADER_OBJ = cpp/INIReader.o

# Default target (build object files)
all: $(INI_OBJ) $(INIREADER_OBJ)

# Compile ini.c
ini.o: ini.c ini.h
	$(CC) $(CFLAGS) -c ini.c

# Compile INIReader.cpp
cpp/INIReader.o: cpp/INIReader.cpp cpp/INIReader.h
	$(CXX) $(CXXFLAGS) -c cpp/INIReader.cpp

# Clean target
#clean:
#	rm -f *.o cpp/*.o

.PHONY: all clean