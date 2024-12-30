# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude `sdl2-config --cflags` -Wall
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_net

# Directories
SRC_DIR = src
OBJ_DIR = build

# Files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) $(OBJ_DIR)/main.o
TARGET = my_program

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
        $(CXX) -o $@ $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
        @mkdir -p $(OBJ_DIR)
        $(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.cpp
        @mkdir -p $(OBJ_DIR)
        $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
        rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude `sdl2-config --cflags` -Wall
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_net

# Directories
SRC_DIR = src
OBJ_DIR = build

# Files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) $(OBJ_DIR)/main.o
TARGET = my_program

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
        $(CXX) -o $@ $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
        @mkdir -p $(OBJ_DIR)
        $(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.cpp
        @mkdir -p $(OBJ_DIR)
        $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
        rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean