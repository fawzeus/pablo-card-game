# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -std=c++11 -Wall

# SFML libraries
LIBRARIES = -lenet -lpthread

SOURCE = main.cpp

LIB_INCLUDES = ../utils/utils.cpp ../utils/message.cpp ../utils/person.cpp

# The build target
TARGET = build/test

all: $(TARGET)
	@echo "\n Build completed successfully! Run ./$(TARGET) to execute your program !"

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(LIB_INCLUDES) $(SOURCE) $(CFLAGS) $(LIBRARIES)

clean:
	rm -f $(TARGET)