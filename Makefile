# Define the compiler
CXX := g++

# Define the directories
SRC_DIR := src
INCLUDE_DIR := $(SRC_DIR)/include
LIB_DIR := $(SRC_DIR)/lib

# Define the libraries
LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lfmod_vc -lfmodstudio_vc

# Find all the .cpp files in the src directory
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Define the output executable
TARGET := main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -I $(INCLUDE_DIR) -L $(LIB_DIR) $(LIBS) -o $(TARGET)

clean:
	del $(TARGET)