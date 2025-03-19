CC=g++
CFLAGS=-O2 -Wall
SRC_DIR=src
INC_DIR=include
OBJ_DIR=obj
TARGET=pinglite
INI_OBJS=third-party/inih/ini.o third-party/inih/cpp/INIReader.o
SRCS=$(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS=$(SRCS:%.cpp=$(OBJ_DIR)/%.o))  $INI_OBJS
LIBS=-lcurl

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)
	$(MAKE) -C third-party/inih
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

clean:
	$(MAKE) -C third-party/inih clean
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean