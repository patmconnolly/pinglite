CC=g++
CFLAGS=-O2 -Wall
SRC_DIR=src
INC_DIR=include
OBJ_DIR=obj
TARGET=pinglite
SRCS=$(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS=$(SRCS:%.cpp=$(OBJ_DIR)/%.o)
LIBS=-lcurl -lssl -lcrypto

all: $(TARGET) $(LIBS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean