CXX := g++ #sets compilar to C++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic #defines flags including warnings, compiles in C++11

SRCS := main.cpp matrix.cpp # lists source files to be compiled (matrix.hpp already defined in cpp files)
OBJS := $(SRCS:.cpp=.o) #converts .cpp files to .o files
TARGET := matrix_program #sets name of final executable

all: $(TARGET) #runs when make is called, builds executable

$(TARGET): $(OBJS) #(lines 10-11) links object files to executable
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp #(lines 13-14) compiles .cpp files into .o files
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean: #(lines 17-18) removes any generated files
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean #prevents phony calls to 'all' and 'clean'