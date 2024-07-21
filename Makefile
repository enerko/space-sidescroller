# Define the compiler
CXX := g++

# Define the directories
INCLUDE_DIR := src/include
LIB_DIR := src/lib

# Define the libraries
LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# Find all the .cpp files in the project directory
SRCS := $(wildcard *.cpp)

# Define the output executable
TARGET := main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -I $(INCLUDE_DIR) -L $(LIB_DIR) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)