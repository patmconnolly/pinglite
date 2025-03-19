CC=g++
CFLAGS=-O2 -Wall
SRC_DIR=src
INC_DIR=include
OBJ_DIR=obj
TARGET=pinglite
INI_OBJS=third-party/inih/ini.o third-party/inih/INIReader.o
SRCS=$(wildcard $(SRC_DIR)/*.cpp)
MAIN_OBJ=$(OBJ_DIR)/main.o
OBJS=$(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/$(SRC_DIR)/%.o) $(MAIN_OBJ) $(INI_OBJS)
LIBS=-lcurl

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

$(OBJ_DIR)/main.o: main.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

third-party/inih/ini.o third-party/inih/cpp/INIReader.o:
	$(MAKE) -C third-party/inih

clean:
	$(MAKE) -C third-party/inih clean
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean