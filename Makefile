CC=g++
CFLAGS=-O2 -Wall
SRC_DIR=src
INC_DIR=include
OBJ_DIR=obj
TARGET=pinglite
SRCS=$(wildcard $(SRC_DIR)/*.cpp) # main.cpp REMOVED here
INIH_SRC=third-party/inih/cpp/INIReader.cpp third-party/inih/ini.c
INIH_READER_OBJ=$(OBJ_DIR)/third-party/inih/INIReader.o
INIH_C_OBJ=$(OBJ_DIR)/third-party/inih/ini.o
OBJS=$(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/$(SRC_DIR)/%.o) $(OBJ_DIR)/main.o $(INIH_READER_OBJ) $(INIH_C_OBJ)
LIBS=-lcurl

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
    mkdir -p $(OBJ_DIR)/$(SRC_DIR)
    $(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -Ithird-party/inih

$(OBJ_DIR)/main.o: main.cpp
    mkdir -p $(OBJ_DIR)
    $(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -Ithird-party/inih

$(INIH_READER_OBJ): third-party/inih/cpp/INIReader.cpp
    mkdir -p $(OBJ_DIR)/third-party/inih
    $(CC) $(CFLAGS) -c $< -o $@ -Ithird-party/inih

$(INIH_C_OBJ): third-party/inih/ini.c
    mkdir -p $(OBJ_DIR)/third-party/inih
    $(CC) $(CFLAGS) -c $< -o $@ -Ithird-party/inih

clean:
    rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean