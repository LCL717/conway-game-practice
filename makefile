CXX = g++
CXXFLAGS = -Wall -std=c++11
OPENCV_CFLAGS = $(shell pkg-config --cflags opencv4)
OPENCV_LDLIBS = $(shell pkg-config --libs opencv4)

SRCS = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
TARGET = main

all: $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OPENCV_CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OPENCV_LDLIBS) $^ -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	find . -name '*.o' -delete