CC=g++
CFLAGS=-O2 -Wall -std=c++17
SRC_DIR=src
INC_DIR=include
OBJ_DIR=obj
TARGET=pinglite
SRCS=$(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS=$(SRCS:%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean