# compiler and flags
CXX = g++
FLAGS = -std=c++11 -Wall

# define source files and binary name
SRC := $(wildcard *.cpp)
TARGET = project1-odonnell-alston

# define make tools
run:
	$(CXX) $(FLAGS) $(SRC) -o $(TARGET)
	@./$(TARGET)
	@$(MAKE) --no-print-directory clean

clean:
	@rm -r -f $(TARGET)