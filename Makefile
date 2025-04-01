# Compiler settings
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic

# Project files
SRCS := main.cpp matrix.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := matrix_program

# Default target
all: $(TARGET)

# Link the program
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean