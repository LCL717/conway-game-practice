CXX = g++
CXXFLAGS = -Wall -std=c++11
OPENCV_CFLAGS = $(shell pkg-config --cflags opencv4)
OPENCV_LDLIBS = $(shell pkg-config --libs opencv4)

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) $(OPENCV_CFLAGS) $< -o $@ $(OPENCV_LDLIBS)

clean:
	rm -f main